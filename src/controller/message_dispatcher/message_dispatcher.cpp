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
				SCS::RPC::Processor::processRpcMessage(toRegister.clientId, toRegister.socket, msg);
			},
		},
		toRegister.message
	);
}

};