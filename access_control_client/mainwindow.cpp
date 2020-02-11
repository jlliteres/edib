#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.hpp"

using JSON = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->btnClose->setEnabled(false);
    m_ui->btnOpen->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::init_server(QString url)
{
    m_webSocket.setUrl(url.toStdString());
    m_webSocket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << msg->str << std::endl;

                JSON receivedObject = JSON::parse(msg->str, nullptr, false);
                if(receivedObject["error"] == 0)
                {
                    std::cout << "ENTER" << std::endl;

                }
                add_log(QString::fromStdString(msg->str));
            }
        }
    );

    m_webSocket.start();

    add_log("Connection open: " + url);
}

void MainWindow::add_log(QString item)
{
    m_ui->log->addItem(item);
}


void MainWindow::on_btnClose_clicked()
{
    m_webSocket.stop();
    add_log("Connection closed");
    m_ui->btnClose->setEnabled(false);
    m_ui->btnOpen->setEnabled(true);
}

void MainWindow::on_btnSend_clicked()
{
    JSON message;
    message["action"] = "register";
    message["clientID"] = clientID++;
    message["passID"] = "1234";
    std::cout << message.dump() << std::endl;
    m_webSocket.send(message.dump());
}

void MainWindow::on_btnOpen_clicked()
{
    init_server(serverUrl);
    m_ui->btnClose->setEnabled(true);
    m_ui->btnOpen->setEnabled(false);

}
