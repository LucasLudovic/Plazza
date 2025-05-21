//
// EPITECH PROJECT, 2025
// Server
// File description:
// Server
//

#pragma once

#include "Networks/ANetwork.hpp"
#include <map>
#include <poll.h>
#include <vector>

namespace Network {

    using ClientId = pid_t;

    typedef struct ClientInfo_s {
        ClientId id;
        int clientFd;
    } ClientInfo_t;

    class Server : public ANetwork {
       public:
        Server();
        ~Server() override;

        ClientInfo_t acceptClient(ClientId id);

        [[nodiscard]] bool send(const data_t &data) override;
        [[nodiscard]] bool receive() override;

        [[nodiscard]] bool sendTo(ClientId id, const data_t &data);

        [[nodiscard]] const data_t &getData() const override;
        void closeClient(ClientId id);
        void closeAll();

       private:
        std::map<ClientId, int> _clients;
        data_t _data;

        std::vector<struct pollfd> _getPfds();
        std::vector<ClientId> _getIds();
    };
}  // namespace Network
