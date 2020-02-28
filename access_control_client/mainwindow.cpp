#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "adduser.h"
#include "handler.h"

#include <QDebug>
#include <QMessageBox>
#include <QStringList>

/*
 * ADMIN LOGIN -> user: admin, password: admin.
 *
 * USER LOGIN -> user: Josep, password: 1234,
 *               user: Maria, password: 1111,
 *               user: Catalina, password: 2222.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    this->setWindowTitle("Access Control");

    ///Buttons
    m_ui->btnClose->setEnabled(false);
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

    connect(m_ui->tblIN,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this, SLOT(on_btnExit_clicked()));
    connect(m_ui->tblOUT,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this, SLOT(on_btnEnter_clicked()));
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
            ///Load info on open connection
            if (msg->type == ix::WebSocketMessageType::Open)
            {
                m_ui->btnClose->setEnabled(true);
                m_ui->btnOpen->setEnabled(false);
                m_ui->btnLock->setEnabled(true);
                load();
            }

            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "Msg received: " << msg->str << std::endl;

                JSON receivedObject = JSON::parse(msg->str, nullptr, false);

                if(receivedObject.is_discarded())
                {
                    qDebug() << "JSON no válido";
                }
                else
                {///Valid JSON
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

void MainWindow::load()
{
    ///Send JSON to server to LOAD info from database
    JSON message;
    message["action"] = "load";
    message["clientID"] = m_clientID++;

    m_webSocket.send(message.dump());
}

void MainWindow::unlock()
{
    ///Visual changes for admin privileges
    m_ui->btnLock->setText("Lock");
    m_ui->btnAdd->setEnabled(true);
    m_ui->btnDelete->setEnabled(true);
    m_ui->actionS_tatus->setEnabled(true);
    m_isLocked = false;
}

void MainWindow::lock()
{
    ///Visual changes for non-admin privileges
    m_ui->btnLock->setText("Unlock...");
    m_ui->actionS_tatus->setEnabled(false);
    m_ui->btnAdd->setEnabled(false);
    m_ui->btnDelete->setEnabled(false);
    m_isLocked = true;
}

void MainWindow::fillTable(QStringList listID, QStringList listName, int switcher)
{
    qRegisterMetaType<QVector<int>>("QVector<int>");
    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");
    ///Fill the tables with the database data
    QTableWidget* table;
    int row{0};
    int column{0};

    /// 'swicther' sets the active table
    if (switcher == 0)
    {
        table = m_ui->tblOUT;
    }
    else
    {
        table = m_ui->tblIN;
    }//end if

    table->setRowCount(0);

    table->setHorizontalHeaderLabels(QStringList() << "ID" << "Name");

    for(QString id : listID)
    {
        QTableWidgetItem *itemID = new QTableWidgetItem(id);
        QTableWidgetItem *name = new QTableWidgetItem(listName.value(listID.indexOf(id)));

        table->insertRow(row);
        table->setItem(row, column, itemID);
        column++;
        table->setItem(row, column, name);
        row++;
        column = 0;
        itemID->setTextAlignment(Qt::AlignCenter);
        name->setTextAlignment(Qt::AlignCenter);
    }

    table->sortByColumn(1, Qt::AscendingOrder);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::logUser(int switcher)
{
    ///Move user from table to table
    QTableWidget* tableStart;
    QTableWidget* tableEnd;
    /// 'swicther' sets the START table and the END table
    if (switcher == 0)
    {
        tableStart = m_ui->tblOUT;
        tableEnd = m_ui->tblIN;
    }
    else
    {
        tableStart = m_ui->tblIN;
        tableEnd = m_ui->tblOUT;
    }//end if

    tableEnd->insertRow(tableEnd->rowCount());
    tableEnd->setItem(tableEnd->rowCount() - 1 , 0, tableStart->item(tableStart->currentRow(), 0)->clone());
    tableEnd->setItem(tableEnd->rowCount() - 1, 1, tableStart->currentItem()->clone());

    tableStart->removeRow(tableStart->currentRow());

    tableStart->sortByColumn(1, Qt::AscendingOrder);
    tableEnd->sortByColumn(1, Qt::AscendingOrder);
}

void MainWindow::loginUser(const QString& action, int switcher)
{
    QTableWidget* table;
    ///Show login window when ENTER or EXIT buttons are pressed and send JSON to server.
    /// 'swicther' sets the active table
    if (switcher == 0)
    {
        table = m_ui->tblOUT;
    }
    else
    {
        table = m_ui->tblIN;
    }//end if

    if(table->currentItem() != nullptr)
    {
        Login *login{new Login()};
        login->show();
        login->setUser(table->currentItem()->text());

        connect(login, &Login::accepted, [this, action, table, login](){
            JSON loginJSON;
            loginJSON["clientID"] = m_clientID++;
            loginJSON["action"] = action.toStdString();
            loginJSON["user"] = table->item(table->currentRow(), 0)->text().toInt();
            loginJSON["password"] = login->password();
            qDebug() << "JSON sent: " <<QString::fromStdString(loginJSON.dump());

            m_webSocket.send(loginJSON.dump());
        });

        delete login;
    }//end if

}

void MainWindow::filter(const QString& filter, int switcher)
{    
    ///Filter table results

    QTableWidget* table;

    if (switcher == 0)
    {
        table = m_ui->tblOUT;
    }
    else
    {
        table = m_ui->tblIN;
    }//end if

    ///Hide rows that don't match
    for( int i = 0; i < table->rowCount(); ++i )
    {
        bool match = false;
        for( int j = 0; j < table->columnCount(); ++j )
        {
            QTableWidgetItem *item = table->item( i, j );
            if( item->text().contains(filter) )
            {
                match = true;
            }//end if
        }
        table->setRowHidden( i, !match );
    }
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

void MainWindow::on_btnAdd_clicked()
{
    ///Open AddUser dialog
    AddUser *add{new AddUser()};
    add->show();

    ///Send new user to server
    connect(add, &Login::accepted, [this, add](){

            JSON loginJSON;
            loginJSON["clientID"] = m_clientID++;
            loginJSON["action"] = "add";
            loginJSON["user"] = add->user();
            loginJSON["password"] = add->password();
            qDebug() << QString::fromStdString(loginJSON.dump());

            m_webSocket.send(loginJSON.dump());
    });
    delete add;
}

void MainWindow::on_btnLock_clicked()
{

    ///Open login dialog
   if(m_isLocked)
   {
       Login *login{new Login()};
       login->show();

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

       delete login;
   }
   else
   {
       lock();
   }//end if

}

void MainWindow::on_action_Exit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_filterOut_textChanged(const QString &text)
{
    ///Filter table results
    filter(text, 0);
}

void MainWindow::on_filterIn_textChanged(const QString &text)
{
    ///Filter table results
    filter(text, 1);
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
    m_ui->btnOpen->setEnabled(true);
    m_ui->btnLock->setEnabled(false);
}

void MainWindow::on_btnEnter_clicked()
{
    loginUser("enter", 0);
}

void MainWindow::on_btnExit_clicked()
{
    loginUser("exit", 1);
}


