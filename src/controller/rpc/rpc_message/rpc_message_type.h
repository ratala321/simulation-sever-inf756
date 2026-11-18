#ifndef SCS_RPC_MESSAGE_TYPE
#define SCS_RPC_MESSAGE_TYPE

#include <cstdint>

namespace SCS::RPC
{

enum class RpcMessageType : uint16_t
{
	// Sent to client upon connexion, to indentify itself with the server.
	idSync = 0,
	// Sent from client to signal the server. The server then signal back to the client.
	ping = 1,
	// Sent from client to start a simulation. The configuration of the simulation is specified in the body.
	startSimulation = 2,
};

};

#endif // !SCS_RPC_MESSAGE_TYPE
