#ifndef SCS_RPC_MESSAGE_BUFFER
#define SCS_RPC_MESSAGE_BUFFER

#include <cstdint>
#include <vector>

namespace SCS::RPC
{

using ReadBuffer = std::vector<uint8_t>;
using WriteBuffer = struct RpcMessageBuffer;

constexpr size_t maxReadingBufferSize = 1024;

struct RpcMessageBuffer
{
	uint8_t* buffer;
	size_t sizeOfBuffer;
};

};

#endif // !SCS_RPC_MESSAGE_BUFFER