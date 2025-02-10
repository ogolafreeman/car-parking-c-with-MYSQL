#include "parkingslots.h"
#include <fstream>  // For file handling

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

// New function to export parking slots to CSV
void ParkingSlots::exportSlotsToCSV(const std::string& filename) {
    if (!conn) {
        std::cerr << "Database connection not available!" << std::endl;
        return;
    }

    MYSQL_RES *res;
    MYSQL_ROW row;

    std::string query = "SELECT id, location, status, price FROM parking_spots";
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Error executing query: " << mysql_error(conn) << std::endl;
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Error storing result: " << mysql_error(conn) << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Writing the header row
    file << "Slot ID,Location,Status,Price\n";

    // Writing the data rows
    while ((row = mysql_fetch_row(res))) {
        file << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "\n";
    }

    file.close();
    mysql_free_result(res);

    std::cout << "Parking slots exported successfully to " << filename << std::endl;
}
