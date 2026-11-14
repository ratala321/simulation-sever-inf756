#ifndef SCS_RPC_MESSAGE_HEADER
#define SCS_RPC_MESSAGE_HEADER

#include "rpc_message_type.h"
#include "rpc_message_buffer.h"

#include <type_traits>

namespace SCS::RPC
{

using HeaderBuffer = BufferBaseType[sizeof(RpcMessageType) / sizeof(BufferBaseType)];

struct RpcMessageHeader
{
	RpcMessageType type;
};

};

#endif // !SCS_RPC_MESSAGE_HEADER
