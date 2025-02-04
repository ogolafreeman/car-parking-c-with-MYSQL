#include "users.h"


Users::Users() {
    conn = mysql_init(NULL);
    if (!conn) {
        std::cout << "MySQL initialization failed!" << std::endl;
        return;
    }
    conn = mysql_real_connect(conn, "localhost", "root", "", "carparking", 3306, NULL, 0);
    if (!conn) {
        std::cout << "Database connection failed: " << mysql_error(conn) << std::endl;
    }
}

Users::~Users() {
    if (conn) {
        mysql_close(conn);
    }
}

void Users::viewUsers() {
    if (!conn) {
        std::cout << "Database connection not available!" << std::endl;
        return;
    }

    std::cout << "----- User List -----\n";
    std::string query = "SELECT id, name, email, role, created_at FROM users";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row;
            std::cout << "ID | Name | Email | Role | Created At\n";
            std::cout << "--------------------------------------------------\n";
            while ((row = mysql_fetch_row(result))) {
                std::cout << row[0] << " | " << row[1] << " | " << row[2]
                          << " | " << row[3] << " | " << row[4] << std::endl;
            }
            mysql_free_result(result);
        }
    } else {
        std::cout << "Error retrieving users: " << mysql_error(conn) << std::endl;
    }
}

void Users::addUser(const std::string &name, const std::string &email, const std::string &password, const std::string &role) {
    if (!conn) return;

    std::stringstream ss;
    ss << "INSERT INTO users (name, email, password, role) VALUES ('"
       << name << "', '" << email << "', '" << password << "', '" << role << "')";

    if (mysql_query(conn, ss.str().c_str()) == 0) {
        std::cout << "User added successfully!\n";
    } else {
        std::cout << "Error adding user: " << mysql_error(conn) << std::endl;
    }
}

void Users::editUser(int id, const std::string &name, const std::string &email, const std::string &password, const std::string &role) {
    if (!conn) return;

    std::stringstream ss;
    ss << "UPDATE users SET name = '" << name << "', email = '" << email
       << "', password = '" << password << "', role = '" << role << "' WHERE id = " << id;

    if (mysql_query(conn, ss.str().c_str()) == 0) {
        std::cout << "User updated successfully!\n";
    } else {
        std::cout << "Error updating user: " << mysql_error(conn) << std::endl;
    }
}

void Users::deleteUser(int id) {
    if (!conn) return;

    std::stringstream ss;
    ss << "DELETE FROM users WHERE id = " << id;

    if (mysql_query(conn, ss.str().c_str()) == 0) {
        std::cout << "User deleted successfully!\n";
    } else {
        std::cout << "Error deleting user: " << mysql_error(conn) << std::endl;
    }
}
