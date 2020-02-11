#include "server.h"


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

                            JSON receivedObject = JSON::parse(msg->str, nullptr, false);

                            JSON response;
                            response["action"] = "register";
                            response["clientID"] = receivedObject["clientID"];
                            response["serverID"] = serverID++;
                            response["passID"] = "1234";
                            response["response"] = "Entry Confirmed";
                            response["error"] = 0;

                            webSocket->send(response.dump());
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
