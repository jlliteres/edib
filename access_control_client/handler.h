#ifndef HANDLER_H
#define HANDLER_H
#include "json.hpp"
#include "mainwindow.h"


using JSON = nlohmann::json;

class Handler
{
public:
    Handler();
    void responseHandler(const JSON&, MainWindow&);

private:
    JSON regist(const JSON&);
    JSON load(const JSON&);
    JSON admin(JSON, std::string user, std::string password);

};

#endif // HANDLER_H
