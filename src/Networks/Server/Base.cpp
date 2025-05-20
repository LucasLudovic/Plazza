//
// EPITECH PROJECT, 2025
// Server
// File description:
// Base functions for server
//

#include "NetworkError.hpp"
#include "Server.hpp"
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

using plazza::NetworkError;

Network::Server::Server()
{
    this->_fd = -1;
}

Network::Server::~Server()
{
    this->closeAll();
}

void Network::Server::closeClient(Network::ClientId id)
{
    if (!this->_clients[id]) {
        return;
    }
    ::close(this->_clients[id]);
    this->_clients.erase(id);
}

void Network::Server::closeAll()
{
    for (const auto &it: this->_clients) {
        this->closeClient(it.first);
    }
    this->_clients.clear();
}

Network::ClientInfo_t Network::Server::acceptClient()
{
}
