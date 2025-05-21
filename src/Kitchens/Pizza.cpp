/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza.cpp
*/

#include "Pizza.hpp"

/**
 * @brief Set the quantity of a specific ingredient in the pizza
 *
 * @param ingredient The ingredient to set the quantity for
 */
void plazza::Pizza::setIngredient(Ingredient ingredient)
{
    _ingredients[ingredient] = unPow(ingredient);
}

/**
 * @brief Set multiple ingredients in the pizza
 *
 * @param ingredients A vector of ingredients to set in the pizza
 */
void plazza::Pizza::setIngredient(std::vector<Ingredient> ingredients)
{
    for (auto &ingredient : ingredients)
        setIngredient(ingredient);
}

/**
 * @brief Consume a specified quantity of an ingredient from the pizza
 *
 * @param ingredient The ingredient to consume
 * @param quantity The amount of the ingredient to consume
 * @throws KitchenError If the ingredient is not found or insufficient quantity is available
 */
void plazza::Pizza::consumeIngredient(Ingredient ingredient, size_t quantity)
{
    if (_ingredients.find(ingredient) == _ingredients.end())
        throw KitchenError("Ingredient not found", "Plazza");
    if (_ingredients[ingredient] < quantity)
        throw KitchenError("Not enough ingredient", "Plazza");
    _ingredients[ingredient] -= quantity;
}
