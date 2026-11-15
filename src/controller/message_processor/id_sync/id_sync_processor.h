#ifndef SCS_MSG_PROCESSOR_ID_SYNC
#define SCS_MSG_PROCESSOR_ID_SYNC

#include "client_id.h"
#include "network_definitions.h"
#include "rpc_message_body.h"
#include "socket_owner.h"

#include <memory>

namespace SCS::RPC::Processor
{
	void processRpcMessage(
		std::shared_ptr <SCS::SocketOwner> client,
		const SCS::ClientIdType clientId,
		SCS::SocketTCP& socket,
		const IdSyncMessageBody& toProcess
	);
};

#endif // !SCS_MSG_PROCESSOR_ID_SYNC