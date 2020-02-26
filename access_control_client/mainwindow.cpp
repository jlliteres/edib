#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "handler.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    this->setWindowTitle("Access Control");

    ///Buttons
    m_ui->btnClose->setEnabled(false);
    m_ui->btnSend->setEnabled(false);
    m_ui->btnOpen->setEnabled(true);
    m_ui->btnAdd->setEnabled(false);
    m_ui->btnLock->setEnabled(false);
    m_ui->btnDelete->setEnabled(false);

    ///Menu buttons
    m_ui->actionS_tatus->setEnabled(false);

    ///Table
    //m_ui->tblIN->setColumnHidden(0, true);
    m_ui->tblIN->setColumnWidth(1, 200);

    m_serverUrl = "ws://localhost:9900/";
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_btnOpen_clicked()
{
    init_server(m_serverUrl);

}

void MainWindow::on_btnClose_clicked()
{
    lock();
    m_webSocket.stop();
    m_clientID = 1;
    add_log("Connection closed");
    m_ui->btnClose->setEnabled(false);
    m_ui->btnSend->setEnabled(false);
    m_ui->btnOpen->setEnabled(true);
    m_ui->btnLock->setEnabled(false);
}

void MainWindow::on_btnSend_clicked()
{
    JSON message;
    message["action"] = "load";
    //message["action"] = "register";
    message["clientID"] = m_clientID++;
    message["passID"] = "1234";
    std::cout << message.dump() << std::endl;
    m_webSocket.send(message.dump());
}

void MainWindow::on_btnLock_clicked()
{

///Open login dialog
   if(m_isLocked)
   {

       Login *login{new Login()};
       login->show();
       login->setModal(true);

///Send admin login to server
       connect(login, &Login::accepted, [this, login](){
           JSON loginJSON;
           loginJSON["clientID"] = m_clientID++;
           loginJSON["action"] = "admin";
           loginJSON["user"] = login->user();
           loginJSON["password"] = login->password();
           qDebug() << QString::fromStdString(loginJSON.dump());

           m_webSocket.send(loginJSON.dump());
       });

   }
   else
   {
       lock();
   }//end if
}

void MainWindow::unlock()
{
    m_ui->btnLock->setText("Lock");
    m_ui->btnAdd->setEnabled(true);
    m_ui->btnDelete->setEnabled(true);
    m_ui->actionS_tatus->setEnabled(true);
    m_isLocked = false;
}

void MainWindow::lock()
{
    m_ui->actionS_tatus->setEnabled(false);
    m_ui->btnAdd->setEnabled(false);
    m_ui->btnDelete->setEnabled(false);
    m_ui->btnLock->setText("Unlock...");
    m_isLocked = true;
}

void MainWindow::init_server(QString url)
{
    m_webSocket.setUrl(url.toStdString());
    m_webSocket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Open)
            {
                m_ui->btnClose->setEnabled(true);
                m_ui->btnOpen->setEnabled(false);
                m_ui->btnSend->setEnabled(true);
                m_ui->btnLock->setEnabled(true);
            }

            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << msg->str << std::endl;

                JSON receivedObject = JSON::parse(msg->str, nullptr, false);

                if(receivedObject.is_discarded())
                {
                    qDebug() << "JSON no válido";
                }
                else
                {///JSON válido
                    if(exists(receivedObject, "action"))
                    {
                        Handler handler;

                        handler.responseHandler(receivedObject, *this);

                    }//end if
                }//end if

                add_log(QString::fromStdString(msg->str));
            }
        }
    );

    m_webSocket.start();

    //add_log("Connection open: " + url);
}

void MainWindow::fillTable(QStringList listID, QStringList listName)
{
    int row{0};
    int column{0};
    qDebug() << "Fill table";

    for(QString id : listID)
    {
        QTableWidgetItem *itemID = new QTableWidgetItem(id);
        QTableWidgetItem *name = new QTableWidgetItem(listName.value(listID.indexOf(id)));

        m_ui->tblIN->insertRow(row);
        m_ui->tblIN->setItem(row, column, itemID);
        column++;
        m_ui->tblIN->setItem(row, column, name);
        row++;
        column = 0;
    }

}

bool MainWindow::exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}

void MainWindow::add_log(QString item)
{
    m_ui->log->addItem(item);
}


void MainWindow::on_action_Exit_triggered()
{
    QCoreApplication::quit();
}
