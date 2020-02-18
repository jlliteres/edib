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

bool Database::login(const QString password)
{
    bool isOK = m_database.open();
    bool result{false};
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    QSqlQuery query;
    query.prepare("SELECT * from login WHERE password = crypt(?, password);");
    query.addBindValue(password);

    query.exec();

    if(query.size() == 1)
    {
       result = true;
    }

    m_database.close();
    return result;
}

JSON Database::load()
{
    bool isOK = m_database.open();
    JSON dbJSON;
    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    QSqlQuery query;
    query.prepare("SELECT * from matricula;");
    //query.addBindValue(QString::fromStdString(key));

    query.exec();
    while(query.next())
    {
        QString value = query.value(1).toString();
        qDebug() << value;
        //dbJSON["user"] += value.toStdString();
    }

    m_database.close();

    return dbJSON;
}
