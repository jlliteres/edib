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
    if (action == "enter")
    {
        responseJSON = enter(responseJSON, receivedJSON["user"].get<int>(), receivedJSON["password"]);
    }
    else if (action == "exit")
    {
        responseJSON = exit(responseJSON, receivedJSON["user"].get<int>(), receivedJSON["password"]);
    }
    else if (action == "load")
    {
        responseJSON = load(responseJSON);
    }
    else if (action == "admin")
    {
        responseJSON = admin(responseJSON, receivedJSON["user"], receivedJSON["password"]);
    }    
    else if (action == "")
    {

    }

    return responseJSON;
}


JSON Handler::admin(JSON responseJSON, std::string user, std::string password)
{
    Database db;
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "admin";

    ///No valid login, error = 1
    if(db.admin(user, password))
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
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "load";

    dbJSON["list"] = db.load();

    return dbJSON;
}

JSON Handler::enter(const JSON& responseJSON, int user, std::string password)
{
    Database db;
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "enter";

    ///No valid login, error = 1
    if(db.enter(user, password))
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }

    return dbJSON;
}

JSON Handler::exit(const JSON& responseJSON, int user, std::string password)
{
    Database db;
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "exit";

    ///No valid login, error = 1
    if(db.exit(user, password))
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }

    return dbJSON;
}
