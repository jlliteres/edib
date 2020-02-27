#ifndef HANDLER_H
#define HANDLER_H
#include "json.hpp"
#include "database.h"

using JSON = nlohmann::json;

class Handler
{
public:
    Handler();
    JSON responseHandler(const JSON&, const int);

private:
    JSON enter(const JSON&, int user, std::string password);
    JSON exit(const JSON&, int user, std::string password);
    JSON load(const JSON&);
    JSON admin(JSON, std::string user, std::string password);
    JSON add(JSON, std::string user, std::string password);
    Database m_database;


};

#endif // HANDLER_H
