//
// EPITECH PROJECT, 2025
// ANetwork
// File description:
// Implementation for ANetwork functions
//

#include "ANetwork.hpp"
#include <unistd.h>

Network::ANetwork::~ANetwork()
{
    this->close();
}

void Network::ANetwork::close()
{
    if (this->_fd > 0) {
        ::close(this->_fd);
    }
    this->_fd = -1;
}
