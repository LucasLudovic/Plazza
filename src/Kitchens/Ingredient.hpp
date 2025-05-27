/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Ingredient.hpp
*/

#pragma once

#include "Data.hpp"
#include <map>
#include <mutex>

namespace plazza {
    enum Ingredient {
        DOE = 1,
        TOMATO = 2,
        GRUYERE = 4,
        HAM = 8,
        MUSHROOMS = 16,
        STEAK = 32,
        EGGPLANT = 64,
        GOAT_CHEESE = 128,
        CHIEF_LOVE = 256
    };

    const std::vector<std::string> ingredientString = {"doe", "tomato",
        "gruyere", "ham", "mushrooms", "steak", "eggplant", "goat cheese",
        "chief love"};

    class Stock {
       public:
        Stock();

        void refill();
        void useIngredients(const std::vector<Ingredient> &ingredients);
        bool hasIngredients(const std::vector<Ingredient>& ingredient);

       private:
        std::map<Ingredient, int> _ingredients;
        std::mutex _stockMutex;
    };

    Ingredient convertIngredient(const std::string &str);
    std::string convertIngredient(const Ingredient &ingredient);
}  // namespace plazza
