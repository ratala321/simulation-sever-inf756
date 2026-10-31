#include "client_session.h"

#include "../../rpc_message/rpc_message.h"

#include <asio/awaitable.hpp>
#include <asio/cancel_after.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/write.hpp>

#include <spdlog/spdlog.h>

SCS::ClientSession::ClientSession(SocketTCP socket) noexcept
	: socket{ std::move(socket) }, clientId{ ++clientIdCounter }
{
}

void SCS::ClientSession::start()
{
    asio::co_spawn(
		socket.get_executor(),
		[this] -> asio::awaitable<void>
		{
			SCS::RpcMessageBody<SCS::RpcMessageType::idSync> body;
			SCS::RpcMessageBuffer data = SCS::serialize(body);
			co_await asio::async_write(socket, asio::buffer(data.buffer, data.sizeOfBuffer), asio::cancel_after(std::chrono::seconds(5)));
		},
		[](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch(...)
			{
				spdlog::error("Can't properly start client session");
				throw;
			}
		}
	);
}
