//
// EPITECH PROJECT, 2025
// Server
// File description:
// Server
//

#pragma once

#include "Data.hpp"
#include "Network/ANetwork.hpp"
#include <map>
#include <poll.h>
#include <vector>

namespace Network {

enum class client_status: uint8_t {
    OK,
    NOK,
    DECO
};

    typedef struct status_s {
        int fd;
        client_status status;
    } status_t;

    typedef struct ClientInfo_s {
        int id;
        int clientFd;
    } ClientInfo_t;

    class Server : public ANetwork {
       public:
        Server();
        ~Server() override;

        ClientInfo_t acceptClient();

        bool send(const plazza::order_t &data);
        [[nodiscard]] status_t receive();

        bool sendTo(int id, const plazza::order_t &data);

        [[nodiscard]] const plazza::order_t &getData() const;
        std::vector<int> getIds();
        void closeClient(int id);
        void closeAll();

       private:
        std::map<int, int> _clients;
        plazza::order_t _data;
        int _nextId = 0;

        std::vector<struct pollfd> _getPfds();
    };
}  // namespace Network
