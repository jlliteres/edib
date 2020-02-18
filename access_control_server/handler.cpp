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
    else if (action == "")
    {

    }
    else if (action == "")
    {

    }
    else if (action == "")
    {

    }
    else if (action == "")
    {

    }

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
