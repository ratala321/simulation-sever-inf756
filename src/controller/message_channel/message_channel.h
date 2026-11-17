#ifndef SCS_MESSAGE_CHANNEL
#define SCS_MESSAGE_CHANNEL

#include "rpc_message_body.h"

#include <asio/experimental/channel.hpp>

namespace SCS
{
	using MessageChannel = asio::experimental::channel<void(asio::error_code, SCS::RPC::DeserializationResult)>;
};

#endif // !SCS_MESSAGE_CHANNEL
