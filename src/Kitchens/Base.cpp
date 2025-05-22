//
// EPITECH PROJECT, 2025
// Kitchen
// File description:
// Kitchen base functions
//

#include "Kitchens/Kitchen.hpp"
#include "Network/Server/Server.hpp"
plazza::Kitchen::Kitchen(Network::ClientInfo_t &client_info)
{
    this->_fd = client_info.clientFd;
}

void plazza::Kitchen::run()
{
}
