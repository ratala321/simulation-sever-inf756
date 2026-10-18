#include "client_session.h"

SCS::ClientSession::ClientSession(SocketTCP socket)
	: socket{ std::move(socket) }
{
}
