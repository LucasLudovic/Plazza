/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ShellRenderer.cpp
*/

#include "ShellRenderer.hpp"
#include "Plazza.hpp"

plazza::ShellRenderer::ShellRenderer() : _shouldClose(false), _takeOrder(false)
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

void plazza::ShellRenderer::update() {}

void plazza::ShellRenderer::render(const plazza::Plazza &plazza)
{
    (void)plazza;
}

std::string &plazza::ShellRenderer::takeOrder()
{
    _takeOrder = false;
    return _order;
}

void plazza::ShellRenderer::showStatus(
    const std::map<int, std::vector<order_t>> &kitchens)
{
    if (kitchens.empty()) {
        std::cout << "No kitchens available" << std::endl;
        return;
    }

    for (const auto &kitchen : kitchens) {
        std::cout << "Kitchen " << kitchen.first << ":" << std::endl;
        int i = 0;
        for (const auto &order : kitchen.second) {
            std::cout << std::string(4, ' ');
            if (i < this->_nbCooks)
                std::cout << "Cook " << i + 1 << ": ";
            std::cout << convertPizzaType(order.type) << "x "
                      << convertPizzaSize(order.size) << std::endl;
            i += 1;
        }
    }
}
