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
        QSqlQuery query;
        query.prepare("SELECT * from login WHERE user_id = ? AND password = crypt(?, password) AND active = 1;");
        query.addBindValue(logUser);
        query.addBindValue(password);

        query.exec();

        if(query.size() == 1)
        {
           QSqlQuery query2;
           query2.prepare("INSERT INTO log (user_id) VALUES (?);");
           query2.addBindValue(logUser);
           query2.exec();
           result = true;
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
        QSqlQuery query;
        query.prepare("SELECT * from login WHERE user_id = ? AND password = crypt(?, password) AND active = 1;");
        query.addBindValue(logUser);
        query.addBindValue(password);

        query.exec();

        if(query.size() == 1)
        {
           QSqlQuery query2;
           query2.prepare("UPDATE log SET exit_time = now()::timestamp WHERE user_id = ? AND exit_time IS NULL;");
           query2.addBindValue(logUser);
           query2.exec();
           result = true;
        }//end if
    }//end if

    m_database.close();
    return result;
}

JSON Database::load()
{
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();
    qDebug() << isOK;

    if(isOK)
    {
        QSqlQuery query;
        query.prepare("SELECT user_id, name FROM users WHERE user_id NOT IN (SELECT user_id FROM log WHERE exit_time IS NULL);");
        //query.addBindValue(QString::fromStdString(key));

        query.exec();
        while(query.next())
        {
            JSON queryJSON;
            int id = query.value(0).toInt();
            QString name = query.value(1).toString().simplified();
            queryJSON["userID"] = id;
            queryJSON["name"] = name.toStdString();

            dbJSON["user"] += queryJSON;

        }
    }//end if
    m_database.close();

    return dbJSON;
}
