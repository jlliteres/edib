# EDIB C++ project (en desarrollo)
Control de acceso de trabajadores para una empresa.

## Idea
#### Client-Server-Database
Se pretende crear un control de acceso instalable en cualquier dispositivo, que permita a los trabajadores registrar su entrada y salida de la empresa de una manera sencilla y visual. Se desarrolla también un servidor que gestiona las peticiones y se comunica con la base de datos, haciendo uso de JSON y WebSocket.

## Cómo funciona
El usuario visualiza el listado de trabajadores que no están trabajando y los que sí lo hacen, pudiendo filtrar la lista para encontrar su nombre, deberá seleccionarlo y, a continuación, insertar una contraseña que sólo conecerá él, para así garantizar la autenticidad del trabajador. Automáticamente se envía la información al servidor que lo registra en la base de datos si no hay errores y el usuario cambia a la columna de personas que están trabajando.

## Cliente
1. Inicia la conexión con el servidor.
2. Envía un mensaje para cargar las tablas con la información de la base de datos.
3. Cuando un usuario pretende entrar o salir, se comunica al servidor.
4. Si el servidor responde correctamente, se actualiza la información de las tablas.

## Servidor
1. Se comprueba que el mensaje recibido sea un JSON válido.
2. Se envía el JSON a un objeto, un [handler](tree/master/acces_control_server/handler.cpp), que determinará el "action" o petición que hace este mensaje.
3. Según el "action" se realiza la función correspondiente, haciendo uso de otro [objeto](edib/acces_control_server/database.cpp) que se comunica con la base de datos.
4. Si la respuesta de la base de datos es correcta, se devuelve un JSON al cliente con error 0.
5. Si no es correcta, se comunica al cliente con error 1.

## Herramientas utilizadas
- [Qt Creator(c++)](https://www.qt.io/)
- [PostgreSQL](https://www.postgresql.org/)
- [Doxygen](http://www.doxygen.nl/)

## Librerías utilizadas
* [nlohmann/json](https://github.com/nlohmann/json)
* [IXWebSocket](https://github.com/machinezone/IXWebSocket)
