#ifndef SCS_MSG_PROCESSOR_PING
#define SCS_MSG_PROCESSOR_PING

#include "client_id.h"
#include "network_definitions.h"
#include "rpc_message_body.h"

namespace SCS::RPC::Processor
{
	void processRpcMessage(const SCS::ClientIdType clientId, SCS::SocketTCP& socket, const PingMessageBody& toProcess);
};

#endif // !SCS_MSG_PROCESSOR_PING