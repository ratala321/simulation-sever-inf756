#include "simulation_loop_runner.h"

namespace SCS
{

void SimulationLoopRunner::operator()()
{
	while (true)
	{
		std::unique_lock ul(mutateSimulationsLock, std::try_to_lock);
		if (not ul.owns_lock()) { continue; }

		for (auto& s : simulations)
		{
			s.update();
		}
	}
}

};