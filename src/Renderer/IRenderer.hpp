/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IRenderer.hpp
*/

#pragma once

#include <iostream>

namespace plazza {
    class IRenderer
    {
        public:
            virtual ~IRenderer() = default;

            virtual void init() = 0;

            virtual bool shouldClose() = 0;

            virtual void update() = 0;

            virtual void render() = 0;

            virtual bool shouldTakeOrder() = 0;
            virtual std::string takeOrder() = 0;

            virtual void showError(const std::string &message) = 0;
    };
}
