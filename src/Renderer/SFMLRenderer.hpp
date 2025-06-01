/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** SFMLRenderer.hpp
*/

#pragma once

#include "IRenderer.hpp"
#include "Plazza.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

#include <SFML/Graphics.hpp>

namespace plazza {
    class SFMLRenderer : public IRenderer
    {
        public:
            SFMLRenderer() : _takeOrder(false) {}
            ~SFMLRenderer() = default;

            void init(int nbCooks) override;

            bool shouldClose() override { return !_window.isOpen(); }

            void update() override;

            void render(const plazza::Plazza &plazza) override;

            bool shouldTakeOrder() override { return _takeOrder; }
            std::string &takeOrder() override;

            void showError(const std::string &message);
            void showStatus(const std::map<int, std::vector<order_t>> &) {}

        private:
            bool _takeOrder;
            std::string _order;
            int _nbCooks;

            sf::RenderWindow _window;
            sf::Font _font;
            sf::Texture _noteTexture;
            sf::Sprite _noteSprite;
            sf::Texture _kitchenTexture;
            void _displayText(std::string str, sf::Vector2f pos, sf::Color color);
            void _drawKitchen(int id, int nbCooks);
    };
}
