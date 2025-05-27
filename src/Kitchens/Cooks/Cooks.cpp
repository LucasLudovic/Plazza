//
// EPITECH PROJECT, 2025
// Cooks
// File description:
// Base functions for cooks
//

#include "Cooks.hpp"
#include "CookError.hpp"
#include "KitchenError.hpp"
#include "Kitchens/Pizza.hpp"
#include "Network/Client/Client.hpp"

plazza::Cooks::Cooks(
    int nbCooks, Stock &stock, float multiplier, Network::Client &client)
    : _nbCooks(nbCooks), _multiplier(multiplier), _stock(stock),
      _client(client)
{
    for (int i = 0; i < nbCooks; i += 1) {
        this->_cookThread.emplace_back([this, i] {
            while (true) {
                plazza::order_t order;
                {
                    std::unique_lock<std::mutex> lock(this->_ordersMutex);
                    condition.wait(lock, [this] {
                        return this->_stop || !this->_orders.empty();
                    });

                    if (this->_stop && this->_orders.empty()) 
                        return;
                    order = this->_orders.front();
                    this->_orders.pop();
                }

                Pizza pizza(order.type, order.size);

                auto ingredients = _getIngredientsForPizza(order.type);
                if (this->_stock.hasIngredients(ingredients)) {
                    this->_stock.useIngredients(ingredients);
                    this->_activeCooks += 1;

                    int cookingTime = this->_getCookingTime(order.type);
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(cookingTime));

                    plazza::order_t completedOrder = order;
                    if (!this->_client.send(completedOrder)) {
                        throw CookError(
                            "Failed to send completed order", "Cooks");
                    }
                    this->_activeCooks -= 1;
                    continue;
                }
                {
                    std::lock_guard<std::mutex> lock(this->_ordersMutex);
                    this->_orders.push(order);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        });
    }
}

unsigned plazza::Cooks::getActiveCooks() const
{
    return this->_activeCooks.load();
}

const std::queue<plazza::order_t> &plazza::Cooks::getOrders() const
{
    return this->_orders;
}
