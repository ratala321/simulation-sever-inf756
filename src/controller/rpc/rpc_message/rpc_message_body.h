#ifndef SCS_RPC_MESSAGE_BODY
#define SCS_RPC_MESSAGE_BODY

#include "rpc_message_type.h"
#include "client_id.h"

#include <array>
#include <cstdint>
#include <variant>

namespace SCS::RPC
{

template<RpcMessageType T>
struct RpcMessageBody;

template<>
struct RpcMessageBody<RpcMessageType::idSync>
{
	SCS::ClientIdType assignedId;
};
using IdSyncMessageBody = RpcMessageBody<RpcMessageType::idSync>;

using DeserializationResult = std::variant<std::monostate, IdSyncMessageBody>;

};

#endif // !SCS_RPC_MESSAGE_BODY
