#include "app.h"
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QSqlQuery>

App::App(QObject *parent) : QObject(parent)
{
    QTimer::singleShot(0, this, SLOT(run()));
}


void App::run()
{
    qDebug() << "running...";

    m_context.run(); // run
    if (m_context.shouldExit())
    {
        QCoreApplication::quit();
    } // end if

}

Db::~Db()
{
    if (m_db.isOpen())
    {
        m_db.close();
    } // end if
}

bool Db::insert()
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (name) VALUES (:name)");
    query.bindValue(":name", "prueba");
    bool result = query.exec();
    qDebug() << query.lastError().text();
    return result;
}

Db::Db()
{
    if (!QSqlDatabase::contains( "MyDb"))
    {
        m_db = QSqlDatabase::addDatabase("QPSQL", "MyDb");
    }
    else
    {
        m_db = QSqlDatabase::database("MyDb");
    } // end if
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setPassword("");

}

bool Db::select()
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM users WHERE user_id = :id");
    query.bindValue(":id", 1);

    bool result = query.exec();
    qDebug() << query.lastError().text();
    return result;
}

void Db::close()
{
    m_db.close();
}

bool Db::init()
{
    bool result = 0;

    m_db.close();
    m_db.setDatabaseName("template1");

    bool ok = m_db.open();

    if (ok)
    {

        qDebug() << "Borrando...";
        QSqlQuery q0("DROP DATABASE IF EXISTS tests", m_db);
        if (q0.lastError().type() == QSqlError::NoError)
        {
            qDebug() << "Creando...";
            QSqlQuery q1("CREATE DATABASE tests", m_db);
            if (q1.lastError().type() == QSqlError::NoError)
            {
                m_db.close();
                m_db.setDatabaseName("tests");
                m_db.open();

                /// Crea estructura en la base de datos
                QString sql {"CREATE TABLE users ( \
                    user_id     SERIAL, \
                    name    varchar(40), \
                    active int,\
                    PRIMARY KEY(user_id) \
                )"};

                qDebug() << "Iniciando...";
                QSqlQuery q2(sql, m_db);
                if (q2.lastError().type() == QSqlError::NoError)
                {
                    result = true;
                } // end if
            }
            else
            {
                qDebug() << "B:" << m_db.lastError().text();
            } // end if

        }
        else
        {
            qDebug() << "A:" << m_db.lastError().text();
        } // end if

    } // end if

    return result;
}

QSqlError Db::lastError()
{
    return m_db.lastError();
}

TEST_CASE("base datos #0")
{
    Db db;
    int ok = db.init();

    if (ok)
    {
        qDebug() << "DB UP AND RUNNING";

        SUBCASE("Insert #0")
        {
            CHECK( db.insert() == true );
        }

        SUBCASE("Select #0")
        {
            CHECK( db.select() == true );
        }
    }
    else
    {
        qDebug() << db.lastError().text();

    } // end if

}



