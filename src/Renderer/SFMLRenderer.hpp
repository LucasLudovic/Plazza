/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** SFMLRenderer.hpp
*/

#pragma once

#include "IRenderer.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

#include <SFML/Graphics.hpp>

namespace plazza {
    class SFMLRenderer : public IRenderer
    {
        public:
            SFMLRenderer() : _takeOrder(false) {}
            ~SFMLRenderer() = default;

            void init() override;

            bool shouldClose() override { return !_window.isOpen(); }

            void update() override;

            void render() override;

            bool shouldTakeOrder() override { return _takeOrder; }
            std::string &takeOrder() override;

            void showError(const std::string &message) override;

        private:
            bool _takeOrder;
            std::string _order;

            sf::RenderWindow _window;
            sf::Font _font;
            void _displayText(std::string str, sf::Vector2f pos, sf::Color color);
    };
}
