//
// EPITECH PROJECT, 2025
// Client
// File description:
// Base implementation for IPC Client
//

#include "Client.hpp"

Network::Client::Client(int fd)
{
    this->_fd = fd;
};
