//
// EPITECH PROJECT, 2025
// Client
// File description:
// Class for IPC client
//

#pragma once

#include "Data.hpp"
#include "Network/ANetwork.hpp"
#include "Network/Server/Server.hpp"

namespace Network {
    class Client : public ANetwork {
       public:
        Client(int fd);

        [[nodiscard]] bool send(const plazza::order_t &data);
        [[nodiscard]] bool receive() override;

        [[nodiscard]] const plazza::order_t &getData() const;

       private:
        plazza::order_t _data;
    };
}  // namespace Network
