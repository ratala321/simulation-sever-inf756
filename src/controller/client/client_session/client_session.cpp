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
		[self = shared_from_this()] -> asio::awaitable<void>
		{
			try
			{
				SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::idSync> body{ self->clientId };
				SCS::RPC::WriteBuffer buffer = SCS::RPC::serialize(body);
				co_await asio::async_write(self->socket, asio::buffer(buffer), asio::cancel_after(std::chrono::seconds(5)));
			}
			catch (...)
			{
				spdlog::warn("client session `{}` start failed", self->clientId);
			}
		},
		[self = shared_from_this()](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch (...)
			{
				spdlog::error("Can't properly start client session `{}`");
				// TODO SCS-28: close this session
			}
		}
	);
}

void SCS::ClientSession::listen()
{
	asio::co_spawn(
		socket.get_executor(),
		[self = shared_from_this()] -> asio::awaitable<void>
		{
			// TODO SCS-28: break while when is pending deletion
			while (self->socket.is_open())
			{
				SCS::RPC::HeaderBuffer headerBuff;
				co_await asio::async_read(self->socket, asio::buffer(headerBuff));

				SCS::RPC::RpcMessageHeader header = SCS::RPC::deserializeHeader(headerBuff.data());

				const auto bodyBufferSize = SCS::RPC::getBodyBufferSize(header.type);
				SCS::RPC::ReadBuffer bodyBuffer;
				if (bodyBufferSize != 0)
				{
					bodyBuffer.reserve(bodyBufferSize);

					co_await asio::async_read(self->socket, asio::buffer(bodyBuffer, bodyBuffer.capacity()));
				}
				SCS::RPC::DeserializationResult dr = SCS::RPC::deserializeBody(header, bodyBuffer.data());

				SCS::MessageDispatcher::registerMessage({ .client = self, .clientId = self->clientId, .socket = self->socket, .message = dr });
			}
		},
		[self = shared_from_this()](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch (const std::exception& ex)
			{
				spdlog::error("Can't listen to server via client session with id `{}`: {}", self->clientId, ex.what());
				// TODO SCS-28: close this session
			}
			catch (...)
			{
				spdlog::error("Can't listen to server via client session with id : {}", self->clientId);
				// TODO SCS-28: close this session
			}
		}
	);
}
