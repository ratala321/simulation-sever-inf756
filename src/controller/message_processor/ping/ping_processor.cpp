#include "ping_processor.h"

#include "rpc_message_buffer.h"
#include "rpc_serialize.h"

#include <asio/buffer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/write.hpp>
#include <asio/cancel_after.hpp>

#include <spdlog/spdlog.h>

void SCS::RPC::Processor::processRpcMessage(const SCS::ClientIdType clientId, SCS::SocketTCP& socket, const SCS::RPC::PingMessageBody& toProcess)
{
	spdlog::info("receive ping for client session `{}`", clientId);

	asio::co_spawn(
		socket.get_executor(),
		[clientId, &socket] -> asio::awaitable<void>
		{
			SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::ping> body{};
			SCS::RPC::WriteBuffer data = SCS::RPC::serialize(body);
			co_await asio::async_write(socket, asio::buffer(data.buffer, data.sizeOfBuffer), asio::cancel_after(std::chrono::seconds(5)));
			spdlog::info("Sent ping back to client session `{}`", clientId);
		},
		[clientId](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch (...)
			{
				spdlog::error("Can't ping back client session `{}`", clientId);
				throw;
			}
		}
	);
}
