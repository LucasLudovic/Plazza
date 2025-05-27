/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Plazza.hpp
*/

#include "Plazza.hpp"
#include "Kitchens/Kitchen.hpp"
#include "Network/Client/Client.hpp"
#include "Network/Server/Server.hpp"
#include <iostream>

plazza::Plazza::Plazza(int &argc, const char *const *&argv)
{
    errorHandling(argc, argv);

    _cookingTimeMultiplier = std::stof(argv[1]);
    _cooks = std::stoi(argv[2]);
    _time = std::stoi(argv[3]);

    _server = Network::Server();
    _renderer = nullptr;

    if (argv[4] != nullptr && std::string(argv[4]) == "-g") {
        _renderer = std::make_unique<SFMLRenderer>();
    }
    if (!_renderer)
        _renderer = std::make_unique<ShellRenderer>();

    _renderer->init();
}

void plazza::Plazza::run()
{
    while (!_renderer->shouldClose()) {
        _renderer->update();

        updateKitchens();
        if (_renderer->shouldTakeOrder()) {
            try {
                parseOrder(_renderer->takeOrder());
                attributeOrder();
            } catch (const plazza::OrderError &e) {
                _renderer->showError(
                    e.where() + std::string(" Error: ") + e.what());
            }
        }
        _renderer->render();
    }
}

/**
 * @brief Validates command-line arguments for the Plazza application
 *
 * Checks the number and type of arguments passed to the program.
 * Handles help flag (-h) and ensures all arguments are numeric.
 * Throws a PlazzaError if arguments are invalid.
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @throws PlazzaError if incorrect number of arguments or non-numeric arguments
 */
void plazza::Plazza::errorHandling(int &argc, const char *const *&argv)
{
    if (argc == 2 && std::string(argv[1]) == "-h") {
        std::cout << "Usage: ./plazza [multiplier] [cooks] [time]" << std::endl;
        exit(0);
    }

    if (argc < 4)
        throw plazza::PlazzaError("Wrong number of arguments", "Plazza");

    // make sure that the arguments are all numbers
    for (int i = 1; i < 4; i++) {
        for (size_t j = 0; argv[i][j]; j++) {
            if (!std::isdigit(argv[i][0]))
                throw plazza::PlazzaError(
                    "Arguments must be numbers", "Plazza");
        }
    }
}

/**
 * @brief Processes a received command from a kitchen
 *
 * Handles the completion of an order from a specific kitchen.
 * If a valid kitchen ID is received, removes the corresponding order
 * from the kitchen's order list.
 *
 * @param id The kitchen ID that has completed an order
 */
void plazza::Plazza::updateKitchens()
{
    if (_kitchens.empty())
        return;
    auto id = this->_server.receive();

    if (id != -1) {
        const order_t order = this->_server.getData();

        auto it = _kitchens.find(id);
        if (it != _kitchens.end()) {
            auto &orders = it->second;
            auto orderIt = std::find(orders.begin(), orders.end(), order);
            if (orderIt != orders.end()) {
                orders.erase(orderIt);
            }

            if (it->second.empty()) {
                _kitchens.erase(it);
            }
        }
    }

    std::vector<int> kitchenIDs = this->_server.getIds();
    for (auto &kitchenID : kitchenIDs) {
        if (_kitchens.find(kitchenID) == _kitchens.end())
            _kitchens.erase(kitchenID);
    }
}

/**
 * @brief Parses a pizza order string into individual pizza orders
 *
 * Processes a semicolon-separated order string, extracting pizza name, size, and quantity.
 * Validates the order format and converts pizza details to internal order representation.
 * Pushes validated orders into the internal order queue.
 *
 * @param order A string containing pizza orders in the format "PizzaName Size xQuantity"
 * @throws OrderError if order format is invalid or quantity cannot be parsed
 */
void plazza::Plazza::parseOrder(std::string &order)
{
    if (order.empty())
        return;

    std::stringstream ss(order);
    std::string orderStr;

    while (std::getline(ss, orderStr, ';')) {
        std::istringstream orderStream(orderStr);
        std::string name, size, quantityStr;

        orderStream >> name >> size >> quantityStr;

        if (quantityStr.empty() || quantityStr[0] != 'x')
            throw plazza::OrderError(
                "Invalid quantity format: " + quantityStr, "Order");

        unsigned int quantity = 0;
        try {
            quantity = std::stoul(quantityStr.substr(1));
        } catch (const std::exception &e) {
            throw plazza::OrderError(
                "Invalid quantity format: " + quantityStr, "Order");
        }

        for (unsigned int i = 0; i < quantity; i++) {
            _orders.push({
                convertPizzaType(name),
                convertPizzaSize(size)
            });
        }
    }
    order.clear();
}

/**
 * @brief Distributes pizza orders to available kitchens
 *
 * Manages the allocation of pizza orders to existing kitchens or creates new kitchens
 * when necessary. Calculates the number of remaining kitchen slots and creates additional
 * kitchens if the current kitchen capacity is insufficient to handle pending orders.
 *
 * Iterates through existing kitchens, sending orders to available slots and tracking
 * order distribution. Creates new kitchens based on the number of pending pizzas and
 * kitchen cooking capacity.
 *
 * @note Prints diagnostic information about order distribution and kitchen creation
 */
void plazza::Plazza::attributeOrder()
{
    if (_orders.empty())
        return;

    unsigned int nbRemainingSlots = 0;
    if (!this->_server.getIds().empty()) {
        for (auto &kitchen : _kitchens) {
            nbRemainingSlots += 2 * _cooks - (kitchen.second.empty() ? 0 : kitchen.second.size());
        }
    }

    // if there is no kitchen available, create one
    int nbPizza = _orders.size() - nbRemainingSlots;

    if (nbPizza > 0) {

        int nbKitchenToCreate = nbPizza / (2 * _cooks);
        if (nbPizza < 2 * (int)_cooks || nbPizza % (2 * (int)_cooks) != 0)
        nbKitchenToCreate++;

        for (int i = 0; i < nbKitchenToCreate; i++)
            createKitchen(_cookingTimeMultiplier, _cooks, _time);
    }

    for (auto &kitchen : this->_kitchens) {
        unsigned int kitchenSize = (kitchen.second.empty() ? 0 : kitchen.second.size());
        for (unsigned int i = kitchenSize; i < 2 * _cooks && !_orders.empty(); i++) {
            order_t &order = _orders.front();
            _orders.pop();

            this->_server.sendTo(kitchen.first, order);
            kitchen.second.push_back(order);
        }
    }
}

/**
 * @brief Creates a new kitchen process for pizza preparation
 *
 * Forks a new process to create a kitchen with specified cooking parameters.
 * Adds the new kitchen's process ID to the list of kitchens.
 *
 * @param cookingTimeMultiplier Multiplier for cooking time
 * @param cooks Number of cooks in the kitchen
 * @param time Kitchen processing time
 * @throws PlazzaError if kitchen process creation fails
 */
void plazza::Plazza::createKitchen(
    float cookingTimeMultiplier, int cooks, int time)
{
    Network::ClientInfo_t info = this->_server.acceptClient();

    pid_t pid = fork();

    if (pid == -1)
        throw plazza::PlazzaError("Failed to create kitchen", "Plazza");
    if (pid != 0) {
        _kitchens[info.id] = {};
        return;
    }

    Kitchen kitchen(info, cookingTimeMultiplier, cooks, time);
    kitchen.run();
    exit(0);
}
