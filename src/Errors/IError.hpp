/*
** EPITECH PROJECT, 2025
** B-OOP-400-BDX-4-1-plazza-baptiste.blambert
** File description:
** IError
*/

#pragma once

#include <iostream>
#include <stdexcept>

namespace plazza {
    class IError : public std::exception
    {
        public:
            virtual const char *what() const noexcept override = 0;
            virtual const char *where() const noexcept = 0;
    };
}
