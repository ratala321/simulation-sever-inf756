#include "ping_processor.h"

#include "rpc_message_buffer.h"
#include "rpc_serialize.h"

#include <spdlog/spdlog.h>
#include <asio.hpp>

void SCS::processRpcMessage(ClientSession& session, const SCS::RPC::PingMessageBody& toProcess)
{
	spdlog::info("receive ping for client session `{}`", session.id());

	SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::ping> msg{};
	SCS::RPC::WriteBuffer data = SCS::RPC::serialize(msg);

	asio::async_write(
		session.connexion(),
		asio::buffer(data.buffer, data.sizeOfBuffer),
		asio::cancel_after(
			std::chrono::seconds(5),
			[id = session.id()](const std::error_code& ec, std::size_t bytes_transferred)
			{
				if (ec == asio::error::operation_aborted)
				{
					spdlog::error("Couldn't ping client sesssion `{}`. The operation either timed out or cancelled");
				}
				else if (!ec)
				{
					spdlog::info("Successfully sent {} bytes to client session `{}`", bytes_transferred, id);
				}
				else
				{
					spdlog::error("Write to client session `{}` failed: {}", id, ec.message());
				}
			}
		)
	);
}
