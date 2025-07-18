/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IRenderer.hpp
*/

#pragma once

#include <iostream>
#include <map>

#include "Data.hpp"

namespace plazza {

    class Plazza;

    class IRenderer
    {
        public:
            virtual ~IRenderer() = default;

            virtual void init(int nbCooks) = 0;

            virtual bool shouldClose() = 0;

            virtual void update() = 0;

            virtual void render(const plazza::Plazza &plazza) = 0;

            virtual bool shouldTakeOrder() = 0;
            virtual std::string &takeOrder() = 0;

            virtual void showError(const std::string &message) = 0;
            virtual void showStatus(const std::map<int, std::vector<order_t>> &kitchens) = 0;
    };
}
