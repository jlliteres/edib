#ifndef HANDLER_H
#define HANDLER_H
#include "json.hpp"

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

};

#endif // HANDLER_H
