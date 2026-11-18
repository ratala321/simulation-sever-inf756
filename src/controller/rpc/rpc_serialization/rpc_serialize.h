#ifndef SCS_RPC_SERIALIZE
#define SCS_RPC_SERIALIZE

#include "rpc_message_body.h"
#include "rpc_message_buffer.h"
#include "rpc_message_type.h"

namespace SCS::RPC
{

template<RpcMessageType T>
WriteBuffer serialize(const MessageRequestBody<T>&)
{
	static_assert(false, "non existing serialization for MessageResponseBody of type provided");
	return {};
}


template<>
WriteBuffer serialize(const IdSyncMessageBody& toSerialize);

template<>
WriteBuffer serialize(const PingMessageBody& toSerialize);

};

#endif // !SCS_RPC_SERIALIZE
