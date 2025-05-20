/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Plazza.hpp
*/

#pragma once

#include <iostream>

#include "PlazzaError.hpp"

namespace plazza {
    class Plazza
    {
        public:
            Plazza(int argc, const char *const *argv);
            ~Plazza() = default;

            void run();
    };
}
