#ifndef SCS_CLIENT_SESSION
#define SCS_CLIENT_SESSION

#include <asio/ip/tcp.hpp>

namespace SCS
{

class ClientSession
{
public:
	using SocketTCP = asio::ip::tcp::socket;

	ClientSession(SocketTCP socket);

private:
	SocketTCP socket;
};

};

#endif // !SCS_CLIENT_SESSION
