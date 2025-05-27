//
// EPITECH PROJECT, 2025
// Kitchen
// File description:
// Kitchen base functions
//

#include "Kitchens/Cooks/Cooks.hpp"
#include "Kitchens/Kitchen.hpp"
#include "Network/Client/Client.hpp"
#include "Network/Server/Server.hpp"

plazza::Kitchen::Kitchen(Network::ClientInfo_t &client_info,
    int cookingMultiplier, int nbCooks, int restockTime)
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
    Cooks cooks(this->_nbCooks, stock, this->_cookingTimeMultiplier, client);

    std::atomic<bool> stop = false;

    auto restockTime = this->_restockTime;
    std::thread restockThread([&stock, restockTime, &stop]() {
        while (!stop.load()) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(restockTime));
            if (!stop.load()) {
                stock.refill();
            }
        }
    });

    auto lastActivity = std::chrono::steady_clock::now();
    const unsigned maxCapacity = 2 * this->_nbCooks;

    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto timeSinceLastActivity =
            std::chrono::duration_cast<std::chrono::seconds>(
                now - lastActivity);

        if (timeSinceLastActivity.count() >= 5 &&
            cooks.getActiveCooks() == 0 && cooks.getOrders().size() == 0) {
            break;
        }

        if (client.receive()) {
            const auto &order = client.getData();
            lastActivity = now;

            if (cooks.acceptMoreOrders(maxCapacity))
                cooks.addOrder(order);
            else
                break;
        }
    }

    stop.store(true);
    if (restockThread.joinable()) {
        restockThread.join();
    }
}
