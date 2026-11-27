#ifndef SCS_RPC_SERIALIZE
#define SCS_RPC_SERIALIZE

#include "rpc_message_body.h"
#include "rpc_message_buffer.h"
#include "rpc_message_type.h"

#include <concepts>

namespace SCS::RPC
{

template <template <RpcMessageType> class F>
struct conversion_tester
{
	template <RpcMessageType T>
	conversion_tester(const F<T>&);
};

template <class From, template <RpcMessageType> class To>
struct is_instance_of
{
	static constexpr bool value = std::is_convertible<From, SCS::RPC::conversion_tester<To>>::value;
};

template <class T>
concept RequestOrResponseBody = requires (T t)
{
	SCS::RPC::is_instance_of<T, MessageRequestBody>::value || SCS::RPC::is_instance_of<T, MessageResponseBody>::value;
};

template<RequestOrResponseBody T>
WriteBuffer serialize(const T&)
{
	static_assert(false, "non existing serialization for MessageResponseBody of type provided");
	return {};
}


template<>
WriteBuffer serialize(const IdSyncMessageBody& toSerialize);

template<>
WriteBuffer serialize(const PingMessageBody& toSerialize);

template<>
WriteBuffer serialize(const StartSimulationResponseBody& toSerialize);

};

#endif // !SCS_RPC_SERIALIZE
