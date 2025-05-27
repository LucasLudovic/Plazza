/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** SFMLRenderer.cpp
*/

#include "SFMLRenderer.hpp"
#include <iostream>

void plazza::SFMLRenderer::init()
{
    _window.create(sf::VideoMode({800, 600}), "Plazza");
}

void plazza::SFMLRenderer::update()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}

void plazza::SFMLRenderer::render()
{
    _window.clear();
    _window.display();
}

std::string &plazza::SFMLRenderer::takeOrder()
{
    _takeOrder = false;
    return _order;
}

void plazza::SFMLRenderer::showError(const std::string &message)
{
    (void)message;
}
