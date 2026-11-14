#ifndef SCS_MESSAGE_DISPATCHER
#define SCS_MESSAGE_DISPATCHER

#include "client_id.h"
#include "network_definitions.h"
#include "rpc_message_body.h"

namespace SCS::MessageDispatcher
{

struct MessageData
{
	ClientIdType clientId;
	SCS::SocketTCP& socket;
	const SCS::RPC::DeserializationResult& message;
};

void registerMessage(MessageData toRegister);

};

#endif // !SCS_MESSAGE_DISPATCHER