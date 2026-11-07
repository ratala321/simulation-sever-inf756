#ifndef SCS_RPC_MESSAGE
#define SCS_RPC_MESSAGE

#include "rpc_message_type.h"
#include "rpc_message_body.h"

namespace SCS::RPC
{

template <RpcMessageType T>
struct RpcMessage
{
	RpcMessageType type;
	RpcMessageBody<T> body;
};

};

#endif // SCS_RPC_MESSAGE