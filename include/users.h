#ifndef USERS_H
#define USERS_H

#include <windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <sstream>  // Add this line


class Users {
private:
    MYSQL *conn;
public:
    Users();  // Constructor to connect to DB
    ~Users(); // Destructor to close DB connection

    void viewUsers();                            // View all users
    void addUser(const std::string &, const std::string &, const std::string &, const std::string &); // Add user
    void editUser(int, const std::string &, const std::string &, const std::string &, const std::string &); // Edit user
    void deleteUser(int);                        // Delete user
};

#endif
