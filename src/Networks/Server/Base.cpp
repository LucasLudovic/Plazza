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
    if (this->_clients.find(id) == this->_clients.end()) {
        return;
    }
    ::close(this->_clients[id]);
    this->_clients.erase(id);
}

void Network::Server::closeAll()
{
    for (const auto &it : this->_clients) {
        this->closeClient(it.first);
    }
    this->_clients.clear();
}

Network::ClientInfo_t Network::Server::acceptClient(Network::ClientId id)
{
    int sv[2];

    if (this->_clients.find(id) != this->_clients.end())
        throw NetworkError("ClientId alreade in use", "Server");
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1)
        throw NetworkError("Socketpair failed to add client", "Server");

    this->_clients.insert({id, sv[0]});

    return {id, sv[1]};
}

const data_t &Network::Server::getData() const
{
    return this->_data;
}
