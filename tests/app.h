#ifndef APP_H
#define APP_H

#include "doctest.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

class Db
{
    QSqlDatabase m_db;
public:
    Db();
    ~Db();
    bool init();
    void close();
    QSqlError lastError();
    bool insert();
    bool select();
};

class App : public QObject
{
    Q_OBJECT

    doctest::Context m_context;

public:
    App(QObject *parent = nullptr);

public slots:
    void run();
};

#endif // APP_H
