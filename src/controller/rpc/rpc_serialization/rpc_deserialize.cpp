#include "rpc_deserialize.h"

#include "serialization.h"

namespace SCS::RPC
{

DeserializationResult deserialize(const ReadBuffer& toDeserialize)
{
	std::underlying_type_t<SCS::RPC::RpcMessageType> msgType;
	SCS::Serialization::deserializeRaw(toDeserialize.data(), msgType);

	switch (static_cast<SCS::RPC::RpcMessageType>(msgType))
	{
	case RpcMessageType::idSync:
		return deserialize<RpcMessageType::idSync>(toDeserialize);
	}

	throw non_supported_message_type_for_deserialization{};
}

template<>
DeserializationResult deserialize<RpcMessageType::idSync>(const ReadBuffer& toDeserialize)
{
	const uint8_t* data = toDeserialize.data();
	data += sizeof(SCS::RPC::RpcMessageType);

	SCS::ClientIdType clientId;
	SCS::Serialization::deserializeRaw(data, clientId);

	return RpcMessageBody<RpcMessageType::idSync>{.assignedId = clientId};
}

};
