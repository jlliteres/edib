#ifndef HANDLER_H
#define HANDLER_H
#include "json.hpp"

using JSON = nlohmann::json;

class Handler
{
public:
    Handler();
    JSON responseHandler(const JSON&);

private:
    JSON regist(const JSON&);
};

#endif // HANDLER_H
