#include "overview.h"
#include "database.h" // Include the shared database header
#include <iostream>
#include <iomanip> // For formatting output

void displayDashboardOverview(MYSQL* conn) {
    if (!conn) {
        std::cerr << "Invalid database connection!" << std::endl;
        return;
    }

    // Fetch data from the database
    std::cout << "\n********** DASHBOARD OVERVIEW **********\n";

    // 1. Total Available Parking Slots
    if (mysql_query(conn, "SELECT COUNT(*) FROM parking_spots WHERE status = 'Available'")) {
        std::cerr << "Error fetching available slots: " << mysql_error(conn) << std::endl;
    } else {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            std::cout << "Total Available Parking Slots: " << row[0] << std::endl;
            mysql_free_result(result);
        }
    }

    // 2. Total Occupied Slots
    if (mysql_query(conn, "SELECT COUNT(*) FROM parking_spots WHERE status = 'Occupied'")) {
        std::cerr << "Error fetching occupied slots: " << mysql_error(conn) << std::endl;
    } else {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            std::cout << "Total Occupied Parking Slots: " << row[0] << std::endl;
            mysql_free_result(result);
        }
    }

    // 3. Revenue Summary (Daily/Weekly/Monthly Earnings)
    if (mysql_query(conn, "SELECT SUM(amount) FROM transactions WHERE DATE(transaction_time) = CURDATE() AND status = 'Completed'")) {
        std::cerr << "Error fetching daily revenue: " << mysql_error(conn) << std::endl;
    } else {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            std::cout << "Daily Revenue: $" << (row[0] ? row[0] : "0.00") << std::endl;
            mysql_free_result(result);
        }
    }

    if (mysql_query(conn, "SELECT SUM(amount) FROM transactions WHERE YEARWEEK(transaction_time) = YEARWEEK(NOW()) AND status = 'Completed'")) {
        std::cerr << "Error fetching weekly revenue: " << mysql_error(conn) << std::endl;
    } else {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            std::cout << "Weekly Revenue: $" << (row[0] ? row[0] : "0.00") << std::endl;
            mysql_free_result(result);
        }
    }

    if (mysql_query(conn, "SELECT SUM(amount) FROM transactions WHERE MONTH(transaction_time) = MONTH(NOW()) AND status = 'Completed'")) {
        std::cerr << "Error fetching monthly revenue: " << mysql_error(conn) << std::endl;
    } else {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            std::cout << "Monthly Revenue: $" << (row[0] ? row[0] : "0.00") << std::endl;
            mysql_free_result(result);
        }
    }

    // 4. Live Parking Slot Status (Visual representation)
    std::cout << "\nLive Parking Slot Status:\n";
    if (mysql_query(conn, "SELECT id, location, status FROM parking_spots")) {
        std::cerr << "Error fetching parking slot status: " << mysql_error(conn) << std::endl;
    } else {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            std::cout << std::left << std::setw(10) << "Slot ID" << std::setw(20) << "Location" << std::setw(15) << "Status" << std::endl;
            std::cout << "----------------------------------------\n";
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                std::cout << std::left << std::setw(10) << row[0] << std::setw(20) << row[1] << std::setw(15) << row[2] << std::endl;
            }
            mysql_free_result(result);
        }
    }
}
