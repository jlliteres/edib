#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "json.hpp"

using JSON = nlohmann::json;

class Database
{
public:
    Database();
    JSON load();
    bool login(const std::string, const std::string);
    QSqlDatabase m_database;
};

#endif // DATABASE_H
