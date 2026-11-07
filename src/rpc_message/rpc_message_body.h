#ifndef SCS_RPC_MESSAGE_BODY
#define SCS_RPC_MESSAGE_BODY

#include "rpc_message_buffer.h"
#include "rpc_message_type.h"
#include "serialization/serialization.h"
#include "../controller/client_session/client_id.h"

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

template<RpcMessageType T>
RpcMessageBuffer serialize(const RpcMessageBody<T>&)
{
	static_assert(false, "non existing serialization for RpcMessageBody of type provided");
	return {};
}

template<>
RpcMessageBuffer serialize(const RpcMessageBody<RpcMessageType::idSync>& toSerialize)
{
	using RawEnumType = std::underlying_type_t<RpcMessageType>;

	constexpr size_t sizeOfBuffer = sizeof(RpcMessageType::idSync) + sizeof(toSerialize.assignedId);
	uint8_t buffer[sizeOfBuffer];

	SCS::Serialization::serializeRaw(buffer, static_cast<RawEnumType>(RpcMessageType::idSync));
	SCS::Serialization::serializeRaw(buffer, toSerialize.assignedId);

	return { .buffer = buffer, .sizeOfBuffer = sizeOfBuffer};
}

};

#endif // !SCS_RPC_MESSAGE_BODY
