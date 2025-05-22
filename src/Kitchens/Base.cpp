//
// EPITECH PROJECT, 2025
// Kitchen
// File description:
// Kitchen base functions
//

#include "Kitchens/Kitchen.hpp"
#include "Network/Server/Server.hpp"
#include "Network/Client/Client.hpp"

plazza::Kitchen::Kitchen(Network::ClientInfo_t &client_info, int cookingMultiplier,
            int nbCooks, int restockTime)
{
    this->_fd = client_info.clientFd;
    this->_cookingTimeMultiplier = cookingMultiplier;
    this->_nbCooks = nbCooks;
    this->_restockTime = restockTime;
}

void plazza::Kitchen::run()
{
    Network::Client client(this->_fd);
    Stock stock;
}
