#ifndef SCS_RPC_SERIALIZE
#define SCS_RPC_SERIALIZE

#include "rpc_message_body.h"
#include "rpc_message_buffer.h"
#include "rpc_message_type.h"

namespace SCS::RPC
{

template<RpcMessageType T>
RpcMessageBuffer serialize(const RpcMessageBody<T>&)
{
	static_assert(false, "non existing serialization for RpcMessageBody of type provided");
	return {};
}


template<>
RpcMessageBuffer serialize(const IdSyncMessageBody& toSerialize);

template<>
RpcMessageBuffer serialize(const PingMessageBody& toSerialize);

};

#endif // !SCS_RPC_SERIALIZE
