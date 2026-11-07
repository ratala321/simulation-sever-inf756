#include "rpc_serialize.h"

#include "serialization.h"

namespace SCS::RPC
{

template<>
RpcMessageBuffer serialize(const IdSyncMessageBody& toSerialize)
{
	using RawEnumType = std::underlying_type_t<RpcMessageType>;

	static constexpr size_t sizeOfBuffer = sizeof(RpcMessageType::idSync) + sizeof(IdSyncMessageBody);
	uint8_t buffer[sizeOfBuffer];

	SCS::Serialization::serializeRaw(buffer, static_cast<RawEnumType>(RpcMessageType::idSync));
	SCS::Serialization::serializeRaw(buffer, toSerialize.assignedId);

	return { .buffer = buffer, .sizeOfBuffer = sizeOfBuffer };
}

template<>
RpcMessageBuffer serialize(const PingMessageBody& toSerialize)
{
	return RpcMessageBuffer{ .buffer = nullptr, .sizeOfBuffer = 0 };
}

};
