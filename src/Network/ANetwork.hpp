//
// EPITECH PROJECT, 2025
// ANetwork
// File description:
// Abstract for network interface
//

#pragma once

#include "Network/INetwork.hpp"

namespace Network {
    class ANetwork : public INetwork {
       public:
        virtual ~ANetwork();

        void close() override;

       protected:
        int _fd;
    };
}  // namespace Network
