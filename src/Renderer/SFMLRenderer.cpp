/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** SFMLRenderer.cpp
*/

#include "SFMLRenderer.hpp"
#include "PlazzaError.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cctype>

void plazza::SFMLRenderer::init()
{
    this->_window.create(sf::VideoMode({800, 600}), "Plazza");
    if (!this->_font.loadFromFile("./assets/fonts/JetBrainsMonoNerdFont-Medium.ttf"))
        throw plazza::PlazzaError("Failed to load font", "SFML");
    if (!this->_noteTexture.loadFromFile("./assets/note.png"))
        throw plazza::PlazzaError("Failed to load note", "SFML");
    this->_noteSprite.setTexture(this->_noteTexture);
}

void plazza::SFMLRenderer::update()
{
    sf::Event event;

    std::map<sf::Keyboard::Key, char> keyPress = {{sf::Keyboard::Num0, '0'},
        {sf::Keyboard::Num1, '1'}, {sf::Keyboard::Num2, '2'},
        {sf::Keyboard::Num3, '3'}, {sf::Keyboard::Num4, '4'},
        {sf::Keyboard::Num5, '5'}, {sf::Keyboard::Num6, '6'},
        {sf::Keyboard::Num7, '7'}, {sf::Keyboard::Num8, '8'},
        {sf::Keyboard::Num9, '9'}, {sf::Keyboard::A, 'a'},
        {sf::Keyboard::B, 'b'}, {sf::Keyboard::C, 'c'}, {sf::Keyboard::D, 'd'},
        {sf::Keyboard::E, 'e'}, {sf::Keyboard::F, 'f'}, {sf::Keyboard::G, 'g'},
        {sf::Keyboard::H, 'h'}, {sf::Keyboard::I, 'i'}, {sf::Keyboard::J, 'j'},
        {sf::Keyboard::K, 'k'}, {sf::Keyboard::L, 'l'}, {sf::Keyboard::M, 'm'},
        {sf::Keyboard::N, 'n'}, {sf::Keyboard::O, 'o'}, {sf::Keyboard::P, 'p'},
        {sf::Keyboard::Q, 'q'}, {sf::Keyboard::R, 'r'}, {sf::Keyboard::S, 's'},
        {sf::Keyboard::T, 't'}, {sf::Keyboard::U, 'u'}, {sf::Keyboard::V, 'v'},
        {sf::Keyboard::W, 'w'}, {sf::Keyboard::X, 'x'}, {sf::Keyboard::Y, 'y'},
        {sf::Keyboard::Z, 'z'}, {sf::Keyboard::Space, ' '}};

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                if (!this->_order.empty()) {
                    this->_takeOrder = true;
                }
            } else if (event.key.code == sf::Keyboard::BackSpace) {
                if (!this->_order.empty()) {
                    this->_order.pop_back();
                }
            } else {
                for (auto &it : keyPress) {
                    if (event.key.code == it.first &&
                        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                        this->_order += std::toupper(it.second);
                        continue;
                    }
                    if (event.key.code == it.first) {
                        this->_order += it.second;
                        continue;
                    }
                }
            }
        }
    }
}

void plazza::SFMLRenderer::_displayText(std::string str, sf::Vector2f pos, sf::Color color)
{
    sf::Text text;

    text.setFont(this->_font);
    text.setString(str.c_str());
    text.setFillColor(color);
    text.setCharacterSize(10);
    text.setPosition(pos);
    this->_window.draw(text);
}

void plazza::SFMLRenderer::render()
{
    this->_window.clear();
    this->_displayText("Enter your Order :", {10, 10}, sf::Color::White);
    this->_noteSprite.setPosition({10,10});
    this->_noteSprite.setScale({0.5, 0.5});
    this->_window.draw(this->_noteSprite);
    this->_displayText(this->_order, {55, 92}, sf::Color::Black);
    this->_window.display();
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
