#ifndef SCS_RPC_REQUEST_BODY
#define SCS_RPC_REQUEST_BODY

#include "rpc_message_type.h"
#include "client_id.h"

#include <cstdint>
#include <variant>
#include <vector>

namespace SCS::RPC
{

template<RpcMessageType T>
struct MessageRequestBody;

template<>
struct MessageRequestBody<RpcMessageType::idSync>
{
	SCS::ClientIdType assignedId;
};
using IdSyncMessageBody = MessageRequestBody<RpcMessageType::idSync>;

template<>
struct MessageRequestBody<RpcMessageType::ping>
{
};
using PingMessageBody = MessageRequestBody<RpcMessageType::ping>;

template<>
struct MessageRequestBody<RpcMessageType::startSimulation>
{
	uint32_t sizeOfJson;
	std::vector<uint8_t> jsonRawBytes;
};
using StartSimulationRequestBody = MessageRequestBody<RpcMessageType::startSimulation>;

using DeserializationResult = std::variant<std::monostate, IdSyncMessageBody, PingMessageBody, StartSimulationRequestBody>;

};

#endif // !SCS_RPC_REQUEST_BODY
