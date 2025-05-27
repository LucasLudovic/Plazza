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
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
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

            void showError(const std::string &message);
            void showStatus(const std::map<int, std::vector<order_t>> &) {}

        private:
            bool _takeOrder;
            std::string _order;

            sf::RenderWindow _window;
            sf::Font _font;
            sf::Texture _noteTexture;
            sf::Sprite _noteSprite;
            void _displayText(std::string str, sf::Vector2f pos, sf::Color color);
    };
}
