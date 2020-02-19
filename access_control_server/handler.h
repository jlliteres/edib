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
    JSON regist(const JSON&);
    JSON load(const JSON&);
    JSON login(JSON);

};

#endif // HANDLER_H
