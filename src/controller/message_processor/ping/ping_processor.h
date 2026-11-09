#ifndef SCS_MSG_PROCESSOR_PING
#define SCS_MSG_PROCESSOR_PING

#include "client_session.h"
#include "rpc_message_body.h"

namespace SCS
{
	void processRpcMessage(ClientSession& session, const SCS::RPC::PingMessageBody& toProcess);
};

#endif // !SCS_MSG_PROCESSOR_PING