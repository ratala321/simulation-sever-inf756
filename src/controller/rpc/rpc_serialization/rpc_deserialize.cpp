#include "rpc_deserialize.h"

#include "serialization.h"

namespace SCS::RPC
{

DeserializationResult deserialize(const ReadRawBuffer msgBuffer)
{
	RpcMessageHeader header = deserializeHeader(msgBuffer);

	return deserializeBody(header, msgBuffer + sizeof(header));
}

RpcMessageHeader deserializeHeader(const ReadRawBuffer headerBuffer) noexcept
{
	std::underlying_type_t<SCS::RPC::RpcMessageType> nonEnumType;
	SCS::Serialization::deserializeRaw(headerBuffer, nonEnumType);

	return  { .type = static_cast<SCS::RPC::RpcMessageType>(nonEnumType) };
}

size_t getBodyBufferSize(const RpcMessageType type)
{
	switch (type)
	{
	case RpcMessageType::idSync:
		return sizeof(RpcMessageBody<RpcMessageType::idSync>);
	case RpcMessageType::ping:
		return sizeof(RpcMessageBody<RpcMessageType::ping>);
	}

	throw non_supported_message_type_for_deserialization{};
}

DeserializationResult deserializeBody(const RpcMessageHeader header, const ReadRawBuffer bodyBuffer)
{
	switch (header.type)
	{
	case RpcMessageType::idSync:
		return deserialize<RpcMessageType::idSync>(bodyBuffer);
	case RpcMessageType::ping:
		return deserialize<RpcMessageType::ping>(bodyBuffer);
	}

	throw non_supported_message_type_for_deserialization{};
}

template<>
DeserializationResult deserialize<RpcMessageType::idSync>(const ReadRawBuffer toDeserialize)
{
	SCS::ClientIdType clientId;
	SCS::Serialization::deserializeRaw(toDeserialize, clientId);

	return RpcMessageBody<RpcMessageType::idSync>{.assignedId = clientId};
}

template<>
DeserializationResult deserialize<RpcMessageType::ping>(const ReadRawBuffer toDeserialize)
{
	return RpcMessageBody<RpcMessageType::ping>{};
}

};
