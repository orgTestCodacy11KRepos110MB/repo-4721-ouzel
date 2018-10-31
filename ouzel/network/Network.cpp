// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include <system_error>
#ifdef _WIN32
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  include <WinSock2.h>
#  include <WS2tcpip.h>
#else
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <errno.h>
#  include <poll.h>
#  include <netdb.h>
#  include <unistd.h>
#endif
#include "Network.hpp"
#include "Client.hpp"

namespace ouzel
{
    namespace network
    {
        Network::Network()
        {
#ifdef _WIN32
            WORD sockVersion = MAKEWORD(2, 2);
            WSADATA wsaData;
            int error = WSAStartup(sockVersion, &wsaData);
            if (error != 0)
                throw std::system_error(error, std::system_category(), "Failed to start WinSock failed");

            if (wsaData.wVersion != sockVersion)
                throw std::system_error(WSAEINVALIDPROVIDER, std::system_category(), "Incorrect WinSock version");
#endif
        }

        Network::~Network()
        {
#ifdef _WIN32
            if (endpoint != INVALID_SOCKET)
                closesocket(endpoint);

            WSACleanup();
#else
            if (endpoint != -1)
                close(endpoint);
#endif
        }

        void Network::getAddress(const std::string& address, uint32_t& result)
        {
            addrinfo* info;
            int ret = getaddrinfo(address.c_str(), nullptr, nullptr, &info);

            if (ret != 0)
            {
#ifdef _WIN32
                int error = WSAGetLastError();
#else
                int error = errno;
#endif
                throw std::system_error(error, std::system_category(), "Failed to get address info of " + address);
            }

            sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(info->ai_addr);
            result = ntohl(addr->sin_addr.s_addr);

            freeaddrinfo(info);
        }

        void Network::listen(const std::string& address, uint16_t port)
        {
        }

        void Network::connect(const std::string& address, uint16_t port)
        {
        }

        void Network::disconnect()
        {
        }
    } // namespace network
} // namespace ouzel
