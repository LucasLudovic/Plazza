/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ShellRenderer.hpp
*/

#pragma once

#include "IRenderer.hpp"

/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ShellRenderer.hpp
*/

#pragma once

#include "IRenderer.hpp"

#include <unistd.h>
#include <atomic>
#include <thread>
#include <mutex>

namespace plazza {
    class ShellRenderer : public IRenderer
    {
        public:
            ShellRenderer();
            ~ShellRenderer();

            void init() override {}

            bool shouldClose() override { return _shouldClose; }

            void update() override;

            void render() override;

            bool shouldTakeOrder() override { return _takeOrder; }
            std::string &takeOrder() override;

            void showError(const std::string &message) { std::cerr << message << std::endl; }
            void showStatus(const std::map<int, std::vector<order_t>> &kitchens);

        private:
            std::atomic<bool> _shouldClose;
            std::atomic<bool> _takeOrder;

            std::string _order;
            std::thread _inputThread;
            std::mutex _mutex;

            void inputLoop();
    };
}
