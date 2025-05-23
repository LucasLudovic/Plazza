/*
** EPITECH PROJECT, 2025
** B-OOP-400-BDX-4-1-plazza-baptiste.blambert
** File description:
** AError
*/

#pragma once

#include "IError.hpp"

namespace plazza {
    class AError : public IError
    {
        public:
            AError(const std::string &msg, const std::string &where) noexcept;

            const char *what() const noexcept;
            const char *where() const noexcept;

        private:
            std::string _msg;
            std::string _where;
    };
}
