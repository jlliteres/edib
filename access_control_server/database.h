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
    bool admin(const std::string, const std::string);
    bool enter(const int, const std::string);
    bool exit(const int, const std::string);
    bool addUser(const std::string, const std::string);
    bool modify(const int, const std::string, const std::string);

    QSqlDatabase m_database;
};

#endif // DATABASE_H
