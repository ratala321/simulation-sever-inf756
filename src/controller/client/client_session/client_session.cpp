#include "client_session.h"

#include "message_dispatcher.h"

#include "rpc_serialize.h"
#include "rpc_deserialize.h"

#include <asio/awaitable.hpp>
#include <asio/buffer.hpp>
#include <asio/cancel_after.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/read.hpp>
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
			SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::idSync> body{ clientId };
			SCS::RPC::WriteBuffer buffer = SCS::RPC::serialize(body);
			co_await asio::async_write(socket, asio::buffer(buffer), asio::cancel_after(std::chrono::seconds(5)));
		},
		[](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch (...)
			{
				spdlog::error("Can't properly start client session");
				throw;
			}
		}
	);
}

void SCS::ClientSession::listen()
{
	asio::co_spawn(
		socket.get_executor(),
		[this] -> asio::awaitable<void>
		{
			while (socket.is_open())
			{
				SCS::RPC::HeaderBuffer headerBuff;
				co_await asio::async_read(socket, asio::buffer(headerBuff));

				SCS::RPC::RpcMessageHeader header = SCS::RPC::deserializeHeader(headerBuff.data());

				const auto bodyBufferSize = SCS::RPC::getBodyBufferSize(header.type);
				SCS::RPC::ReadBuffer bodyBuffer;
				if (bodyBufferSize != 0)
				{
					bodyBuffer.reserve(bodyBufferSize);

					co_await asio::async_read(socket, asio::buffer(bodyBuffer));
				}
				SCS::RPC::DeserializationResult dr = SCS::RPC::deserializeBody(header, bodyBuffer.data());

				SCS::MessageDispatcher::registerMessage({ .clientId = clientId, .socket = socket, .message = dr });
			}
		},
		[this](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch (...)
			{
				spdlog::error("Can't listen to server via client session with id : {}", clientId);
				throw;
			}
		}
	);
}
