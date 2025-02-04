#include "parkingslots.h"

ParkingSlots::ParkingSlots() {
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

ParkingSlots::~ParkingSlots() {
    if (conn) {
        mysql_close(conn);
    }
}

void ParkingSlots::viewSlots() {
    if (!conn) {
        std::cout << "Database connection not available!" << std::endl;
        return;
    }

    std::cout << "----- Parking Slots Overview -----\n";
    std::string query = "SELECT id, location, status, price FROM parking_spots";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row;
            std::cout << "ID | Location | Status | Price\n";
            std::cout << "------------------------------------\n";
            while ((row = mysql_fetch_row(result))) {
                std::cout << row[0] << " | " << row[1] << " | " << row[2] << " | KES " << row[3] << std::endl;
            }
            mysql_free_result(result);
        }
    }
}

void ParkingSlots::addSlot(const std::string &location, const std::string &status, double price) {
    if (!conn) return;

    std::stringstream ss;
    ss << "INSERT INTO parking_spots (location, status, price) VALUES ('"
       << location << "', '" << status << "', " << price << ")";

    if (mysql_query(conn, ss.str().c_str()) == 0) {
        std::cout << "Parking slot added successfully!\n";
    } else {
        std::cout << "Error adding slot: " << mysql_error(conn) << std::endl;
    }
}

void ParkingSlots::updateSlotStatus(int slot_id, const std::string &new_status) {
    if (!conn) return;

    std::stringstream ss;
    ss << "UPDATE parking_spots SET status = '" << new_status << "' WHERE id = " << slot_id;

    if (mysql_query(conn, ss.str().c_str()) == 0) {
        std::cout << "Slot status updated successfully!\n";
    } else {
        std::cout << "Error updating slot: " << mysql_error(conn) << std::endl;
    }
}

void ParkingSlots::deleteSlot(int slot_id) {
    if (!conn) return;

    std::stringstream ss;
    ss << "DELETE FROM parking_spots WHERE id = " << slot_id;

    if (mysql_query(conn, ss.str().c_str()) == 0) {
        std::cout << "Slot deleted successfully!\n";
    } else {
        std::cout << "Error deleting slot: " << mysql_error(conn) << std::endl;
    }
}
