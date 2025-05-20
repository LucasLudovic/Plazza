/*
** EPITECH PROJECT, 2025
** B-OOP-400-BDX-4-1-plazza-baptiste.blambert
** File description:
** OrderError
*/

#pragma once

#include "AError.hpp"

namespace plazza {
    class OrderError : public AError
    {
        public:
            OrderError(const std::string &msg, const std::string &where)
                noexcept : AError(msg, where) {};
    };
}
