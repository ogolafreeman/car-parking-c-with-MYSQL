#include "overview.h"



Overview::Overview() {
    conn = connectDatabase();
}

Overview::~Overview() {
    if (conn) {
        mysql_close(conn);
    }
}

MYSQL* Overview::connectDatabase() {
    MYSQL* conn = mysql_init(NULL);
    if (!conn) {
        std::cout << "MySQL initialization failed!" << std::endl;
        return NULL;
    }
    conn = mysql_real_connect(conn, "localhost", "root", "", "carparking", 3306, NULL, 0);
    if (!conn) {
        std::cout << "Connection failed: " << mysql_error(conn) << std::endl;
    }
    return conn;
}

// Function to convert string to int using stringstream
int stringToInt(const char* str) {
    if (!str) return 0;  // Handle null values
    std::stringstream ss(str);
    int value = 0;
    ss >> value;
    return value;
}

// Function to convert string to double using stringstream
double stringToDouble(const char* str) {
    if (!str) return 0.0;  // Handle null values
    std::stringstream ss(str);
    double value = 0.0;
    ss >> value;
    return value;
}

void Overview::displayOverview() {
    if (!conn) {
        std::cout << "Database connection not available!" << std::endl;
        return;
    }

    std::string query = "SELECT COUNT(*) AS total_slots, SUM(CASE WHEN status='Available' THEN 1 ELSE 0 END) AS available_slots FROM parking_spots";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        int totalSlots = stringToInt(row[0]);   // Convert using stringstream
        int availableSlots = stringToInt(row[1]);
        int occupiedSlots = totalSlots - availableSlots;

        std::cout << "Total Slots: " << totalSlots << " | Available: " << availableSlots << " | Occupied: " << occupiedSlots << std::endl;

        mysql_free_result(result);
    } else {
        std::cout << "Error fetching parking data: " << mysql_error(conn) << std::endl;
    }

    query = "SELECT SUM(amount) FROM transactions WHERE DATE(transaction_time) = CURDATE()";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        double dailyRevenue = stringToDouble(row[0]);  // Convert using stringstream
        std::cout << "Today's Revenue: KES " << dailyRevenue << std::endl;

        mysql_free_result(result);
    } else {
        std::cout << "Error fetching revenue data: " << mysql_error(conn) << std::endl;
    }
}
