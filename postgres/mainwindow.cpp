#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("prueba");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("");
    bool isOK = db.open();

    qDebug() << db.lastError().text();

    qDebug() << isOK;

    QSqlQuery query;
    query.exec("SELECT * from matricula;");

    while(query.next())
    {
        int matriculaId = query.value(0).toInt();
        QString matricula = query.value(1).toString().simplified();
        qDebug() << matriculaId << matricula;
    }

    db.close();

    QSqlDatabase::removeDatabase("QPSQL");

}

MainWindow::~MainWindow()
{
    delete ui;
}
