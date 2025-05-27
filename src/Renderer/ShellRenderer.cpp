/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ShellRenderer.cpp
*/

#include "ShellRenderer.hpp"

plazza::ShellRenderer::ShellRenderer() :
    _shouldClose(false),
    _takeOrder(false)
{
    _inputThread = std::thread(&ShellRenderer::inputLoop, this);
}

plazza::ShellRenderer::~ShellRenderer()
{
    _shouldClose = true;
    if (_inputThread.joinable())
        _inputThread.join();
}

void plazza::ShellRenderer::inputLoop()
{
    std::string input;
    while (!_shouldClose) {
        std::cout << "Enter your order:" << std::endl;
        if (!std::getline(std::cin, input)) {
            _shouldClose = true;
            break;
        }
        if (input == "exit") {
            _shouldClose = true;
            break;
        }
        std::lock_guard<std::mutex> lock(_mutex);
        _order = input;
        if (!_order.empty())
            _takeOrder = true;
        usleep(500000);
    }
}

void plazza::ShellRenderer::update()
{}

void plazza::ShellRenderer::render()
{}

std::string &plazza::ShellRenderer::takeOrder()
{
    _takeOrder = false;
    return _order;
}
