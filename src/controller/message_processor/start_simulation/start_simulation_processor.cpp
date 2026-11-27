#include "start_simulation_processor.h"

#include "rpc_message_buffer.h"
#include "rpc_serialize.h"
#include "simulation_manager.h"

#include <asio/buffer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/write.hpp>
#include <asio/cancel_after.hpp>

#include <spdlog/spdlog.h>

asio::awaitable<void> SCS::RPC::Processor::processRpcMessage(
	std::shared_ptr<SCS::SocketOwner> client,
	const SCS::ClientIdType clientId,
	SCS::SocketTCP& socket,
	const SCS::RPC::StartSimulationRequestBody& toProcess)
{
	spdlog::info("receive start simulation for client session `{}`", clientId);

	// TODO SCS-32: process json of world state and ruleset.

	const SimulationId simulationId = SCS::SimulationManager::instance().addSimulation();

	// TODO SCS-33: response back SimulationId to client;

	co_return;
}
