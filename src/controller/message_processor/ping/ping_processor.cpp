#include "ping_processor.h"

#include "rpc_message_buffer.h"
#include "rpc_serialize.h"

#include <asio/buffer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/write.hpp>
#include <asio/cancel_after.hpp>

#include <spdlog/spdlog.h>

asio::awaitable<void> SCS::RPC::Processor::processRpcMessage(
	std::shared_ptr<SCS::SocketOwner> client,
	const SCS::ClientIdType clientId,
	SCS::SocketTCP& socket,
	const SCS::RPC::PingMessageBody& toProcess)
{
	spdlog::info("receive ping for client session `{}`", clientId);

	SCS::RPC::MessageRequestBody<SCS::RPC::RpcMessageType::ping> body{};
	SCS::RPC::WriteBuffer buffer = SCS::RPC::serialize(body);

	co_await asio::async_write(socket, asio::buffer(buffer), asio::cancel_after(std::chrono::seconds(5)));

	spdlog::info("Sent ping back to client session `{}`", clientId);
}
