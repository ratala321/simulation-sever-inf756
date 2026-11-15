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

const char* testArgv[2] = {
	"127.0.0.1",
	"8080"
};


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
			co_await asio::async_read(socket, asio::buffer(buffer, buffer.capacity()));
		}

		co_return SCS::RPC::deserializeBody(header, buffer.data());
	}

	template<SCS::RPC::RpcMessageType T>
	asio::awaitable<void> sendMessage()
	{
		SCS::RPC::RpcMessageBody<T> body{};
		SCS::RPC::WriteBuffer buffer = SCS::RPC::serialize(body);
		co_await asio::async_write(socket, asio::buffer(buffer), asio::cancel_after(std::chrono::seconds(5)));
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
	run(2, const_cast<char**>(testArgv));
}

};

class IntegrationTestSuite : public ::testing::Test {
};

TEST_F(IntegrationTestSuite, IdSyncServerOnClientConnexion) {
	try
	{
		std::mutex m;
		std::condition_variable cv;
		bool testDone = false;
		std::atomic<bool> receivedIdSync = false;

		std::thread tserver{ [] { runServer(); } };

		std::this_thread::sleep_for(std::chrono::microseconds(50));

		MockupClientContext clientContext{ testArgv };

		auto clientController = clientContext.createClient();

		std::thread tclient{
			[&m, &cv, &testDone, &receivedIdSync, &clientContext, &clientController]
			{
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

TEST_F(IntegrationTestSuite, PingServerRespondsToClient) {
	try
	{
		std::mutex m;
		std::condition_variable cv;
		bool testDone = false;
		std::atomic<bool> receivedPing = false;

		std::thread tserver{ [] { runServer(); } };

		std::this_thread::sleep_for(std::chrono::microseconds(50));

		MockupClientContext clientContext{ testArgv };

		auto clientController = clientContext.createClient();

		std::thread tclient{
			[&m, &cv, &testDone, &receivedPing, &clientContext, &clientController]
			{
				asio::co_spawn(
					clientController.socket.get_executor(),
					[&clientController, &cv, &m, &testDone, &receivedPing] -> asio::awaitable<void>
					{
						// skip idSync
						const auto sync = co_await clientController.readNextMessage();

						std::visit(
							SCS::Lang::Visitor{
								[](auto&) { std::cerr << "sync received wrong message type in PingServerRespondsToClient :c\n";},
								[&receivedPing](const SCS::RPC::PingMessageBody&) { receivedPing = true; },
							},
							sync
						);

						//co_await clientController.sendMessage<SCS::RPC::RpcMessageType::ping>();

						const auto dr = co_await clientController.readNextMessage();

						std::visit(
							SCS::Lang::Visitor{
								[](auto&) { std::cerr << "dr received wrong message type in PingServerRespondsToClient :c\n";},
								[&receivedPing](const SCS::RPC::PingMessageBody&) { receivedPing = true; },
							},
							dr
						);

						const auto hello = co_await clientController.readNextMessage();

						std::visit(
							SCS::Lang::Visitor{
								[](auto&) { std::cerr << "hello received wrong message type in PingServerRespondsToClient :c\n";},
								[&receivedPing](const SCS::RPC::PingMessageBody&) { receivedPing = true; },
							},
							hello
						);
						std::cout << "hello called" << std::endl;

						const auto nani = co_await clientController.readNextMessage();

						std::visit(
							SCS::Lang::Visitor{
								[](auto&) { std::cerr << "nani received wrong message type in PingServerRespondsToClient :c\n";},
								[&receivedPing](const SCS::RPC::PingMessageBody&) { receivedPing = true; },
							},
							nani
						);
						std::cout << "nani called" << std::endl;

						const auto wtf = co_await clientController.readNextMessage();
						std::cout << "wtf called" << std::endl;

						std::visit(
							SCS::Lang::Visitor{
								[](auto&) { std::cerr << "wtf received wrong message type in PingServerRespondsToClient :c\n";},
								[&receivedPing](const SCS::RPC::PingMessageBody&) { receivedPing = true; },
							},
							wtf
						);

						{
							std::lock_guard _{ m };
							testDone = true;
						}
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
			cv.wait_for(lock, std::chrono::seconds(10), [&testDone] {return testDone;});
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

		EXPECT_EQ(receivedPing, true);
	}
	catch (...)
	{
		std::cerr << "unknown error in PingServerRespondsToClient" << std::endl;
		ADD_FAILURE();
	}
}
