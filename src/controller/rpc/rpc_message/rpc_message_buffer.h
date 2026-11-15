#ifndef SCS_RPC_MESSAGE_BUFFER
#define SCS_RPC_MESSAGE_BUFFER

#include <cstdint>
#include <vector>

namespace SCS::RPC
{

using BufferBaseType = uint8_t;
using ReadBuffer = std::vector<BufferBaseType>;
using ReadRawBuffer = BufferBaseType*;
using WriteBuffer = std::vector<BufferBaseType>;

constexpr size_t maxReadingBufferSize = 1024;

};

#endif // !SCS_RPC_MESSAGE_BUFFER