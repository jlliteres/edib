#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "handler.h"
#include <QDebug>
#include <QMessageBox>

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
    m_ui->tblOUT->setColumnHidden(0, true);
    m_ui->tblOUT->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_ui->tblIN->setColumnHidden(0, true);
    m_ui->tblIN->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    m_ui->btnClose->setEnabled(false);
    m_ui->btnSend->setEnabled(false);
    m_ui->btnOpen->setEnabled(true);
    m_ui->btnLock->setEnabled(false);
}

void MainWindow::on_btnSend_clicked()
{
    JSON message;
    message["action"] = "load";
    message["clientID"] = m_clientID++;

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

    m_ui->tblOUT->setRowCount(0);

    m_ui->tblOUT->setHorizontalHeaderLabels(QStringList() << "ID" << "Name");

    for(QString id : listID)
    {
        QTableWidgetItem *itemID = new QTableWidgetItem(id);
        QTableWidgetItem *name = new QTableWidgetItem(listName.value(listID.indexOf(id)));
        itemID->setTextAlignment(Qt::AlignCenter);
        name->setTextAlignment(Qt::AlignCenter);

        m_ui->tblOUT->insertRow(row);
        m_ui->tblOUT->setItem(row, column, itemID);
        column++;
        m_ui->tblOUT->setItem(row, column, name);
        row++;
        column = 0;
    }
    m_ui->tblOUT->sortByColumn(1, Qt::AscendingOrder);
    m_ui->tblOUT->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::enter()
{
    m_ui->tblIN->insertRow(m_ui->tblIN->rowCount());
    m_ui->tblIN->setItem(m_ui->tblIN->rowCount() - 1 , 0, m_ui->tblOUT->item(m_ui->tblOUT->currentRow(), 0)->clone());
    m_ui->tblIN->setItem(m_ui->tblIN->rowCount() - 1, 1, m_ui->tblOUT->currentItem()->clone());

    m_ui->tblOUT->removeRow(m_ui->tblOUT->currentRow());

    m_ui->tblOUT->sortByColumn(1, Qt::AscendingOrder);
    m_ui->tblIN->sortByColumn(1, Qt::AscendingOrder);
}

void MainWindow::exit()
{
    m_ui->tblOUT->insertRow(m_ui->tblOUT->rowCount());
    m_ui->tblOUT->setItem(m_ui->tblOUT->rowCount() - 1 , 0, m_ui->tblIN->item(m_ui->tblIN->currentRow(), 0)->clone());
    m_ui->tblOUT->setItem(m_ui->tblOUT->rowCount() - 1, 1, m_ui->tblIN->currentItem()->clone());

    m_ui->tblIN->removeRow(m_ui->tblIN->currentRow());

    m_ui->tblOUT->sortByColumn(1, Qt::AscendingOrder);
    m_ui->tblIN->sortByColumn(1, Qt::AscendingOrder);
}

void MainWindow::warningMsg(QString msg)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Error");
    msgBox.setText(msg);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
}

bool MainWindow::exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}

void MainWindow::on_action_Exit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_filterOut_textChanged(const QString &filter)
{
    ///Filter table results
    for( int i = 0; i < m_ui->tblOUT->rowCount(); ++i )
    {
        bool match = false;
        for( int j = 0; j < m_ui->tblOUT->columnCount(); ++j )
        {
            QTableWidgetItem *item = m_ui->tblOUT->item( i, j );
            if( item->text().contains(filter) )
            {
                match = true;
            }
        }
        m_ui->tblOUT->setRowHidden( i, !match );
    }
}

void MainWindow::on_filterIn_textChanged(const QString &filter)
{
    ///Filter table results
    for( int i = 0; i < m_ui->tblIN->rowCount(); ++i )
    {
        bool match = false;

        QTableWidgetItem *item = m_ui->tblIN->item( i, 1 );
        if( item->text().contains(filter) )
        {
            match = true;
        }

        m_ui->tblIN->setRowHidden( i, !match );
    }
}

void MainWindow::on_btnEnter_clicked()
{
    if(m_ui->tblOUT->currentItem() != nullptr)
    {
        qDebug() << "item selected";

        Login *login{new Login()};
        login->show();
        login->setModal(true);
        login->setUser(m_ui->tblOUT->currentItem()->text());

        connect(login, &Login::accepted, [this, login](){
            JSON loginJSON;
            loginJSON["clientID"] = m_clientID++;
            loginJSON["action"] = "enter";
            loginJSON["user"] = m_ui->tblOUT->item(m_ui->tblOUT->currentRow(), 0)->text().toInt();
            loginJSON["password"] = login->password();
            qDebug() << QString::fromStdString(loginJSON.dump());

            m_webSocket.send(loginJSON.dump());
        });


    }
}

void MainWindow::on_btnExit_clicked()
{
    if(m_ui->tblIN->currentItem() != nullptr)
    {
        qDebug() << "item selected";

        Login *login{new Login()};
        login->show();
        login->setModal(true);
        login->setUser(m_ui->tblIN->currentItem()->text());

        connect(login, &Login::accepted, [this, login](){
            JSON loginJSON;
            loginJSON["clientID"] = m_clientID++;
            loginJSON["action"] = "exit";
            loginJSON["user"] = m_ui->tblIN->item(m_ui->tblIN->currentRow(), 0)->text().toInt();
            loginJSON["password"] = login->password();
            qDebug() << QString::fromStdString(loginJSON.dump());

            m_webSocket.send(loginJSON.dump());
        });


    }
}
