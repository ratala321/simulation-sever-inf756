#ifndef SCS_RPC_MESSAGE_TYPE
#define SCS_RPC_MESSAGE_TYPE

#include <cstdint>

namespace SCS
{

enum class RpcMessageType : uint16_t
{
	// Sent to client upon connexion, to indentify itself with the server.
	idSync = 0,
};

};

#endif // !SCS_RPC_MESSAGE_TYPE
