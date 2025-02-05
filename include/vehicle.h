#ifndef VEHICLE_H
#define VEHICLE_H

#include <windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <sstream>

class Vehicle {
private:
    MYSQL *conn;
public:
    Vehicle();  // Constructor to connect to DB
    ~Vehicle(); // Destructor to close DB connection

    void registerEntry(int booking_id, const std::string &vehicle_plate);
    void registerExit(int booking_id);
    void viewVehicleLogs();
};

#endif
