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

    if (pizzaType == "regina")
        return Regina;
    if (pizzaType == "margarita")
        return Margarita;
    if (pizzaType == "americana")
        return Americana;
    if (pizzaType == "fantasia")
        return Fantasia;
    throw plazza::OrderError("Invalid pizza type", "Plazza");
}

plazza::PizzaSize plazza::convertPizzaSize(const std::string &str)
{
    if (str == "S")
        return S;
    if (str == "M")
        return M;
    if (str == "L")
        return L;
    if (str == "XL")
        return XL;
    if (str == "XXL")
        return XXL;
    throw plazza::OrderError("Invalid pizza size", "Plazza");
}
