#ifndef SCS_MESSAGE_DISPATCHER
#define SCS_MESSAGE_DISPATCHER

#include "client_id.h"
#include "network_definitions.h"
#include "socket_owner.h"
#include "rpc_message_body.h"

#include <asio/awaitable.hpp>

#include <memory>

namespace SCS::MessageDispatcher
{

struct MessageData
{
	std::shared_ptr <SCS::SocketOwner> client;
	ClientIdType clientId;
	SCS::SocketTCP& socket;
	const SCS::RPC::DeserializationResult& message;
};

asio::awaitable<void> registerMessage(MessageData toRegister);

};

#endif // !SCS_MESSAGE_DISPATCHER