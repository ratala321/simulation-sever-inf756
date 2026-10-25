#ifndef SCS_CLIENT_SESSION
#define SCS_CLIENT_SESSION

#include <asio/ip/tcp.hpp>

#include <atomic>
#include <cstdint>

namespace SCS
{

class ClientSession
{
public:
	using SocketTCP = asio::ip::tcp::socket;

	ClientSession(SocketTCP socket) noexcept;
	ClientSession(const ClientSession&) = delete;
	ClientSession& operator=(const ClientSession&) = delete;

private:
	constinit static inline std::atomic<uint64_t> clientIdCounter{ 0 };

	SocketTCP socket;
	uint64_t clientId;
};

};

#endif // !SCS_CLIENT_SESSION
