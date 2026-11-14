#ifndef SCS_MSG_PROCESSOR_ID_SYNC
#define SCS_MSG_PROCESSOR_ID_SYNC

#include "client_id.h"
#include "network_definitions.h"
#include "rpc_message_body.h"

namespace SCS::RPC::Processor
{
	void processRpcMessage(const SCS::ClientIdType clientId, SCS::SocketTCP& socket, const IdSyncMessageBody& toProcess);
};

#endif // !SCS_MSG_PROCESSOR_ID_SYNC