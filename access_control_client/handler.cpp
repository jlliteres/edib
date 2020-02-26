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
            main.enter();
        }
        else
        {
            main.warningMsg("Invalid login credentials!");
        }//end if
    }
    else if (action == "load")
    {
        QStringList listID;
        QStringList listName;
        for(auto& json : receivedJSON["list"]["user"].items())
        {
            JSON key = json.value();

            listID << QString::number(key["userID"].get<int>());
            listName << QString::fromStdString(key["name"]);
            std::cout << " ID: "<< key["userID"] << " , name: " << key["name"] << std::endl;

        }
        main.fillTable(listID, listName);

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
            main.exit();
        }
        else
        {
            main.warningMsg("Invalid login credentials!");
        }//end if
    }
    else if (action == "")
    {

    }

}


JSON Handler::admin(JSON responseJSON, std::string user, std::string password)
{
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "admin";

    ///No valid login, error = 1
    if(true)
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }

    return dbJSON;
}

JSON Handler::load(const JSON& responseJSON)
{

    return responseJSON;
}

JSON Handler::regist(const JSON& responseJSON)
{
    //Database db;
    JSON registJSON = responseJSON;
    ///Check database
    /*if(db.load(responseJSON["passID"]))
    {
        registJSON["response"] = "enter";
        registJSON["error"] = 0;
    }
    else
    {
        registJSON["response"] = "invalid pass";
        registJSON["error"] = 1;
    }//end if*/

    registJSON["response"] = "enter";
    registJSON["error"] = 0;
    return registJSON;
}
