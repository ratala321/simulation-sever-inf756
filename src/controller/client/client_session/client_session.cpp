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
	: clientId{ ++clientIdCounter }, socket{ std::move(socket) }, channel{ socket.get_executor(), 128 }
{
}

void SCS::ClientSession::start()
{
	asio::co_spawn(
		socket.get_executor(),
		[self = shared_from_this()]() -> asio::awaitable<void>
		{
			while (self->socket.is_open())
			{
				SCS::RPC::DeserializationResult dr = co_await self->channel.async_receive(asio::use_awaitable);

				co_await SCS::MessageDispatcher::registerMessage({ .client = self, .clientId = self->clientId, .socket = self->socket, .message = dr });
			}
		},
		[self = shared_from_this()](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch (std::exception& ex)
			{
				spdlog::error("Channel of client session `{}` had an error : `{}`", self->clientId, ex.what());
				// TODO SCS-28: close this session
			}
			catch (...)
			{
				spdlog::error("Channel of client session `{}` had an error.", self->clientId);
				// TODO SCS-28: close this session
			}
		}
	);

	SCS::RPC::MessageRequestBody<SCS::RPC::RpcMessageType::idSync> body{ clientId };
	SCS::RPC::WriteBuffer buffer = SCS::RPC::serialize(body);
	asio::write(socket, asio::buffer(buffer));
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
					bodyBuffer.resize(bodyBufferSize);

					co_await asio::async_read(self->socket, asio::buffer(bodyBuffer));
				}
				SCS::RPC::DeserializationResult dr = SCS::RPC::deserializeBody(header, bodyBuffer.data());

				self->channel.try_send(asio::error_code{}, std::move(dr));
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
