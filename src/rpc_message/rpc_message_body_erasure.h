#ifndef SCS_RPC_MESSAGE_BODY_ERASURE
#define SCS_RPC_MESSAGE_BODY_ERASURE

#include "rpc_message_body.h"
#include "../lang/is_instance_of.h"

#include <concepts>
#include <utility>

namespace SCS::RPC
{

struct RpcMessageBodyErasure
{
	template<class T>
	T& unsafeGet()
	{
		return *static_cast<T*>(raw());
	}

protected:
	virtual void* raw() = 0;
};

template<class MB> requires SCS::RPC::is_instance_of <MB, SCS::RPC::RpcMessageBody>::value
struct RpcMessageBodyWrapper : public RpcMessageBodyErasure
{
protected:
	void* raw()
	{
		return &messageBody;
	}

private:
	MB messageBody;
};

};

#endif // !SCS_RPC_MESSAGE_BODY_ERASURE