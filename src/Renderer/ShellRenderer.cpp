/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ShellRenderer.cpp
*/

#include "ShellRenderer.hpp"

void plazza::ShellRenderer::update()
{
    if (std::cin.eof()) {
        _shouldClose = true;
        return;
    }
    std::string input;
    std::cout << "Enter your order:" << std::endl;
    std::getline(std::cin, input);
    if (input == "exit") {
        _shouldClose = true;
        return;
    }
    _order = input;
    _takeOrder = true;
}

void plazza::ShellRenderer::render()
{}

std::string plazza::ShellRenderer::takeOrder()
{
    _takeOrder = false;
    return _order;
}
