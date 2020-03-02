#include "handler.h"

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>

Handler::Handler()
{

}

void Handler::responseHandler(const JSON& receivedJSON, MainWindow* main)
{
    ///1) Get data

    std::string action = receivedJSON["action"];

    ///2) Data treatment

    if(action == "enter")
    {
        if(receivedJSON["error"] == 0)
        {
            main->logUser(0);
        }
        else
        {
            main->warningMsg("Invalid login credentials!");
        }//end if
    }
    else if (action == "load")
    {
        load(receivedJSON, main);
    }
    else if (action == "admin")
    {
        if(receivedJSON["error"] == 0)
        {
            main->unlock();
        }
        else
        {
            main->warningMsg("Invalid admin credentials!");
        }//end if
    }
    else if (action == "exit")
    {
        if(receivedJSON["error"] == 0)
        {
            main->logUser(1);
        }
        else
        {
            main->warningMsg("Invalid login credentials!");
        }//end if
    }
    else if (action == "add" || action == "modify" || action == "delete")
    {
        if(receivedJSON["error"] == 0)
        {
            main->load();
        }//end if
    }
    else if (action == "log")
    {
        QStringList listName;
        QStringList listEnter;
        QStringList listExit;

        for(auto& json : receivedJSON["list"]["log"].items())
        {
            JSON key = json.value();

            listName << QString::fromStdString(key["name"]);
            listEnter << QString::fromStdString(key["enter"]);
            listExit << QString::fromStdString(key["exit"]);

            std::cout << " ID: "<< key["name"] << " , enter: " << key["enter"] << std::endl;
        }

        main->fillLog(listName, listEnter, listExit);
    }//end if

}

void Handler::load(JSON receivedJSON, MainWindow* main)
{
    QStringList listID;
    QStringList listName;

    if (main->exists(receivedJSON["list"], "userOUT"))
    {
        for(auto& json : receivedJSON["list"]["userOUT"].items())
        {
            JSON key = json.value();

            listID << QString::number(key["userID"].get<int>());
            listName << QString::fromStdString(key["name"]);
            std::cout << " ID: "<< key["userID"] << " , name: " << key["name"] << std::endl;
        }
    }//end if

    if(!listID.isEmpty())
    {
        main->fillTable(listID, listName, 0);
        listID.clear();
        listName.clear();
    }//end if

    if (main->exists(receivedJSON["list"], "userIN"))
    {
        for(auto& json : receivedJSON["list"]["userIN"].items())
        {
            JSON key = json.value();

            listID << QString::number(key["userID"].get<int>());
            listName << QString::fromStdString(key["name"]);
            std::cout << " ID: "<< key["userID"] << " , name: " << key["name"] << std::endl;
        }
    }//end if

    if(!listID.isEmpty())
    {
        main->fillTable(listID, listName, 1);
    }//end if
}

