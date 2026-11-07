#ifndef SCS_RPC_DESERIALIZE
#define SCS_RPC_DESERIALIZE

#include "rpc_message_body.h"
#include "rpc_message_buffer.h"
#include "rpc_message_type.h"

namespace SCS::RPC
{

struct non_supported_message_type_for_deserialization {};

DeserializationResult deserialize(const ReadBuffer& toDeserialize);

template<RpcMessageType T>
DeserializationResult deserialize(const ReadBuffer& toDeserialize);

template<>
DeserializationResult deserialize<RpcMessageType::idSync>(const ReadBuffer& toDeserialize);

};

#endif // !SCS_RPC_DESERIALIZE
