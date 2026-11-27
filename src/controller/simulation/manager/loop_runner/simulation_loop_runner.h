#ifndef SCS_SIMULATION_LOOP_RUNNER
#define SCS_SIMULATION_LOOP_RUNNER

#include "simulation_session.h"

#include <mutex>
#include <vector>

namespace SCS
{

struct SimulationLoopRunner
{
	void operator()();

	std::vector<SimulationSession>& simulations;
	std::mutex& mutateSimulationsLock;
};

};

#endif // !SCS_SIMULATION_LOOP_RUNNER
