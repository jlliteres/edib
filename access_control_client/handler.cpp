#include "handler.h"

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>

Handler::Handler()
{

}

void Handler::responseHandler(const JSON& receivedJSON, MainWindow& main)
{
    ///1) Get data

    std::string action = receivedJSON["action"];

    ///2) Data treatment

    if(action == "enter")
    {
        if(receivedJSON["error"] == 0)
        {
            main.logUser(0);
        }
        else
        {
            main.warningMsg("Invalid login credentials!");
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
            main.unlock();
        }
        else
        {
            main.warningMsg("Invalid admin credentials!");
        }//end if
    }
    else if (action == "exit")
    {
        if(receivedJSON["error"] == 0)
        {
            main.logUser(1);
        }
        else
        {
            main.warningMsg("Invalid login credentials!");
        }//end if
    }
    else if (action == "add" || action == "modify")
    {
        if(receivedJSON["error"] == 0)
        {
            main.load();
        }//end if
    }//end if

}

void Handler::load(JSON receivedJSON, MainWindow& main)
{
    QStringList listID;
    QStringList listName;

    if (main.exists(receivedJSON["list"], "userOUT"))
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
        main.fillTable(listID, listName, 0);
        listID.clear();
        listName.clear();
    }//end if

    if (main.exists(receivedJSON["list"], "userIN"))
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
        main.fillTable(listID, listName, 1);
    }//end if
}

