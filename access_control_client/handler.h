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
    void load(JSON, MainWindow&);

};

#endif // HANDLER_H
