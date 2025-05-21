//
// EPITECH PROJECT, 2025
// Communication
// File description:
// Communication channel
//

#include "NetworkError.hpp"
#include "Server.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

bool Network::Server::receive()
{
    if (this->_clients.empty())
        return false;

    const int timeout = 1000;

    std::vector<struct pollfd> pfds = this->_getPfds();
    std::vector <ClientId> ids = this->_getIds();

    int ret = poll(pfds.data(), pfds.size(), timeout);

    if (ret < 0)
        throw plazza::NetworkError("Error in poll", "Server");
    if (ret == 0)
        return false;
    size_t index = 0;
    for (auto &it: pfds) {
        if (it.revents & POLLIN) {
            data_t data;
            size_t received = recv(it.fd, &data, sizeof(data), 0);

            if (received == 0) {
                this->closeClient(ids[index]);
            }
            if (received != sizeof(data))
                throw plazza::NetworkError("Data couldn't be correctly sent", "Server");
            this->_data = data;
            return true;
        }
        index += 1;
    }
    return true;
}

bool Network::Server::send(const data_t &data)
{
    bool success = true;

    for (auto &[id, fd] : this->_clients) {
        auto sent = this->sendTo(id, data);
        if (sent == false)
            success = false;
    }
    return success;
}

bool Network::Server::sendTo(ClientId id, const data_t &data)
{
    if (this->_clients.find(id) == this->_clients.end())
        return false;

    return ::write(_clients[id], &data, sizeof(data)) == sizeof(data);
}

std::vector<struct pollfd> Network::Server::_getPfds()
{
    std::vector<struct pollfd> pfds;

    for (const auto &[clientId, fd]: this->_clients) {
        struct pollfd pfd;
        pfd.fd = fd;
        pfd.events = POLLIN | POLLHUP;
        pfd.revents = 0;
        pfds.push_back(pfd);
    }

    return pfds;
}

std::vector<Network::ClientId> Network::Server::_getIds()
{
    std::vector<ClientId> ids;

    for (const auto &[clientId, fd]: this->_clients) {
        ids.push_back(clientId);
    }

    return ids;
}
