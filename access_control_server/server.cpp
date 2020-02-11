#include "server.h"


Server::Server()
{
    init_server();
}

void Server::init_server()
{
    ix::WebSocketServer server(9900, "0.0.0.0");

    server.setOnConnectionCallback(
        [&server](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg)
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
                            JSON message;
                            message["action"] = "register";
                            message["id"] = "1";
                            message["passID"] = "1234";
                            message["response"] = "Entry Confirmed";

                            webSocket->send(message.dump());
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
