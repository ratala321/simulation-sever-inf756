#include "client_session.h"

#include "../../rpc_message/rpc_message.h"
#include "../../rpc_message/rpc_message_trait.h"
#include "../../rpc_message/rpc_serialize.h"
#include "../../rpc_message/rpc_deserialize.h"

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
			SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::idSync> body;
			SCS::RPC::WriteBuffer data = SCS::RPC::serialize(body);
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

void SCS::ClientSession::listen()
{
    asio::co_spawn(
		socket.get_executor(),
		[this] -> asio::awaitable<void>
		{
			SCS::RPC::ReadBuffer buffer;
			buffer.reserve(SCS::RPC::maxReadingBufferSize);
			co_await asio::async_read(socket, asio::dynamic_buffer(buffer, buffer.capacity()));
			// get body type variant
			SCS::RPC::MessageTraitVariant msgVariant{ SCS::RPC::IdSyncMessageType{} };
			
			auto r = SCS::RPC::deserialize(msgVariant, buffer);
			SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::idSync> msg = r.unsafeGet<SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::idSync>>();
			// Do something with read message.
			/*
				1. Send to a queue with client info
			*/
			// How to go in listen mode again ?
			/*
				1. ...
			*/
		},
		[this](std::exception_ptr e)
		{
			try
			{
				if (e) { std::rethrow_exception(e); }
			}
			catch(...)
			{
				spdlog::error("Can't listen to server via client session with id : {}", clientId);
				throw;
			}
		}
	);
}
