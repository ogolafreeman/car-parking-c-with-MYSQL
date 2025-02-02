#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include <conio.h> // For getch() to hide password input
#include "dashboard.h" // Include dashboard functionality

using namespace std;

const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "carparking";
unsigned int port = 3306;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

void showProgressBar(int duration, const string& message) {
    int progress = 0;
    int step = 5;
    int delay = duration * 1000 / (100 / step);

    cout << message << endl;
    while (progress <= 100) {
        cout << "\r[" << string(progress / 5, '=') << string(20 - (progress / 5), ' ') << "] " << progress << "%";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay));
        progress += step;
    }
    cout << "\r[" << string(20, '=') << "] 100%" << endl;
}

MYSQL* connectDatabase() {
    showProgressBar(2, "Connecting to the database...");
    MYSQL* conn = mysql_init(NULL);
    if (!conn) {
        cout << "MySQL initialization failed!" << endl;
        return NULL;
    }
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
    if (!conn) {
        cout << "Connection failed: " << mysql_error(conn) << endl;
    } else {
        cout << "Connected to the database successfully!" << endl;
    }
    return conn;
}

void registerUser() {
    MYSQL* conn = connectDatabase();
    if (!conn) return;

    string name, email, userPassword, role;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Password: ";

    char ch;
    while ((ch = _getch()) != '\r') { // Mask password input
        if (ch == '\b' && !userPassword.empty()) {
            cout << "\b \b";
            userPassword.pop_back();
        } else if (ch != '\b') {
            userPassword.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;

    int roleChoice;
    cout << "Select Role: \n1. Admin \n2. User\nEnter choice: ";
    cin >> roleChoice;
    role = (roleChoice == 1) ? "Admin" : "User";

    stringstream query;
    query << "INSERT INTO users (name, email, password, role) VALUES ('"
          << name << "', '" << email << "', SHA2('" << userPassword << "', 256), '" << role << "')";

    showProgressBar(2, "Registering user...");
    if (mysql_query(conn, query.str().c_str()) == 0) {
        cout << "User registered successfully as " << role << "!" << endl;
    } else {
        cout << "Registration failed: " << mysql_error(conn) << endl;
    }

    mysql_close(conn);
}

void loginUser() {
    MYSQL* conn = connectDatabase();
    if (!conn) return;

    string email, userPassword;
    int attempts = 3;

    while (attempts > 0) {
        cin.ignore();
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Password: ";

        char ch;
        userPassword = "";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b' && !userPassword.empty()) {
                cout << "\b \b";
                userPassword.pop_back();
            } else if (ch != '\b') {
                userPassword.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        stringstream query;
        query << "SELECT role FROM users WHERE email = '" << email << "' AND password = SHA2('" << userPassword << "', 256)";

        showProgressBar(2, "Verifying credentials...");
        if (mysql_query(conn, query.str().c_str()) == 0) {
            MYSQL_RES* result = mysql_store_result(conn);
            if (result) {
                if (mysql_num_rows(result) > 0) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    string role = row[0];
                    cout << "Login successful! Welcome, " << email << " (" << role << ")!" << endl;
                    mysql_free_result(result);
                    mysql_close(conn);

                    // Call the external dashboard function
                    dashboard(role);
                    return;
                } else {
                    cout << "Invalid email or password! Attempts left: " << --attempts << endl;
                }
                mysql_free_result(result);
            } else {
                cout << "Error retrieving result: " << mysql_error(conn) << endl;
            }
        } else {
            cout << "Login failed: " << mysql_error(conn) << endl;
        }

        if (attempts == 0) {
            cout << "Too many failed attempts! Exiting..." << endl;
        }
    }
    mysql_close(conn);
}

int main() {
    int choice;
    cout << "1. Register\n2. Login\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        registerUser();
    } else if (choice == 2) {
        loginUser();
    } else {
        cout << "Invalid choice!" << endl;
    }
    return 0;
}
