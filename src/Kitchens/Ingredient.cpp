/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Ingredient.cpp
*/

#include "Ingredient.hpp"

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
    std::transform(ingredient.begin(), ingredient.end(), ingredient.begin(), ::tolower);

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
