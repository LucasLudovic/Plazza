//
// EPITECH PROJECT, 2025
// Cooking
// File description:
// Cooking
//

#include "CookError.hpp"
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

std::vector<plazza::Ingredient> plazza::Cooks::getIngredientsForPizza(
    PizzaType type)
{
    switch (type) {
        case PizzaType::Margarita:
            return {Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE};
        case PizzaType::Regina:
            return {Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE,
                Ingredient::HAM, Ingredient::MUSHROOMS};
        case PizzaType::Americana:
            return {Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE,
                Ingredient::STEAK};
        case PizzaType::Fantasia:
            return {Ingredient::DOE, Ingredient::TOMATO, Ingredient::EGGPLANT,
                Ingredient::GOAT_CHEESE, Ingredient::CHIEF_LOVE};
        default:
            throw CookError("Unable to get ingredient for pizza", "Cook");
    }
}
