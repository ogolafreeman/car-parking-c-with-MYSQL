#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>  // Added for std::cout, std::cin
#include <conio.h>   // For getch() to hide password input
#include <sstream>  // For string conversion

class Overview {
private:
    MYSQL *conn;  // Declare the connection object
public:
    Overview();
    ~Overview();
    MYSQL* connectDatabase();
    void displayOverview();
};

#endif
