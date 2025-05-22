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

plazza::Plazza::Plazza(int &argc, const char *const *&argv)
{
    errorHandling(argc, argv);

    _cookingTimeMultiplier = std::stof(argv[1]);
    _cooks = std::stoi(argv[2]);
    _time = std::stoi(argv[3]);

    for (int i = 4; i < argc; i++) {
        if (std::string(argv[i]) == "-g") {
            _renderer = std::make_unique<SFMLRenderer>();
        }
    }
    if (!_renderer)
        _renderer = std::make_unique<ShellRenderer>();

    _renderer->init();

    _lastID = 0;
}

void plazza::Plazza::run()
{
    while (!_renderer->shouldClose()) {
        _renderer->update();

        if (_renderer->shouldTakeOrder()) {
            try {
                parseOrder(_renderer->takeOrder());
                attributeOrder();
            } catch (const plazza::OrderError &e) {
                _renderer->showError(e.where() + std::string(" Error: ") + e.what());
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
                throw plazza::PlazzaError("Arguments must be numbers", "Plazza");
        }
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
void plazza::Plazza::parseOrder(const std::string &order)
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
            throw plazza::OrderError("Invalid quantity format: " + quantityStr, "Order");

        unsigned int quantity = 0;
        try {
            quantity = std::stoul(quantityStr.substr(1));
        } catch (const std::exception& e) {
            throw plazza::OrderError("Invalid quantity format: " + quantityStr, "Order");
        }

        order_t order = {
            convertPizzaType(name),
            convertPizzaSize(size),
            quantity
        };

        _orders.push_back(order);
    }
}

void plazza::Plazza::attributeOrder()
{
    if (_orders.empty())
        return;

    unsigned int nbPizza = 0;

    for (auto &order : _orders)
        nbPizza += order.quantity;

    std::cout << "Number of pizzas: " << nbPizza << std::endl;
    unsigned int nbKitchen = nbPizza / (2 * _cooks);
    if (nbPizza < 2 * _cooks || nbPizza % (2 * _cooks) != 0)
        nbKitchen++;

    ReevaluateKitchens(nbKitchen);

    unsigned int orderIndex = 0;
    for (auto &kitchen : _kitchensIDs) {
        for (unsigned int i = 0; i < 2 * _cooks; i++) {
            if (orderIndex >= _orders.size())
                break;
            order_t &order = _orders[orderIndex];

            std::cout << "Order " << convertPizzaType(order.type) << " " << convertPizzaSize(order.size) <<
            " sent to kitchen " << kitchen << std::endl;
            order.quantity--;
            if (order.quantity == 0)
                orderIndex++;
        }
    }
    _orders.clear();
    std::cout << "All orders sent" << std::endl;
}

void plazza::Plazza::ReevaluateKitchens(const unsigned int &nbKitchenNeeded)
{
    std::cout << "Reevaluating kitchens " << "(" << nbKitchenNeeded << ")" << std::endl;
    if (nbKitchenNeeded <= _kitchens.size()) {
        for (unsigned int i = nbKitchenNeeded; i < _kitchens.size(); i++) {
            // kill(_kitchens[i], SIGKILL);
            _kitchens.erase(_kitchens.begin() + i);
            std::cout << "Kitchen " << i << " killed" << std::endl;
        }
    } else {
        for (unsigned int i = _kitchens.size(); i < nbKitchenNeeded; i++)
            createKitchen(_cookingTimeMultiplier, _cooks, _time);
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
void plazza::Plazza::createKitchen(float cookingTimeMultiplier, int cooks, int time)
{
    Network::ClientInfo_t info = this->_server.acceptClient();

    pid_t pid = fork();

    if (pid == -1)
        throw plazza::PlazzaError("Failed to create kitchen", "Plazza");
    if (pid != 0) {
        std::cout << "Kitchen created (pid: " << pid << ", id: " << info.id << ")" << std::endl;
        _kitchens.push_back(pid);
        return;
    }

    this->_server.closeAll();
    Kitchen kitchen(info, cookingTimeMultiplier, cooks, time);
    kitchen.run();
    exit(0);
}
