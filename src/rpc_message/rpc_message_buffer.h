#ifndef SCS_RPC_MESSAGE_BUFFER
#define SCS_RPC_MESSAGE_BUFFER

#include <cstdint>

namespace SCS::RPC
{

struct RpcMessageBuffer
{
	uint8_t* buffer;
	size_t sizeOfBuffer;
};

};

#endif // !SCS_RPC_MESSAGE_BUFFER