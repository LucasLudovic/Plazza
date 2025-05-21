//
// EPITECH PROJECT, 2025
// Communication
// File description:
// Communication channel
//

#include "Server.hpp"
#include <unistd.h>

bool Network::Server::receive()
{
    if (this->_clients.empty())
        return false;
    return true;
}

bool Network::Server::send(const data_t &data)
{
    for (auto &[id, fd] : this->_clients) {
        auto sent = this->sendTo(id, data);
        if (sent == false)
            return false;
    }
    return true;
}

bool Network::Server::sendTo(ClientId id, const data_t &data)
{
    if (this->_clients.find(id) == this->_clients.end())
        return false;

    std::string message = data.pizzaName + " " + std::to_string(data.size) +
                          " " + std::to_string(data.quantity);
    size_t sent = ::write(_clients[id], message.c_str(), message.size());
    return sent == message.size();
}
