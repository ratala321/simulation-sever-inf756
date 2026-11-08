#ifndef SCS_MSG_PROCESSOR_ID_SYNC
#define SCS_MSG_PROCESSOR_ID_SYNC

#include "client_session.h"
#include "rpc_message_body.h"

namespace SCS::RPC::Processor
{
	void processRpcMessage(const ClientSession& session, const IdSyncMessageBody& toProcess);
};

#endif // !SCS_MSG_PROCESSOR_ID_SYNC