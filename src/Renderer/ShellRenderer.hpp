/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ShellRenderer.hpp
*/

#pragma once

#include "IRenderer.hpp"
#include "Plazza.hpp"

#include <atomic>
#include <mutex>
#include <thread>
#include <unistd.h>

namespace plazza {
    class ShellRenderer : public IRenderer {
       public:
        ShellRenderer();
        ~ShellRenderer();

        void init(int nbCooks) override { this->_nbCooks = nbCooks; }

        bool shouldClose() override { return _shouldClose; }

        void update() override;

        void render(const plazza::Plazza &plazza) override;

        bool shouldTakeOrder() override { return _takeOrder; }

        std::string &takeOrder() override;

        void showError(const std::string &message)
        {
            std::cerr << message << std::endl;
        }

        void showStatus(const std::map<int, std::vector<order_t>> &kitchens);

       private:
        std::atomic<bool> _shouldClose;
        std::atomic<bool> _takeOrder;

        std::string _order;
        std::thread _inputThread;
        std::mutex _mutex;

        int _nbCooks;
        void inputLoop();
        void _displayCook(
            int nbOrders, std::vector<plazza::order_t> const &orders);
        void _displayQueue(
            int nbOrders, std::vector<plazza::order_t> const &orders);
    };
}  // namespace plazza
