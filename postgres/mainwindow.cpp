#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("prueba");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("");
    bool isOK = db.open();

    //qDebug() << db.lastError().text();

    qDebug() << isOK;

    QSqlQuery query;
    query.exec("SELECT * FROM matricula");

    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString().simplified();


        qDebug() << id << name;
    }

    db.close();

}

MainWindow::~MainWindow()
{
    delete m_ui;
}
