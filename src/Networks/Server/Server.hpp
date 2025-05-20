//
// EPITECH PROJECT, 2025
// Server
// File description:
// Server
//

#pragma once

#include "Networks/ANetwork.hpp"
#include <map>
#include <sched.h>


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

        [[nodiscard]] bool send(const std::string &data) override;
        [[nodiscard]] bool receive() override;

        [[nodiscard]] bool sendTo(ClientId id, const data_t &data);

        [[nodiscard]] const std::string &getData() const;
        void closeClient(ClientId id);
        void closeAll();

       private:
        std::map<ClientId, int> _clients;
        std::string _data;
        ClientId _nextId = 0;
    };
}  // namespace Network
