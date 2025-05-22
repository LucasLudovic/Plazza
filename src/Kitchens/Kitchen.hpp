//
// EPITECH PROJECT, 2025
// Kitchen
// File description:
// Kitchen
//

#pragma once

#include "Network/Server/Server.hpp"

namespace plazza {
    class Kitchen {
       public:
        Kitchen(Network::ClientInfo_t &info);
        ~Kitchen() = default;

        void run();

       private:
        int _fd;
    };
}  // namespace plazza
