# EDIB C++ project github.com/jlliteres/edib (en desarrollo)
Control de acceso de trabajadores para una empresa.

## Idea
#### Client-Server-Database
Se pretende crear un control de acceso instalable en cualquier dispositivo, que permita a los trabajadores registrar su entrada y salida de la empresa de una manera sencilla y visual. Se desarrolla también un servidor que gestiona las peticiones y se comunica con la base de datos, haciendo uso de JSON y WebSocket.

La base de datos viene con información para poder probar la aplicación:
- Administrador: admin Contraseña: admin
- Josep Lliteres Contraseña: 1234

## Cómo funciona
#### **Todos los mensajes de respuesta del servidor son _parseados_ para comprobar que son JSON válidos. Se usa un [handler](access_control_client/handler.cpp) para determinar el _action_ de la respuesta y realizar la función correspondiente**

### Cliente
1. Inicia la conexión con el servidor.
2. Envía un JSON para cargar las tablas con la información de la base de datos.
3. Cuando un usuario pretende entrar o salir aparece una ventana para introducir sus credenciales. 
4. Se comunica al servidor con un JSON.
5. Si el servidor responde correctamente, _error 0_, se actualiza la información de las tablas.

### Cliente (admin)
1. Pulsando el botón _Unlock..._ se muestra una ventana para introducir los datos de _administrador_.
2. Se envía un JSON al servidor.
3. Si las credenciales son correctas, se desbloquean las opciones de:
   - Agregar un usuario.
   - Eliminar un usuario.
   - Modificar un usuario.
   - Comprobar las entradas y salidas de los usuarios.
4. Se bloquean las opciones pulsando _Lock..._

### Servidor
1. Se comprueba que el mensaje recibido sea un JSON válido.
2. Se envía el JSON a un objeto, un [handler](access_control_server/handler.cpp), que determinará el _action_ o petición que hace este mensaje.
3. Según el _action_ se realiza la función correspondiente, haciendo uso de los métodos de otro [objeto](access_control_server/database.cpp) que se comunica con la base de datos.
4. Si la respuesta de la base de datos es correcta, se devuelve un JSON al cliente con _error 0_.
5. Si no es correcta, se comunica al cliente con _error 1_.

## Herramientas utilizadas
- [Qt Creator(c++)](https://www.qt.io/)
- [PostgreSQL](https://www.postgresql.org/)
- [Doxygen](http://www.doxygen.nl/)

## Librerías utilizadas
* [nlohmann/json](https://github.com/nlohmann/json)
* [IXWebSocket](https://github.com/machinezone/IXWebSocket)
