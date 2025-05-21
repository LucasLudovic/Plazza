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

namespace plazza {
    class ShellRenderer : public IRenderer
    {
        public:
            ShellRenderer() : _shouldClose(false), _takeOrder(false) {}
            ~ShellRenderer() = default;

            void init() override {}

            bool shouldClose() override { return _shouldClose; }

            void update() override;

            void render() override;

            bool shouldTakeOrder() override { return _takeOrder; }
            std::string takeOrder() override;

            void showError(const std::string &message) { std::cerr << message << std::endl; }

        private:
            bool _shouldClose;
            bool _takeOrder;

            std::string _order;
    };
}
