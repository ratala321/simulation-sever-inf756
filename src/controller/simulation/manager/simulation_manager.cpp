#include "simulation_manager.h"

#include "simulation_loop_runner.h"

#include <thread>

namespace SCS
{

SimulationManager::SimulationManager()
	: simulationLoopThread{ SimulationLoopRunner{ runningSimulations, mutateSimulationsLock } }
{
}

SimulationId SimulationManager::addSimulation()
{
	std::scoped_lock _{ mutateSimulationsLock };

	runningSimulations.emplace_back();

	return nextSimulationId++;
}

};