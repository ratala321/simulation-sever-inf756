#ifndef SCS_RPC_DESERIALIZE
#define SCS_RPC_DESERIALIZE

#include "rpc_message_body.h"
#include "rpc_message_buffer.h"
#include "rpc_message_header.h"
#include "rpc_message_type.h"

namespace SCS::RPC
{

struct non_supported_message_type_for_deserialization {};

DeserializationResult deserialize(const ReadRawBuffer msgBuffer);
RpcMessageHeader deserializeHeader(const ReadRawBuffer headerBuffer) noexcept;
DeserializationResult deserializeBody(const RpcMessageHeader header, const ReadRawBuffer bodyBuffer);

size_t getBodyBufferSize(const RpcMessageType type);

template<RpcMessageType T>
DeserializationResult deserialize(const ReadRawBuffer toDeserialize);

template<>
DeserializationResult deserialize<RpcMessageType::idSync>(const ReadRawBuffer toDeserialize);

template<>
DeserializationResult deserialize<RpcMessageType::ping>(const ReadRawBuffer toDeserialize);

};

#endif // !SCS_RPC_DESERIALIZE
