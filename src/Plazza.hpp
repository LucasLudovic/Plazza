/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Plazza.hpp
*/

#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "Data.hpp"
#include "Network/Server/Server.hpp"
#include "OrderError.hpp"
#include "PlazzaError.hpp"
#include "SFMLRenderer.hpp"
#include "ShellRenderer.hpp"

namespace plazza {
    class Plazza {
       public:
        Plazza(int &argc, const char *const *&argv);
        ~Plazza() = default;

        void run();

       private:
        void errorHandling(int &argc, const char *const *&argv);

        void parseOrder(const std::string &order);
        void attributeOrder();

        void ReevaluateKitchens(const unsigned int &nbKitchenNeeded);
        void createKitchen(float cookingTimeMultiplier, int cooks, int time);

        float _cookingTimeMultiplier;
        size_t _cooks;
        size_t _time;

        std::unique_ptr<IRenderer> _renderer;

        Network::Server _server;
        std::vector<pid_t> _kitchens;
        std::vector<order_t> _orders;
    };
}  // namespace plazza
