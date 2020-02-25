#include "handler.h"
#include <QString>
#include <QMessageBox>

Handler::Handler()
{

}

void Handler::responseHandler(const JSON& receivedJSON, MainWindow& main)
{
    ///1) Get data


    std::string action = receivedJSON["action"];
    ///2) Data treatment
    if(action == "register")
    {
    }
    else if (action == "load")
    {
    }
    else if (action == "admin")
    {
        if(receivedJSON["error"] == 0)
        {
            main.unlock();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Invalid admin credentials");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }//end if
    }
    else if (action == "")
    {

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
