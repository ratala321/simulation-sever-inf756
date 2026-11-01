#ifndef SCS_RPC_MESSAGE_BODY
#define SCS_RPC_MESSAGE_BODY

#include "rpc_message_buffer.h"
#include "rpc_message_type.h"
#include "../controller/client_session/client_id.h"

#include <array>
#include <cstdint>

namespace SCS::RPC
{

template<RpcMessageType T>
struct RpcMessageBody;

template<>
struct RpcMessageBody<RpcMessageType::idSync>
{
	SCS::ClientIdType assignedId;
};

template <template <RpcMessageType> class F>
struct conversion_tester
{
	template <RpcMessageType T>
	conversion_tester(const F<T>&);
};

template <class From, template <RpcMessageType> class To>
struct is_instance_of
{
	static constexpr bool value = std::is_convertible<From, conversion_tester<To>>::value;
};

};

#endif // !SCS_RPC_MESSAGE_BODY
