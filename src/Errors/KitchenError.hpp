//
// EPITECH PROJECT, 2025
// Network
// File description:
// Network
//

#pragma once

#include "AError.hpp"

namespace plazza {
    class KitchenError : public AError
    {
        public:
            KitchenError(const std::string &msg, const std::string &where)
                noexcept : AError(msg, where) {};
    };
}
