#include "message_dispatcher.h"

#include "visitor.h"

#include "id_sync_processor.h"
#include "ping_processor.h"

#include <variant>

namespace SCS::MessageDispatcher
{

void registerMessage(MessageData toRegister)
{
	std::visit(
		SCS::Lang::Visitor
		{
			[](const std::monostate) {},
			[&toRegister](const auto& msg)
			{
				// TODO SCS-29: send to message_write_queue or message_write_pump
				// thread or coroutine ? imo thread is better.
				SCS::RPC::Processor::processRpcMessage(toRegister.client, toRegister.clientId, toRegister.socket, msg);
			},
		},
		toRegister.message
	);
}

};