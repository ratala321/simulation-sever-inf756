#include "client_session.h"

SCS::ClientSession::ClientSession(SocketTCP socket) noexcept
	: socket{ std::move(socket) }, clientId{ ++clientIdCounter }
{
}
