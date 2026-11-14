#include "id_sync_processor.h"

#include <spdlog/spdlog.h>

void SCS::RPC::Processor::processRpcMessage(const SCS::ClientIdType clientId, SCS::SocketTCP& socket, const SCS::RPC::IdSyncMessageBody& toProcess)
{
	spdlog::info("receive idSync with assignedId `{}` for client session `{}`", toProcess.assignedId, clientId);
}
