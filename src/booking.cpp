#include "booking.h"

Booking::Booking() {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "carparking", 3306, NULL, 0);
    if (!conn) {
        std::cerr << "Database connection failed!" << std::endl;
    }
}

Booking::~Booking() {
    mysql_close(conn);
}

// View Available Parking Slots with Location
void Booking::viewAvailableSlots() {
    if (conn) {
        std::string query = "SELECT id, location FROM parking_spots WHERE status = 'Available'";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row;
            std::cout << "\nAvailable Parking Slots:\n";
            std::cout << "-----------------------------------\n";
            std::cout << "ID\tLocation\n";
            std::cout << "-----------------------------------\n";
            while ((row = mysql_fetch_row(res))) {
                std::cout << row[0] << "\t" << row[1] << std::endl;
            }
            mysql_free_result(res);
        } else {
            std::cerr << "Error retrieving parking slots: " << mysql_error(conn) << std::endl;
        }
    }
}

// Add Booking and Update Slot Status
void Booking::addBooking(int user_id, const std::string &customer_name, const std::string &phone, const std::string &car_plate, int parking_id) {
    if (conn) {
        std::ostringstream query;
        query << "INSERT INTO bookings (user_id, parking_id, customer_name, phone, car_plate) VALUES ("
              << user_id << ", " << parking_id << ", '" << customer_name << "', '" << phone << "', '" << car_plate << "')";

        if (mysql_query(conn, query.str().c_str()) == 0) {
            std::cout << "Booking added successfully!\n";
            updateSlotStatus(parking_id, "Occupied");
        } else {
            std::cerr << "Error adding booking: " << mysql_error(conn) << std::endl;
        }
    }
}

// Update Booking Status
void Booking::updateBooking(int booking_id, const std::string &status) {
    if (conn) {
        std::ostringstream query;
        query << "UPDATE bookings SET status = '" << status << "' WHERE id = " << booking_id;

        if (mysql_query(conn, query.str().c_str()) == 0) {
            std::cout << "Booking updated successfully!\n";
            if (status == "Cancelled" || status == "Completed") {
                // Free the parking slot
                std::ostringstream getSlotQuery;
                getSlotQuery << "SELECT parking_id FROM bookings WHERE id = " << booking_id;
                mysql_query(conn, getSlotQuery.str().c_str());
                MYSQL_RES *res = mysql_store_result(conn);
                if (res) {
                    MYSQL_ROW row = mysql_fetch_row(res);
                    if (row) {
                        updateSlotStatus(atoi(row[0]), "Available");  // ✅ Changed stoi() to atoi()
                    }
                    mysql_free_result(res);
                }
            }
        } else {
            std::cerr << "Error updating booking: " << mysql_error(conn) << std::endl;
        }
    }
}

// Delete Booking and Free Parking Slot
void Booking::deleteBooking(int booking_id) {
    if (conn) {
        std::ostringstream getSlotQuery;
        getSlotQuery << "SELECT parking_id FROM bookings WHERE id = " << booking_id;
        mysql_query(conn, getSlotQuery.str().c_str());
        MYSQL_RES *res = mysql_store_result(conn);
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                updateSlotStatus(atoi(row[0]), "Available");  // ✅ Changed stoi() to atoi()
            }
            mysql_free_result(res);
        }

        std::ostringstream query;
        query << "DELETE FROM bookings WHERE id = " << booking_id;

        if (mysql_query(conn, query.str().c_str()) == 0) {
            std::cout << "Booking deleted successfully!\n";
        } else {
            std::cerr << "Error deleting booking: " << mysql_error(conn) << std::endl;
        }
    }
}

// View All Bookings
void Booking::viewBookings() {
    if (conn) {
        std::string query = "SELECT b.id, u.name, b.customer_name, b.phone, b.car_plate, p.location, b.status "
                            "FROM bookings b "
                            "JOIN users u ON b.user_id = u.id "
                            "JOIN parking_spots p ON b.parking_id = p.id";

        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row;
            std::cout << "\nAll Bookings:\n";
            std::cout << "------------------------------------------------------------------------------------------------------\n";
            std::cout << "ID\tUser\tCustomer Name\tPhone\tCar Plate\tLocation\tStatus\n";
            std::cout << "------------------------------------------------------------------------------------------------------\n";
            while ((row = mysql_fetch_row(res))) {
                std::cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << "\t" << row[5] << "\t" << row[6] << std::endl;
            }
            mysql_free_result(res);
        } else {
            std::cerr << "Error retrieving bookings: " << mysql_error(conn) << std::endl;
        }
    }
}

// Update Parking Slot Status
void Booking::updateSlotStatus(int parking_id, const std::string &status) {
    if (conn) {
        std::ostringstream query;
        query << "UPDATE parking_spots SET status = '" << status << "' WHERE id = " << parking_id;

        if (mysql_query(conn, query.str().c_str()) == 0) {
            std::cout << "Parking slot status updated to " << status << "!\n";
        } else {
            std::cerr << "Error updating parking slot: " << mysql_error(conn) << std::endl;
        }
    }
}
