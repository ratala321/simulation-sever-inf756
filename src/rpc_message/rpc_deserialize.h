#ifndef SCS_RPC_DESERIALIZE
#define SCS_RPC_DESERIALIZE

#include "rpc_message_body.h"
#include "rpc_message_body_erasure.h"
#include "rpc_message_trait.h"
#include "serialization/serialization.h"
#include "../lang/visitor.h"

#include <variant>
#include <type_traits>

namespace SCS::RPC
{

template<class T>
auto deserialize()
{
	static_assert(false, "No deserialize method for provided MessageTraitVariants. You probably just added a type to the variant without adding the deserialization method for it.");
	return RpcMessageBodyWrapper<RpcMessageBody<RpcMessageType::idSync>>{};
}

template<>
auto deserialize<InvalidMessageType>()
{
	// TODO SCS-9: handle runtime error; maybe the data was corrupted
	return RpcMessageBodyWrapper<RpcMessageBody<RpcMessageType::idSync>>{};
}

template<>
auto deserialize<IdSyncMessageType>()
{
	//using RawEnumType = std::underlying_type_t<RpcMessageType>;

	//constexpr size_t sizeOfBuffer = sizeof(RpcMessageType::idSync) + sizeof(toDeserialize.assignedId);
	//uint8_t buffer[sizeOfBuffer];

	//SCS::Serialization::serializeRaw(buffer, static_cast<RawEnumType>(RpcMessageType::idSync));
	//SCS::Serialization::serializeRaw(buffer, toDeserialize.assignedId);

	//return { .buffer = buffer, .sizeOfBuffer = sizeOfBuffer};
	return RpcMessageBodyWrapper<RpcMessageBody<RpcMessageType::idSync>>{};
}

auto deserialize(const MessageTraitVariant mtv, const ReadBuffer& toDeserialize)
{
	const auto result = std::visit(
		SCS::Lang::Visitor{
			[](const auto messageType) { return deserialize<std::decay_t<decltype(messageType)>>(); }
		},
		mtv
	);

	return result;
}

};

#endif // !SCS_RPC_DESERIALIZE
