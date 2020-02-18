#include "handler.h"
#include "database.h"
#include <QString>

Handler::Handler()
{

}

JSON Handler::responseHandler(const JSON& receivedJSON, const int serverID)
{
    ///1) Get data
    JSON responseJSON;
    responseJSON["clientID"] = receivedJSON["clientID"];
    responseJSON["serverID"] = serverID;

    std::string action = receivedJSON["action"];
    ///2) Data treatment
    if( action == "register")
    {
        responseJSON = regist(responseJSON);
    }
    else if (action == "load")
    {
        responseJSON = load(responseJSON);
    }
    else if (action == "login")
    {
        responseJSON = login(responseJSON);
    }
    else if (action == "")
    {

    }
    else if (action == "")
    {

    }

    return responseJSON;
}


JSON Handler::login(const JSON& responseJSON)
{
    Database db;
    JSON dbJSON = responseJSON;

    ///No valid login, error = 1
    if(db.login(QString::fromStdString(responseJSON["password"])))
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
    Database db;
    db.load();

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
