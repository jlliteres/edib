#include "server.h"
#include "handler.h"
#include <QDateTime>
#include <QDebug>

Server::Server()
{
    init_server();
}

void Server::init_server()
{
    ix::WebSocketServer server(9900, "0.0.0.0");

    server.setOnConnectionCallback(
        [&server, this](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server, this](const ix::WebSocketMessagePtr msg)
                {
                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        JSON json;
                        json["action"] = "connection";
                        json["error"] = 0;

                        webSocket->send(json.dump());
                        std::cout << "New connection" << std::endl;

                    }
                    else if (msg->type == ix::WebSocketMessageType::Close)
                    {
                        std::cout << "Closed connection" << std::endl;
                    }
                    else if (msg->type == ix::WebSocketMessageType::Message)
                    {
                        if (!msg->binary)
                        {
                            /// Text format

                            std::cout << "Received message: " << msg->str << std::endl;

                            ///1) Get data

                            JSON receivedObject = JSON::parse(msg->str, nullptr, false);

                            if(receivedObject.is_discarded())
                            {
                                qDebug() << "JSON isn't valid";
                            }
                            else
                            {///JSON is valid

                            ///2) Data treatment
                                if(exists(receivedObject, "action"))
                                {

                                    JSON response = m_handler.responseHandler(receivedObject, serverID++);

                                    webSocket->send(response.dump());

                                }//end if
                            }//end if
                        }
                    }
                }

            );
        }
    );

    auto res = server.listen();
    if (!res.first)
    {
        /// Error handling
        //return 1;
    }

    server.start();
    server.wait();
    server.stop();
}

bool Server::exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}
