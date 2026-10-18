#include "src/controller/controller.h"

#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>

#include <iostream>
#include <cstdint>
#include <string>

int run(int argc, char* argv[])
{
	using namespace asio::ip;

	asio::io_context ioMainContext;

	SCS::Controller controller{ SCS::ControllerInitParams{argc, argv, ioMainContext} };

	asio::co_spawn(
		ioMainContext,
		controller.start(),
		asio::detached
	);

    asio::signal_set signals(ioMainContext, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto){ ioMainContext.stop(); });

	ioMainContext.run();

	return 0;
}