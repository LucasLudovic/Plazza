//
// EPITECH PROJECT, 2025
// Kitchen
// File description:
// Kitchen
//

#pragma once

#include "Kitchens/Ingredient.hpp"
#include "Network/Server/Server.hpp"

namespace plazza {
    class Kitchen {
       public:
        Kitchen(Network::ClientInfo_t &info, int cookingMultiplier,
            int nbCooks, int restockTime);
        ~Kitchen() = default;

        void run();

       private:
        int _fd;
        float _cookingTimeMultiplier;
        int _nbCooks;
        int _restockTime;

        std::vector<Ingredient> getIngredientsForPizza(PizzaType type);
        int getCookingTime(PizzaType type);
    };
}  // namespace plazza
