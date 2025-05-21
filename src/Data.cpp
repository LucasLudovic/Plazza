/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Enum.hpp
*/

#include "Data.hpp"

plazza::PizzaType plazza::convertPizzaType(const std::string &str)
{
    std::string pizzaType = str;
    trim(pizzaType);
    std::transform(pizzaType.begin(), pizzaType.end(), pizzaType.begin(), ::tolower);

    for (size_t i = 0; i < pizzaTypeString.size(); i++) {
        if (pizzaType == pizzaTypeString[i])
            return static_cast<plazza::PizzaType>(std::pow(2, i));
    }
    throw plazza::OrderError("Invalid pizza type", "Plazza");
}

plazza::PizzaSize plazza::convertPizzaSize(const std::string &str)
{
    for (size_t i = 0; i < pizzaSizeString.size(); i++) {
        if (str == pizzaSizeString[i])
            return static_cast<plazza::PizzaSize>(std::pow(2, i));
    }
    throw plazza::OrderError("Invalid pizza size", "Plazza");
}
