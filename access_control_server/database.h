/**
    @file database.h
    @version 1.0
    @date 02/03/2020
    @author Josep Lliteres
    @title Object for database management.
    @brief Object with functions for database connection and query.
  */
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
    /**
     * @brief Database Default constructor
     */
    Database();
    /**
     * @brief load Function to load all the user results and return them into JSON.
     * @return JSON to return.
     */
    JSON load();
    /**
     * @brief log Function to load all the results of the log table and return them into JSON.
     * @return JSON to return.
     */
    JSON log();
    /**
     * @brief admin Checks if the admin login is correct.
     * @param username Username to check.
     * @param password Password to check.
     * @return Returns true if correct.
     */
    bool admin(const std::string username, const std::string password);
    /**
     * @brief enter Checks if the user login is valid.
     * @param id User id to check.
     * @param password Password to check.
     * @return Returns true if correct.
     */
    bool enter(const int id, const std::string password);
    /**
     * @brief exit Checks if the user login is valid.
     * @param id User id to check.
     * @param password Password to check.
     * @return Returns true if correct.
     */
    bool exit(const int id, const std::string password);
    /**
     * @brief addUser Inserts a new user to the database.
     * @param name Name to insert.
     * @param password Password to insert.
     * @return Returns true if correct.
     */
    bool addUser(const std::string name, const std::string password);
    /**
     * @brief modify Updates the user info.
     * @param id User id to update.
     * @param name New name for user.
     * @param password New password for user, can be empty.
     * @return Returns true if correct.
     */
    bool modify(const int id, const std::string name, const std::string password);
    /**
     * @brief deleteUser Sets given user to inactive.
     * @param id User id to update.
     * @return Returns true if correct.
     */
    bool deleteUser(const int id);


private:

    QSqlDatabase m_database;
    void processLine(std::string line);
    void readFile();
    void loadProperties();

    std::map<std::string, std::string> m_properties;

};

#endif // DATABASE_H
