#ifndef SCS_SIMULATION_MANAGER
#define SCS_SIMULATION_MANAGER

#include "simulation_definitions.h"
#include "simulation_session.h"

#include <mutex>
#include <vector>

namespace SCS
{

class SimulationManager
{
private:
	SimulationManager();
	~SimulationManager() = default;

public:
	SimulationManager(const SimulationManager&) = delete;
	SimulationManager(SimulationManager&&) = delete;
	SimulationManager& operator=(const SimulationManager&) = delete;
	SimulationManager& operator=(SimulationManager&&) = delete;

	static SimulationManager& instance()
	{
		static SimulationManager instance;
		return instance;
	}

	SimulationId addSimulation();

private:
	constinit static inline SimulationId nextSimulationId = 0;

	std::mutex mutateSimulationsLock;
	std::vector<SimulationSession> runningSimulations;
	std::thread simulationLoopThread;
};

};

#endif // !SCS_SIMULATION_MANAGER