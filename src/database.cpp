#include "database.h"
#include <iostream>

const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "carparking";
unsigned int port = 3306;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connectDatabase() {
    MYSQL* conn = mysql_init(NULL);
    if (!conn) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return NULL;
    }

    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
    if (!conn) {
        std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Connected to the database successfully!" << std::endl;
    }

    return conn;
}
