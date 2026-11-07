#ifndef SCS_RPC_MESSAGE_BODY
#define SCS_RPC_MESSAGE_BODY

#include "rpc_message_buffer.h"
#include "rpc_message_type.h"
#include "client_id.h"

#include <array>
#include <cstdint>

namespace SCS::RPC
{

template<RpcMessageType T>
struct RpcMessageBody;

template<>
struct RpcMessageBody<RpcMessageType::idSync>
{
	SCS::ClientIdType assignedId;
};
using IdSyncMessageBody = RpcMessageBody<RpcMessageType::idSync>;

};

#endif // !SCS_RPC_MESSAGE_BODY
