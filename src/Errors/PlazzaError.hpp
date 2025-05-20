/*
** EPITECH PROJECT, 2025
** B-OOP-400-BDX-4-1-plazza-baptiste.blambert
** File description:
** plazzaError
*/

#pragma once

#include "AError.hpp"

namespace plazza {
    class PlazzaError : public AError
    {
        public:
            PlazzaError(const std::string &msg, const std::string &where)
                noexcept : AError(msg, where) {};
    };
}
