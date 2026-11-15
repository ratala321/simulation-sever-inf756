#ifndef SCS_RPC_MESSAGE_HEADER
#define SCS_RPC_MESSAGE_HEADER

#include "rpc_message_type.h"
#include "rpc_message_buffer.h"

#include <array>

namespace SCS::RPC
{

using HeaderBuffer = std::array<BufferBaseType, sizeof(RpcMessageType) / sizeof(BufferBaseType)>;

struct RpcMessageHeader
{
	RpcMessageType type;
};

};

#endif // !SCS_RPC_MESSAGE_HEADER
