/*
** EPITECH PROJECT, 2024
** B-OOP-400-BDX-4-1-plazza-florian.labadie
** File description:
** Main.cpp
*/

#include "Plazza.hpp"

int main(int argc, const char *const *argv)
{
    try {
        plazza::Plazza plazza(argc, argv);

        plazza.run();
    } catch (const plazza::IError &e) {
        std::cerr << e.where() << " Error: " << e.what() << std::endl;
        return 84;
    }
    std::cout << "Going to exit" << std::endl;
    return 0;
}
