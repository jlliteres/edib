#include "database.h"

Database::Database()
{

    m_database = QSqlDatabase::addDatabase("QPSQL");
    m_database.setHostName("localhost");
    m_database.setDatabaseName("prueba");
    m_database.setPort(5432);
    m_database.setUserName("postgres");
    m_database.setPassword("");
}

bool Database::modify(const int id, const std::string logName, const std::string logPassword)
{
    QString password = QString::fromStdString(logPassword);
    QString name = QString::fromStdString(logName);

    bool result{false};
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    if(isOK)
    {
        QSqlQuery query;
        query.prepare("UPDATE users SET name = ? WHERE user_id = ?;");
        query.addBindValue(name);
        query.addBindValue(id);

        result = query.exec();

        if(password != "")
        {
            query.prepare("UPDATE login SET active = 0 WHERE user_id = ? AND active = 1;");
            query.addBindValue(id);

            if(query.exec())
            {
                query.prepare("INSERT INTO login (user_id, password) VALUES (?, crypt(?, gen_salt('bf')));");
                query.addBindValue(id);
                query.addBindValue(password);
                result = query.exec();
            }
        }//end if
    }//end if

    m_database.close();
    return result;
}

bool Database::admin(const std::string logUser, const std::string logPassword)
{
    QString user = QString::fromStdString(logUser);
    QString password = QString::fromStdString(logPassword);

    bool result{false};
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    if(isOK)
    {
        ///Check if it's a valid and unique admin login.
        QSqlQuery query;
        query.prepare("SELECT * from admin WHERE username = ? AND password = crypt(?, password);");
        query.addBindValue(user);
        query.addBindValue(password);

        query.exec();

        if(query.size() == 1)
        {
           result = true;
        }//end if
    }//end if

    m_database.close();
    return result;
}
bool Database::addUser(const std::string logName, const std::string logPassword)
{
    QString password = QString::fromStdString(logPassword);
    QString name = QString::fromStdString(logName);
    bool result{false};
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    if(isOK)
    {
        QSqlQuery query;
        ///Check if there's no current user with same name.
        query.prepare("SELECT user_id FROM users WHERE name = ?;");
        query.addBindValue(name);

        query.exec();
        qDebug() << query.size();

        ///query returns 0 if empty. Insert user and new login info for user.
        if(query.size() == 0)
        {
            query.prepare("INSERT INTO users (name) VALUES (?);");
            query.addBindValue(name);

            if(query.exec())
            {
                query.prepare("INSERT INTO login (user_id, password) VALUES ((SELECT user_id FROM users WHERE name = ?), crypt(?, gen_salt('bf')));");
                query.addBindValue(name);
                query.addBindValue(password);
                result = query.exec();
            }//end if
        }//end if
    }//end if

    m_database.close();
    return result;
}

bool Database::enter(const int logUser, const std::string logPassword)
{
    QString password = QString::fromStdString(logPassword);
    bool result{false};
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    if(isOK)
    {
        ///Check if login info is valid and insert new user log.
        QSqlQuery query;
        query.prepare("SELECT * from login WHERE user_id = ? AND password = crypt(?, password) AND active = 1;");
        query.addBindValue(logUser);
        query.addBindValue(password);

        query.exec();

        if(query.size() == 1)
        {
           query.prepare("INSERT INTO log (user_id) VALUES (?);");
           query.addBindValue(logUser);
           result = query.exec();
        }//end if
    }//end if

    m_database.close();
    return result;
}

bool Database::exit(const int logUser, const std::string logPassword)
{
    QString password = QString::fromStdString(logPassword);
    bool result{false};
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    if(isOK)
    {
        ///Check if login info is valid and update exit_time.
        QSqlQuery query;
        query.prepare("SELECT * from login WHERE user_id = ? AND password = crypt(?, password) AND active = 1;");
        query.addBindValue(logUser);
        query.addBindValue(password);

        query.exec();

        if(query.size() == 1)
        {
           query.prepare("UPDATE log SET exit_time = now()::timestamp WHERE user_id = ? AND exit_time IS NULL;");
           query.addBindValue(logUser);
           result = query.exec();
        }//end if
    }//end if

    m_database.close();
    return result;
}

JSON Database::log()
{
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();
    qDebug() << isOK;

    if(isOK)
    {
        ///Load all info from users that are OUT.
        QSqlQuery query;
        query.prepare("SELECT name, enter_time, exit_time FROM users JOIN log using(user_id);");

        query.exec();
        while(query.next())
        {
            JSON queryJSON;
            QString name = query.value(0).toString().simplified();
            QString enter = query.value(1).toString().simplified();
            QString exit = query.value(2).toString().simplified();

            queryJSON["name"] = name.toStdString();
            queryJSON["enter"] = enter.toStdString();
            queryJSON["exit"] = exit.toStdString();

            dbJSON["log"] += queryJSON;
        }

    }//end if
    m_database.close();

    return dbJSON;
}

JSON Database::load()
{
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();
    qDebug() << isOK;

    if(isOK)
    {
        ///Load all info from users that are OUT.
        QSqlQuery query;
        query.prepare("SELECT user_id, name FROM users WHERE user_id NOT IN (SELECT user_id FROM log WHERE exit_time IS NULL) AND active = 1;");

        query.exec();
        while(query.next())
        {
            JSON queryJSON;
            int id = query.value(0).toInt();
            QString name = query.value(1).toString().simplified();
            queryJSON["userID"] = id;
            queryJSON["name"] = name.toStdString();

            dbJSON["userOUT"] += queryJSON;
        }
        ///Load all info from users that are IN.
        query.prepare("SELECT DISTINCT user_id, name FROM log JOIN users USING (user_id) WHERE exit_time IS NULL AND user_id NOT IN (SELECT user_id FROM users WHERE active = 0);");

        query.exec();
        while(query.next())
        {
            JSON queryJSON;
            int id = query.value(0).toInt();
            QString name = query.value(1).toString().simplified();
            queryJSON["userID"] = id;
            queryJSON["name"] = name.toStdString();

            dbJSON["userIN"] += queryJSON;
        }
    }//end if
    m_database.close();

    return dbJSON;
}

bool Database::deleteUser(const int id)
{

    bool result{false};
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    if(isOK)
    {
        QSqlQuery query;
        query.prepare("UPDATE users SET active = 0 WHERE user_id = ?;");
        query.addBindValue(id);

        result = query.exec();
    }//end if

    m_database.close();
    return result;

}
