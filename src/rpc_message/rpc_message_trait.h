#ifndef SCS_RPC_MESSAGE_TRAIT
#define SCS_RPC_MESSAGE_TRAIT

#include "rpc_message_type.h"

#include <variant>

namespace SCS::RPC
{

struct InvalidMessageType {};
struct IdSyncMessageType {};

using MessageTraitVariant = std::variant<InvalidMessageType, IdSyncMessageType>;

};

#endif // !SCS_RPC_MESSAGE_TRAIT
