#include "id_sync_processor.h"

#include <spdlog/spdlog.h>

void SCS::RPC::Processor::processRpcMessage(const ClientSession& session, const IdSyncMessageBody& toProcess)
{
	spdlog::info("receive idSync with assignedId `{}` for client session `{}`", toProcess.assignedId, session.id());
}
