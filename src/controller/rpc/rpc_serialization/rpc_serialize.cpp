#include "rpc_serialize.h"

#include "serialization.h"

namespace SCS::RPC
{

template<>
WriteBuffer serialize(const IdSyncMessageBody& toSerialize)
{
	using RawEnumType = std::underlying_type_t<RpcMessageType>;

	static constexpr size_t sizeOfBuffer = sizeof(RpcMessageType::idSync) + sizeof(IdSyncMessageBody);
	uint8_t buffer[sizeOfBuffer];

	auto temp = SCS::Serialization::serializeRaw(buffer, static_cast<RawEnumType>(RpcMessageType::idSync));
	SCS::Serialization::serializeRaw(temp, toSerialize.assignedId);

	return { buffer, buffer + sizeOfBuffer };
}

template<>
WriteBuffer serialize(const PingMessageBody& toSerialize)
{
	using RawEnumType = std::underlying_type_t<RpcMessageType>;

	static constexpr size_t sizeOfBuffer = sizeof(RpcMessageType::ping);
	uint8_t buffer[sizeOfBuffer];

	SCS::Serialization::serializeRaw(buffer, static_cast<RawEnumType>(RpcMessageType::ping));

	return { buffer, buffer + sizeOfBuffer };
}

template<>
WriteBuffer serialize(const StartSimulationResponseBody& toSerialize)
{
	using RawEnumType = std::underlying_type_t<RpcMessageType>;

	static constexpr size_t sizeOfBuffer =
		sizeof(RpcMessageType::startSimulation) + sizeof(StartSimulationResponseBody::isStarted) + sizeof(StartSimulationResponseBody::simulationId);
	uint8_t buffer[sizeOfBuffer];

	auto temp = SCS::Serialization::serializeRaw(buffer, static_cast<RawEnumType>(RpcMessageType::startSimulation));
	temp = SCS::Serialization::serializeRaw(temp, toSerialize.simulationId);
	SCS::Serialization::serializeRaw(temp, toSerialize.isStarted);

	return { buffer, buffer + sizeOfBuffer };
}

};
