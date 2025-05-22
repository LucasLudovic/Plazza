/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Ingredient.cpp
*/

#include "Ingredient.hpp"

plazza::Stock::Stock()
{
    this->_ingredients[Ingredient::DOE] = 5;
    this->_ingredients[Ingredient::TOMATO] = 5;
    this->_ingredients[Ingredient::GRUYERE] = 5;
    this->_ingredients[Ingredient::HAM] = 5;
    this->_ingredients[Ingredient::MUSHROOMS] = 5;
    this->_ingredients[Ingredient::STEAK] = 5;
    this->_ingredients[Ingredient::EGGPLANT] = 5;
    this->_ingredients[Ingredient::GOAT_CHEESE] = 5;
    this->_ingredients[Ingredient::CHIEF_LOVE] = 5;
}

void plazza::Stock::refill()
{
    std::lock_guard<std::mutex> lock(this->_stockMutex);
    for (auto &it : this->_ingredients) {
        it.second += 1;
    }
}

void plazza::Stock::useIngredients(const std::vector<Ingredient> &ingredients)
{
    std::lock_guard<std::mutex> lock(this->_stockMutex);
    for (const auto &it : ingredients) {
        if (this->_ingredients[it] > 0) {
            this->_ingredients[it] -= 1;
        }
    }
}

/**
 * @brief Converts a string representation of an ingredient to its corresponding enum value
 *
 * @param str The ingredient name as a string (case-insensitive)
 * @return plazza::Ingredient The enum value representing the ingredient
 *
 * This function takes a string ingredient name, normalizes it (trims whitespace and converts to lowercase),
 * and matches it against a predefined list of ingredient names to return the corresponding enum value.
 */
plazza::Ingredient plazza::convertIngredient(const std::string &str)
{
    std::string ingredient = str;
    trim(ingredient);
    std::transform(
        ingredient.begin(), ingredient.end(), ingredient.begin(), ::tolower);

    for (size_t i = 0; i < ingredientString.size(); i++) {
        if (ingredient == ingredientString[i])
            return static_cast<plazza::Ingredient>(std::pow(2, i));
    }
}

std::string plazza::convertIngredient(plazza::Ingredient &ingredient)
{
    for (size_t i = 0; i < ingredientString.size(); i++) {
        if (ingredient == static_cast<plazza::Ingredient>(std::pow(2, i)))
            return ingredientString[i];
    }
}
