/**
    @file server.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title Object for server management.
    @brief Object for server connection and message recieving.
  */
#ifndef SERVER_H
#define SERVER_H
#include "json.hpp"
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "handler.h"
#include <iostream>

using JSON = nlohmann::json;


class Server
{
public:
    /**
     * @brief Server Default constructor.
     */
    Server();
    /**
     * @brief init_server Initializes server.
     */
    void init_server();

private:
    int serverID{1};
    bool exists(const JSON&, const std::string&);
    Handler m_handler;

};

#endif // SERVER_H
