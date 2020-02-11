#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"

#include "json.hpp"

using JSON = nlohmann::json;
int idServer{1};

bool exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}

JSON registro(JSON receivedObject)
{
    static bool estasDentro{false};
    JSON responseMessage = {
        {"idServer", idServer++},
        {"idClient", receivedObject["id"]},
    };
    /// 1) Consultar BBDD para datos tarjeta válidos
    /// 2) Si son válidos comprobar si entra o sale

    if(receivedObject["idTarjeta"] == "0000")
    {///tarjeta no activada
        responseMessage["mensaje"] = "Tarjeta no activada, pase por recepción";
        return responseMessage;
    }

    if(receivedObject["idTarjeta"] == "12345")
    {///tarjeta no válida
        responseMessage["mensaje"] = "Tarjeta no válida";
    }
    else
    {///tarjeta válida
        if(!estasDentro)
        {
            responseMessage["mensaje"] = "Estás entrando";
            estasDentro = true;
        }
        else
        {
            responseMessage["mensaje"] = "Estás saliendo";
            estasDentro = false;
        }//end if
    }//end if
    return responseMessage;
}

int main(int argc, char *argv[])
{

    ix::WebSocketServer server(9990, "0.0.0.0");

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
                        }

                        JSON receivedObject = JSON::parse(msg->str, nullptr, false);

                        if(receivedObject.is_discarded())
                        {
                            ///error
                            std::cout << "JSON no válido" << std::endl;
                        }
                        else
                        {
                            ///JSON válido
                            if(exists(receivedObject, "action"))
                            {
                                std::string action = receivedObject["action"];
                                std::cout << "Received message: " << action << std::endl;

                                if(action == "registro")
                                {
                                    webSocket->send(registro(receivedObject).dump());
                                }//end if
                            }
                            else
                            {
                                std::cout << "No hay action" << std::endl;

                            }//end if
                        }//end if



                    }//end if

                }//end if

            );
        }
    );


    auto res = server.listen();
    if (!res.first)
    {
        // Error handling
        return 1;
    }

    server.start();
    server.wait();
    server.stop();
}

