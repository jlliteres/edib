# EDIB C++ project (en desarrollo)
Control de acceso de trabajadores para una empresa.

## Idea
#### Client-Server-Database
Se pretende crear un control de acceso instalable en cualquier dispositivo, que permita a los trabajadores registrar su entrada y salida de la empresa de una manera sencilla y visual. Se desarrolla también un servidor que gestiona las peticiones y se comunica con la base de datos.

## Cómo funciona
El usuario visualiza el listado de trabajadores que no están trabajando y los que sí lo hacen, pudiendo filtrar la lista para encontrar su nombre, deberá seleccionarlo y, a continuación, insertar una contraseña que sólo conecerá él, para así garantizar la autenticidad del trabajador. Automáticamente se envía la información al servidor que lo registra en la base de datos si no hay errores y el usuario cambia a la columna de personas que están trabajando.

## Herramientas utilizadas
- [Qt Creator(c++)](https://www.qt.io/)
- [PostgreSQL](https://www.postgresql.org/)
- [Doxygen](http://www.doxygen.nl/)

## Librerías utilizadas
* [nlohmann/json](https://github.com/nlohmann/json)
* [IXWebSocket](https://github.com/machinezone/IXWebSocket)
