#include "vehicle.h"

Vehicle::Vehicle() {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "carparking", 3306, NULL, 0);
    if (!conn) {
        std::cerr << "Database connection failed!" << std::endl;
    }
}

Vehicle::~Vehicle() {
    mysql_close(conn);
}

// Register Vehicle Entry
void Vehicle::registerEntry(int booking_id, const std::string &vehicle_plate) {
    if (conn) {
        std::ostringstream checkBooking;
        checkBooking << "SELECT id FROM bookings WHERE id = " << booking_id << " AND status = 'Active'";

        if (mysql_query(conn, checkBooking.str().c_str()) == 0) {
            MYSQL_RES *res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                mysql_free_result(res);

                std::ostringstream query;
                query << "INSERT INTO vehicle_logs (booking_id, vehicle_plate) VALUES ("
                      << booking_id << ", '" << vehicle_plate << "')";

                if (mysql_query(conn, query.str().c_str()) == 0) {
                    std::cout << "Vehicle entry registered successfully!\n";
                } else {
                    std::cerr << "Error registering entry: " << mysql_error(conn) << std::endl;
                }
            } else {
                std::cerr << "Invalid booking ID or booking is not active.\n";
            }
            mysql_free_result(res);
        }
    }
}

// Register Vehicle Exit
void Vehicle::registerExit(int booking_id) {
    if (conn) {
        std::ostringstream query;
        query << "UPDATE vehicle_logs SET exit_time = CURRENT_TIMESTAMP, status = 'Exited' WHERE booking_id = " << booking_id << " AND status = 'Entered'";

        if (mysql_query(conn, query.str().c_str()) == 0) {
            std::cout << "Vehicle exit registered successfully!\n";
        } else {
            std::cerr << "Error registering exit: " << mysql_error(conn) << std::endl;
        }
    }
}

// View Vehicle Logs
void Vehicle::viewVehicleLogs() {
    if (conn) {
        std::string query = "SELECT v.id, b.customer_name, v.vehicle_plate, v.entry_time, v.exit_time, v.status "
                            "FROM vehicle_logs v "
                            "JOIN bookings b ON v.booking_id = b.id";

        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row;
            std::cout << "\nVehicle Logs:\n";
            std::cout << "--------------------------------------------------------------------------\n";
            std::cout << "ID\tCustomer Name\tPlate\tEntry Time\tExit Time\tStatus\n";
            std::cout << "--------------------------------------------------------------------------\n";
            while ((row = mysql_fetch_row(res))) {
                std::cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t"
                          << (row[4] ? row[4] : "Still Parked") << "\t" << row[5] << std::endl;
            }
            mysql_free_result(res);
        } else {
            std::cerr << "Error retrieving logs: " << mysql_error(conn) << std::endl;
        }
    }
}
