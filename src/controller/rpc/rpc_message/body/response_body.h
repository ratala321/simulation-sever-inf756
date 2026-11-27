#ifndef SCS_RPC_RESPONSE_BODY
#define SCS_RPC_RESPONSE_BODY

#include "rpc_message_type.h"
#include "client_id.h"
#include "simulation_definitions.h"

#include <cstdint>

namespace SCS::RPC
{
	template<RpcMessageType T>
	struct MessageResponseBody;

	template<>
	struct MessageResponseBody<RpcMessageType::startSimulation>
	{
		SCS::SimulationId simulationId;
		// network format of boolean. 1 (true) means start simulation had no error. 0 (false) means simulation wasn't able to start.
		uint8_t isStarted;
	};
	using StartSimulationResponseBody = MessageResponseBody<RpcMessageType::startSimulation>;
};

#endif // !SCS_RPC_RESPONSE_BODY
