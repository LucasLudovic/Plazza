//
// EPITECH PROJECT, 2025
// Cooks
// File description:
// Cooks
//

#pragma once

#include "Kitchens/Ingredient.hpp"
#include "Network/Client/Client.hpp"
#include <atomic>
#include <condition_variable>
#include <queue>
#include <thread>
#include <vector>

namespace plazza {
    class Cooks {
       public:
        Cooks(int nbCooks, Stock &stock, float multiplier, Network::Client &client);

        bool acceptMoreOrders(unsigned maxCapacity);
        
        void addOrder(const plazza::order_t &order);
        unsigned getActiveCooks() const;
        const std::queue<plazza::order_t> &getOrders() const;

       private:
        int _nbCooks;
        float _multiplier;
        Stock &_stock;

        Network::Client& _client;

        std::atomic<unsigned> _activeCooks;
        std::atomic<bool> _stop;
        std::vector<std::thread> _cookThread;
        std::queue<plazza::order_t> _orders;
        std::condition_variable condition;

        std::mutex _ordersMutex;

        std::vector<Ingredient> _getIngredientsForPizza(PizzaType type);
        int _getCookingTime(PizzaType type);
    };
}  // namespace plazza
