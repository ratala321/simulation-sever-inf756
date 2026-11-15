#ifndef SCS_MSG_PROCESSOR_PING
#define SCS_MSG_PROCESSOR_PING

#include "client_id.h"
#include "network_definitions.h"
#include "socket_owner.h"
#include "rpc_message_body.h"

#include <memory>

namespace SCS::RPC::Processor
{
	void processRpcMessage(
		std::shared_ptr<SCS::SocketOwner> client,
		const SCS::ClientIdType clientId,
		SCS::SocketTCP& socket,
		const PingMessageBody& toProcess
	);
};

#endif // !SCS_MSG_PROCESSOR_PING