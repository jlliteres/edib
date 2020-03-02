/**
    @file handler.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title Handler object for server responses.
    @brief Object that manages server responses and determines the 'action'.
  */
#ifndef HANDLER_H
#define HANDLER_H

#include "json.hpp"
#include "mainwindow.h"

using JSON = nlohmann::json;

class Handler : public QObject
{
public:
    /**
     * @brief Handler Default constructor.
     */
    Handler();
    /**
     * @brief responseHandler Determines the 'action' of the given JSON and gives the response needed with functions.
     * @param receivedJSON JSON sent by the server.
     * @param main  Pointer to MainWindow object.
     */
    void responseHandler(const JSON& receivedJSON, MainWindow* main);

private:
    void load(JSON, MainWindow*);

};

#endif // HANDLER_H
