//
// EPITECH PROJECT, 2025
// Cooking
// File description:
// Cooking
//

#include "Cooks.hpp"

int plazza::Cooks::_getCookingTime(PizzaType type)
{
    int timeMs = 0;
    switch (type) {
        case PizzaType::Margarita:
            timeMs = 1000;
            break;
        case PizzaType::Regina:
            timeMs = 2000;
            break;
        case PizzaType::Americana:
            timeMs = 2000;
            break;
        case PizzaType::Fantasia:
            timeMs = 4000;
            break;
    }
    return static_cast<int>(timeMs * this->_multiplier);
}
