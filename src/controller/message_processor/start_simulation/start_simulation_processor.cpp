#include "start_simulation_processor.h"

#include "rpc_message_buffer.h"
#include "rpc_serialize.h"
#include "simulation_manager.h"

#include <asio/buffer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/write.hpp>
#include <asio/cancel_after.hpp>

#include <spdlog/spdlog.h>

#include <optional>

namespace
{

std::optional<SCS::SimulationId> startSimulationSession()
{
	try
	{
		return SCS::SimulationManager::instance().addSimulation();
	}
	catch (...)
	{
		return std::nullopt;
	}
}

asio::awaitable<void> sendSuccessToClient(const SCS::ClientIdType clientId, SCS::SocketTCP& socket, const SCS::SimulationId simulationId)
{
	spdlog::info("Sucessfully started simulation session `{}` for client session `{}`", simulationId, clientId);

	SCS::RPC::StartSimulationResponseBody body{ .simulationId = simulationId, .isStarted = 1 };
	SCS::RPC::WriteBuffer buffer = SCS::RPC::serialize(body);

	co_await asio::async_write(socket, asio::buffer(buffer), asio::cancel_after(std::chrono::seconds(5)));

	spdlog::info("Sent ping simulation id `{}` to client session `{}`", simulationId, clientId);
}

asio::awaitable<void> sendFailureToClient(const SCS::ClientIdType clientId, SCS::SocketTCP& socket)
{
	spdlog::warn("Could not start simulation for client session `{}`", clientId);

	SCS::RPC::StartSimulationResponseBody body{ .simulationId = 0, .isStarted = 0 };
	SCS::RPC::WriteBuffer buffer = SCS::RPC::serialize(body);

	co_await asio::async_write(socket, asio::buffer(buffer), asio::cancel_after(std::chrono::seconds(5)));

	spdlog::info("Sent could not start simulation warning to client session `{}`", clientId);
}

};

asio::awaitable<void> SCS::RPC::Processor::processRpcMessage(
	std::shared_ptr<SCS::SocketOwner> client,
	const SCS::ClientIdType clientId,
	SCS::SocketTCP& socket,
	const SCS::RPC::StartSimulationRequestBody& toProcess)
{
	spdlog::info("receive start simulation for client session `{}`", clientId);

	// TODO SCS-32: process json of world state and ruleset.

	const auto simulationId = startSimulationSession();
	if (simulationId)
	{
		co_await sendSuccessToClient(clientId, socket, *simulationId);
	}
	else
	{
		co_await sendFailureToClient(clientId, socket);
	}
}
