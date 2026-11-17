#include "message_dispatcher.h"

#include "visitor.h"

#include "id_sync_processor.h"
#include "ping_processor.h"

#include <variant>

namespace SCS::MessageDispatcher
{

asio::awaitable<void> registerMessage(MessageData toRegister)
{
	co_await std::visit(
		SCS::Lang::Visitor
		{
			[](const std::monostate) -> asio::awaitable<void>
			{
				co_return;
			},
			[&toRegister](const auto& msg) -> asio::awaitable<void>
			{
				// TODO SCS-29: send to message_write_queue or message_write_pump
				// thread or coroutine ? imo thread is better.
				co_await SCS::RPC::Processor::processRpcMessage(toRegister.client, toRegister.clientId, toRegister.socket, msg);
			},
		},
		toRegister.message
	);
}

};