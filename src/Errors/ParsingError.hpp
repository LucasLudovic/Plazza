/*
** EPITECH PROJECT, 2025
** B-OOP-400-BDX-4-1-plazza-baptiste.blambert
** File description:
** ParsingError
*/

#pragma once

#include "AError.hpp"

namespace plazza {
    class ParsingError : public AError
    {
        public:
            ParsingError(const std::string &msg, const std::string &where)
                noexcept : AError(msg, where) {};
    };
}
