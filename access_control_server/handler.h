/**
    @file handler.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title Handler object for client messages.
    @brief Object that determines the 'action' of the given message and uses the Database object to give solutions to these messages.
  */
#ifndef HANDLER_H
#define HANDLER_H
#include "json.hpp"
#include "database.h"

using JSON = nlohmann::json;

class Handler
{
public:
    /**
     * @brief Handler Default constructor.
     */
    Handler();
    /**
     * @brief responseHandler Checks the 'action' with 'if' and 'else if' statements and uses functions for each 'action'.
     * @param receivedJSON JSON sent by the client where 'action' needs to be checked.
     * @param serverID Server message ID.
     * @return Returns a response JSON depending of the 'action'
     */
    JSON responseHandler(const JSON& receivedJSON, const int serverID);

private:
    JSON enter(const JSON&, int user, std::string password);
    JSON exit(const JSON&, int user, std::string password);
    JSON load(const JSON&);
    JSON log(const JSON&);
    JSON deleteUser(JSON, int user);
    JSON admin(JSON, std::string user, std::string password);
    JSON add(JSON, std::string user, std::string password);
    JSON modify(JSON, int, std::string user, std::string password);
    Database m_database;


};

#endif // HANDLER_H
