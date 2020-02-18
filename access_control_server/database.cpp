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

bool Database::load(const std::string key)
{
    bool isOK = m_database.open();

    qDebug() << m_database.lastError().text();

    qDebug() << isOK;

    QSqlQuery query;
    query.prepare("SELECT * from matricula WHERE matricula = ?;");
    query.addBindValue(QString::fromStdString(key));

    /*query.exec();
    while(query.next())
    {
        if(query.size() > 0) return true;
    }
*/
    m_database.close();

    return true;
}
