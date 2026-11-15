#include "controller.h"

#include <asio/use_awaitable.hpp>

#include <spdlog/spdlog.h>

asio::ip::port_type SCS::ControllerInitParams::evaluatePortNumber(const int argc, char* argv[]) const
{
	if (argc == 1)
	{
		spdlog::info("Port 80 will be used by default.\n If you want to specify a particular port, call the program with an argument.\n\t`simulation_server.exe 201` use 201 as a port number.");
		return 80;
	}

	return std::stoi(argv[1]);
}

SCS::Controller::Controller(const ControllerInitParams init)
	: acceptor{ init.ioContext, init.endpoint }
{
}

asio::awaitable<void> SCS::Controller::start()
{
	while (true)
	{
		asio::ip::tcp::socket newClientConnexion = co_await acceptor.async_accept(asio::use_awaitable);
		asio::ip::tcp::no_delay option(true);
		newClientConnexion.set_option(option);

		auto& session = activeClientSessions.emplace_back(std::make_shared<ClientSession>(std::move(newClientConnexion)));
		session->start();
		session->listen();
	}
}
