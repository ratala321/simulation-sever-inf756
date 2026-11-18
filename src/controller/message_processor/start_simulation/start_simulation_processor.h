#ifndef SCS_MSG_PROCESSOR_START_SIMULATION
#define SCS_MSG_PROCESSOR_START_SIMULATION

#include "client_id.h"
#include "network_definitions.h"
#include "socket_owner.h"
#include "rpc_message_body.h"

#include <asio/awaitable.hpp>

#include <memory>

namespace SCS::RPC::Processor
{
	asio::awaitable<void> processRpcMessage(
		std::shared_ptr<SCS::SocketOwner> client,
		const SCS::ClientIdType clientId,
		SCS::SocketTCP& socket,
		const StartSimulationRequestBody& toProcess
	);
};

#endif // !SCS_MSG_PROCESSOR_START_SIMULATION