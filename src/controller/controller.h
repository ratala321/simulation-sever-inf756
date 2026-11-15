#ifndef SCS_CONTROLLER
#define SCS_CONTROLLER

#include "client_session.h"

#include <asio/awaitable.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

#include <cstdint>

namespace SCS
{

struct ControllerInitParams
{
	ControllerInitParams(const int argc, char* argv[], asio::io_context& ioContext)
		: endpoint{ asio::ip::tcp::v4(), evaluatePortNumber(argc, argv) }, ioContext{ ioContext }
	{}

private:
	asio::ip::port_type evaluatePortNumber(const int argc, char* argv[]) const;

public:
	asio::ip::tcp::endpoint endpoint;
	asio::io_context& ioContext;
};

class Controller
{
public:
	using Acceptor = asio::ip::tcp::acceptor;

	Controller(const ControllerInitParams init);

	asio::awaitable<void> start();

private:
	std::vector<ClientSession> activeClientSessions;
	Acceptor acceptor;
};

};

#endif // SCS_CONTROLLER
