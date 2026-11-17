#include "id_sync_processor.h"

#include <spdlog/spdlog.h>

asio::awaitable<void> SCS::RPC::Processor::processRpcMessage(
	std::shared_ptr <SCS::SocketOwner> client,
	const SCS::ClientIdType clientId,
	SCS::SocketTCP& socket,
	const SCS::RPC::IdSyncMessageBody& toProcess)
{
	spdlog::info("receive idSync with assignedId `{}` for client session `{}`", toProcess.assignedId, clientId);
	co_return;
}
