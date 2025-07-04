//
// EPITECH PROJECT, 2025
// Communication
// File description:
// Communication for Client IPC
//

#include "Client.hpp"
#include "Data.hpp"
#include "NetworkError.hpp"
#include <sys/socket.h>
#include <unistd.h>

bool Network::Client::send(const plazza::order_t &data)
{
    return ::write(_fd, &data, sizeof(data)) == sizeof(data);
}

bool Network::Client::receive()
{
    ssize_t received = ::recv(this->_fd, &this->_data, sizeof(_data), MSG_DONTWAIT);

    if (received < 0)
        return false;
    if (received == 0)
        this->close();
    return received == sizeof(_data);
}

const plazza::order_t &Network::Client::getData() const
{
    return this->_data;
}
