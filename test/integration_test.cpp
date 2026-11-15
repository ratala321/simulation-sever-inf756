#include "main.cpp"
#include "network_definitions.h"

#include "rpc_message_body.h"
#include "rpc_message_buffer.h"
#include "rpc_serialize.h"
#include "rpc_deserialize.h"

#include "visitor.h"

#include <asio/buffer.hpp>
#include <asio/connect.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/read.hpp>
#include <asio.hpp>

#include <gtest/gtest.h>

#include <csignal>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace
{

struct MockupClientController
{
	explicit MockupClientController(SCS::SocketTCP socket) : socket{ std::move(socket) }
	{ }

	asio::awaitable<SCS::RPC::DeserializationResult> readNextMessage()
	{
		SCS::RPC::HeaderBuffer hBuffer;
		co_await asio::async_read(socket, asio::buffer(hBuffer));

		const SCS::RPC::RpcMessageHeader header = SCS::RPC::deserializeHeader(hBuffer.data());
		const auto s = SCS::RPC::getBodyBufferSize(header.type);

		SCS::RPC::ReadBuffer buffer;
		if (s != 0)
		{
			buffer.reserve(s);
			co_await asio::async_read(socket, asio::buffer(buffer));
		}

		co_return SCS::RPC::deserializeBody(header, buffer.data());
	}

	SCS::SocketTCP socket;
};

struct MockupClientContext
{
	using Resolver = asio::ip::tcp::resolver;
	using Endpoint = asio::ip::tcp::resolver::results_type;

	MockupClientContext(const char* argv[])
		: resolver(context), endpoint(resolver.resolve(argv[0], argv[1])), signals(context, SIGINT, SIGTERM)
	{
		signals.async_wait([&](auto, auto)
			{
				context.stop();
			}
		);
	}

	void run()
	{
		context.run();
	}

	MockupClientController createClient()
	{
		SCS::SocketTCP socket{ context };
		asio::connect(socket, endpoint);

		return MockupClientController{ std::move(socket) };
	}

	asio::io_context context;
	asio::signal_set signals;
	Resolver resolver;
	Endpoint endpoint;
};

void runServer()
{
	const char* argv[2] = { "127.0.0.1", "8080" };
	run(2, const_cast<char**>(argv));
}

};

class IntegrationTestSuite : public ::testing::Test {
};

TEST_F(IntegrationTestSuite, PingServerRespondsToClient) {
	try
	{
		std::mutex m;
		std::condition_variable cv;
		bool testDone = false;
		std::atomic<bool> receivedIdSync = false;

		std::thread tserver{ [] { runServer(); } };

		std::this_thread::sleep_for(std::chrono::microseconds(1));

		std::thread tclient{
			[&m, &cv, &testDone, &receivedIdSync]
			{
				const char* argv[2] = {
					"127.0.0.1",
					"8080"
				};
				MockupClientContext clientContext{ argv };

				auto clientController = clientContext.createClient();

				asio::co_spawn(
					clientController.socket.get_executor(),
					[&clientController, &cv, &m, &testDone, &receivedIdSync] -> asio::awaitable<void>
					{
						const auto dr = co_await clientController.readNextMessage();

						std::visit(
							SCS::Lang::Visitor{
								[](auto&) { std::cerr << "received wrong message type in PingServerRespondsToClient :c";},
								[&receivedIdSync](const SCS::RPC::IdSyncMessageBody&) { receivedIdSync = true; },
							},
							dr
						);

						m.lock();
						testDone = true;
						m.unlock();
						cv.notify_one();
					},
					[&cv, &m, &testDone](std::exception_ptr e)
					{
						try
						{
							if (e)
							{
								std::rethrow_exception(e);
							}
						}
						catch (...)
						{
							std::cerr << "error in client context";
						}
					}
				);
				clientContext.run();
			}
		};

		{
			std::unique_lock lock{ m };
			cv.wait_for(lock, std::chrono::seconds(2), [&testDone] {return testDone;});
		}

		std::raise(SIGINT);
		if (tserver.joinable())
		{
			tserver.join();
		}
		if (tclient.joinable())
		{
			tclient.join();
		}

		EXPECT_EQ(receivedIdSync, true);
	}
	catch (...)
	{
		std::cerr << "unknown error in PingServerRespondsToClient" << std::endl;
		ADD_FAILURE();
	}
}
