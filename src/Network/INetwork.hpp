//
// EPITECH PROJECT, 2025
// Network
// File description:
// Encapsulation of C sockets
//

#pragma once

#include <cerrno>
#include <cstdint>
#include <string>

namespace Network {
    typedef struct data_s {
        std::string pizzaName;
        unsigned size;
        unsigned quantity;
    } data_t;

    class INetwork {
       public:
        virtual ~INetwork() = default;

        [[nodiscard]] virtual bool receive() = 0;
        [[nodiscard]] virtual const data_t &getData() const = 0;
        virtual void close() = 0;
    };
}  // namespace Network
