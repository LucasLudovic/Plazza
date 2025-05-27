/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Enum.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "OrderError.hpp"
#include "StringUtils.hpp"

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };
    const std::vector<std::string> pizzaTypeString = {
        "regina",
        "margarita",
        "americana",
        "fantasia"
    };
    PizzaType convertPizzaType(const std::string &str);
    std::string convertPizzaType(const PizzaType &pizzaType);

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    const std::vector<std::string> pizzaSizeString = {
        "S",
        "M",
        "L",
        "XL",
        "XXL"
    };
    PizzaSize convertPizzaSize(const std::string &str);
    std::string convertPizzaSize(const PizzaSize &pizzaSize);

    unsigned int unPow(unsigned int nb, unsigned int pow = 2);

    typedef struct order_s {
        PizzaType type;
        PizzaSize size;
    } order_t;

    inline bool operator==(const order_t &lhs, const order_t &rhs) {
        return lhs.type == rhs.type && lhs.size == rhs.size;
    }
}
