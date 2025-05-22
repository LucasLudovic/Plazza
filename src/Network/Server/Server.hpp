//
// EPITECH PROJECT, 2025
// Server
// File description:
// Server
//

#pragma once

#include "Network/ANetwork.hpp"
#include <map>
#include <poll.h>
#include <vector>

namespace Network {

    typedef struct ClientInfo_s {
        int id;
        int clientFd;
    } ClientInfo_t;

    class Server : public ANetwork {
       public:
        Server();
        ~Server() override;

        ClientInfo_t acceptClient();

        [[nodiscard]] bool send(const data_t &data) override;
        [[nodiscard]] bool receive() override;

        [[nodiscard]] bool sendTo(int id, const data_t &data);

        [[nodiscard]] const data_t &getData() const override;
        void closeClient(int id);
        void closeAll();

       private:
        std::map<int, int> _clients;
        data_t _data;
        int _nextId = 0;

        std::vector<struct pollfd> _getPfds();
        std::vector<int> _getIds();
    };
}  // namespace Network
