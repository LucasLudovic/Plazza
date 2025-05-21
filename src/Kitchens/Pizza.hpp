/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza.hpp
*/

#pragma once

#include <map>

#include "KitchenError.hpp"
#include "Ingredient.hpp"

namespace plazza {
    class Pizza
    {
        public:
            Pizza(PizzaType &name, PizzaSize &size) : _name(name), _size(size) {}
            ~Pizza() = default;

            std::string getType() const { return convertPizzaType(_name); }
            std::string getSize() const { return convertPizzaSize(_size); }

            void setIngredient(Ingredient ingredient);
            void setIngredient(std::vector<Ingredient> ingredient);

            void consumeIngredient(Ingredient ingredient, size_t quantity = 1);

        private:
            PizzaType _name;
            PizzaSize _size;

            std::map<Ingredient, unsigned int> _ingredients;
    };
}
