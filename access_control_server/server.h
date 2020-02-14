#ifndef SERVER_H
#define SERVER_H
#include "json.hpp"
#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"

using JSON = nlohmann::json;


class Server
{
public:
    Server();
    void init_server();

private:
    int serverID{1};
    bool exists(const JSON&, const std::string&);

};

#endif // SERVER_H
