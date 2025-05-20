/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** StringUtils.hpp
*/

#pragma once

#include <string>

inline void trim(std::string &str)
{
    str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
}
