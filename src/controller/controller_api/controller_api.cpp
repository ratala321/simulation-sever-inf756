#include "controller_api.h"

#include <spdlog/spdlog.h>

void SCS::ControllerAPI::rpc_ping() const noexcept
{
	spdlog::warn("===\nrpc ping is called !\n===");
}
