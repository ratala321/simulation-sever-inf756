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

struct MockupClient
{
	// TODO
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

	std::thread tserver{ [&m, &cv, &testDone]()
		{
			const char* argv[2] = {
				"127.0.0.1",
				"8080"
			};

			run(2, const_cast<char**>(argv));
		}
	};

	std::thread tclient{
	[&m, &cv, &testDone, &receivedIdSync]
	{
		const char* argv[2] = {
			"127.0.0.1",
			"8080"
		};

		asio::io_context io_context;

		SCS::SocketTCP socket{ io_context };

		asio::ip::tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(argv[0], argv[1]);
		asio::connect(socket, endpoints);

		asio::co_spawn(
			socket.get_executor(),
			[&socket, &cv, &m, &testDone, &receivedIdSync] -> asio::awaitable<void>
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

				SCS::RPC::DeserializationResult dr = SCS::RPC::deserializeBody(header, buffer.data());

				std::visit(
					SCS::Lang::Visitor{
						[](auto&) { },
						[&receivedIdSync](SCS::RPC::IdSyncMessageBody&) { receivedIdSync = true; },
						[](SCS::RPC::PingMessageBody&) { },
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
					throw;
				}
			}
		);
		asio::signal_set signals(io_context, SIGINT, SIGTERM);
		signals.async_wait([&](auto, auto)
			{
				io_context.stop();
			}
		);
		io_context.run();
	}
};

	{
		std::unique_lock lock{ m };
		cv.wait(lock, [&testDone] {return testDone;});
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
		std::cerr << "unknown error" << std::endl;
		ADD_FAILURE();
	}
}
