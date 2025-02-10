#include "payment.h"

Payment::Payment() {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "carparking", 3306, NULL, 0);
    if (!conn) {
        std::cout << "Database connection failed!" << std::endl;
    }
}

Payment::~Payment() {
    mysql_close(conn);
}

void Payment::processPayment(int user_id, int parking_id, double amount, const std::string &payment_method, const std::string &reference) {
    std::stringstream ss;
    ss << "INSERT INTO transactions (user_id, parking_id, amount, payment_method, reference_number, status) "
       << "VALUES (" << user_id << ", " << parking_id << ", " << amount << ", '"
       << payment_method << "', '" << reference << "', 'Pending')";

    std::string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        std::cout << "Payment processing failed: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Payment processed successfully!" << std::endl;
    }
}

void Payment::viewTransactions() {
    std::string query = "SELECT transactions.id, users.name, parking_spots.location, transactions.amount, transactions.transaction_time, transactions.payment_method, transactions.status FROM transactions "
                        "JOIN users ON transactions.user_id = users.id "
                        "JOIN parking_spots ON transactions.parking_id = parking_spots.id";

    if (mysql_query(conn, query.c_str())) {
        std::cout << "Error retrieving transactions: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;

    std::cout << "\nID | User | Parking Spot | Amount | Date | Payment Method | Status\n";
    while ((row = mysql_fetch_row(res))) {
        std::cout << row[0] << " | " << row[1] << " | " << row[2] << " | Ksh " << row[3] << " | " << row[4]
                  << " | " << row[5] << " | " << row[6] << "\n";
    }
    mysql_free_result(res);
}

void Payment::updateTransactionStatus(int transaction_id, const std::string &status) {
    std::stringstream ss;
    ss << "UPDATE transactions SET status = '" << status << "' WHERE id = " << transaction_id;

    std::string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        std::cout << "Failed to update transaction: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Transaction updated successfully!" << std::endl;
    }
}

void Payment::deleteTransaction(int transaction_id) {
    std::stringstream ss;
    ss << "DELETE FROM transactions WHERE id = " << transaction_id;

    std::string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        std::cout << "Failed to delete transaction: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Transaction deleted successfully!" << std::endl;
    }
}

// New function to export transactions to CSV
void Payment::exportTransactionsToCSV(const std::string& filename) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    std::string query = "SELECT id, user_id, parking_id, amount, payment_method, reference_number, status, transaction_time FROM transactions";
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
    file << "Transaction ID,User ID,Parking ID,Amount,Payment Method,Reference,Status,Transaction Time\n";

    // Writing the data rows
    while ((row = mysql_fetch_row(res))) {
        file << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << ","
             << row[4] << "," << row[5] << "," << row[6] << "," << row[7] << "\n";
    }

    file.close();
    mysql_free_result(res);

    std::cout << "Transactions exported successfully to " << filename << std::endl;
}
