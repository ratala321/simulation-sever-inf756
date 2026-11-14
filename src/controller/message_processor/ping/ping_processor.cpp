#include "ping_processor.h"

#include <spdlog/spdlog.h>

void SCS::RPC::Processor::processRpcMessage(const SCS::ClientIdType clientId, SCS::SocketTCP& socket, const SCS::RPC::PingMessageBody& toProcess)
{
	spdlog::info("receive ping for client session `{}`", clientId);

	// TODO SCS-22 : ping back client
}
