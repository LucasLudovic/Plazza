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
    throw OrderError("Invalid pizza type", "Plazza");
}

std::string plazza::convertPizzaType(plazza::PizzaType &pizzaType)
{
    for (size_t i = 0; i < pizzaTypeString.size(); i++) {
        if (pizzaType == static_cast<plazza::PizzaType>(std::pow(2, i)))
            return pizzaTypeString[i];
    }
    throw OrderError("Invalid pizza type", "Plazza");
}

plazza::PizzaSize plazza::convertPizzaSize(const std::string &str)
{
    for (size_t i = 0; i < pizzaSizeString.size(); i++) {
        if (str == pizzaSizeString[i])
            return static_cast<plazza::PizzaSize>(std::pow(2, i));
    }
    throw OrderError("Invalid pizza size", "Plazza");
}

std::string plazza::convertPizzaSize(plazza::PizzaSize &pizzaSize)
{
    for (size_t i = 0; i < pizzaSizeString.size(); i++) {
        if (pizzaSize == static_cast<plazza::PizzaSize>(std::pow(2, i)))
            return pizzaSizeString[i];
    }
    throw OrderError("Invalid pizza size", "Plazza");
}

unsigned int plazza::unPow(unsigned int nb, unsigned int pow)
{
    for (unsigned int i = 0; i < nb; i++) {
        if (std::pow(pow, i) == nb)
            return i;
    }
    throw OrderError("Invalid pizza size", "Plazza");
}
