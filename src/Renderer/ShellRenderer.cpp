/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ShellRenderer.cpp
*/

#include "ShellRenderer.hpp"
#include "Data.hpp"
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

void plazza::ShellRenderer::_displayCook(int nbOrders, const std::vector<plazza::order_t> &orders)
{
    for (int i = 0; i < nbOrders && i < this->_nbCooks; i += 1) {
        const auto &order = orders[i];
        std::cout << std::string(4, ' ');
        std::cout << "Cook " << i + 1 << ": ";
        std::cout << convertPizzaType(order.type) << " "
                  << convertPizzaSize(order.size) << std::endl;
    }
}

void plazza::ShellRenderer::_displayQueue(int nbOrders, const std::vector<plazza::order_t> &orders)
{
    for (int i = this->_nbCooks; i < nbOrders; i += 1) {
        const auto &order = orders[i];
        std::cout << std::string(4, ' ');
        std::cout << convertPizzaType(order.type) << " "
                  << convertPizzaSize(order.size) << std::endl;
    }
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
        int nbOrders = kitchen.second.size();
        this->_displayCook(nbOrders, kitchen.second);
        this->_displayQueue(nbOrders, kitchen.second);
        if (kitchen.second.empty()) {
            std::cout << std::string(4, ' ') << "No active orders"
                      << std::endl;
        }
    }
}
