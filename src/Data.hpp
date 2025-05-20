/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Enum.hpp
*/

#pragma once

#include <iostream>
#include <algorithm>

#include "OrderError.hpp"
#include "StringUtils.hpp"

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };
    PizzaType convertPizzaType(const std::string &str);

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    PizzaSize convertPizzaSize(const std::string &str);

    typedef struct order_s {
        PizzaType type;
        PizzaSize size;
        unsigned int quantity;
    } order_t;
}
