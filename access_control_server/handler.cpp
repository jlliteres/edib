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
    else if (action == "add")
    {
        responseJSON = add(responseJSON, receivedJSON["user"], receivedJSON["password"]);
    }
    else if (action == "modify")
    {
        responseJSON = modify(responseJSON, receivedJSON["id"].get<int>(), receivedJSON["user"], receivedJSON["password"]);
    }
    else if (action == "delete")
    {
        //responseJSON = add(responseJSON, receivedJSON["user"], receivedJSON["password"]);
    }//end if

    return responseJSON;
}

JSON Handler::modify(JSON responseJSON, int id, std::string user, std::string password)
{
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "modify";

    ///Problem modifying user, error = 1
    if(m_database.modify(id, user, password))
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }//end if

    return dbJSON;
}

JSON Handler::add(JSON responseJSON, std::string user, std::string password)
{
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "add";

    ///Problem inserting user, error = 1
    if(m_database.addUser(user, password))
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }//end if

    return dbJSON;
}

JSON Handler::admin(JSON responseJSON, std::string user, std::string password)
{
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "admin";

    ///No valid login, error = 1
    if(m_database.admin(user, password))
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }//end if

    return dbJSON;
}

JSON Handler::load(const JSON& responseJSON)
{
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "load";

    dbJSON["list"] = m_database.load();

    return dbJSON;
}

JSON Handler::enter(const JSON& responseJSON, int user, std::string password)
{
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "enter";

    ///No valid login, error = 1
    if(m_database.enter(user, password))
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }//end if

    return dbJSON;
}

JSON Handler::exit(const JSON& responseJSON, int user, std::string password)
{
    JSON dbJSON = responseJSON;
    dbJSON["action"] = "exit";

    ///No valid login, error = 1
    if(m_database.exit(user, password))
    {
        dbJSON["error"] = 0;
    }
    else
    {
        dbJSON["error"] = 1;
    }//end if

    return dbJSON;
}
