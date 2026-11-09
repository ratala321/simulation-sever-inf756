#ifndef SCS_CLIENT_SESSION
#define SCS_CLIENT_SESSION

#include "client_id.h"

#include <asio/ip/tcp.hpp>

#include <atomic>
#include <cstdint>

namespace SCS
{

class ClientSession
{
public:
	using SocketTCP = asio::ip::tcp::socket;

	explicit ClientSession(SocketTCP socket) noexcept;
	ClientSession(const ClientSession&) = delete;
	ClientSession& operator=(const ClientSession&) = delete;
	ClientSession(ClientSession&& other) noexcept = default;
	ClientSession& operator=(ClientSession&& other) noexcept = default;

	void start();
	void listen();

	SocketTCP& connexion() noexcept { return socket; }
	constexpr SCS::ClientIdType id() const noexcept { return clientId; }

private:
	constinit static inline std::atomic<SCS::ClientIdType> clientIdCounter{ 0 };

	SocketTCP socket;
	const SCS::ClientIdType clientId;
};

};

#endif // !SCS_CLIENT_SESSION
