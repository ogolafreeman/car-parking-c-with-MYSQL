#ifndef PAYMENT_H
#define PAYMENT_H

#include <windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Payment {
private:
    MYSQL *conn;
public:
    Payment();  // Constructor to connect to DB
    ~Payment(); // Destructor to close DB connection

    void processPayment(int user_id, int parking_id, double amount, const std::string &payment_method, const std::string &reference);
    void viewTransactions();
    void updateTransactionStatus(int transaction_id, const std::string& status);  // Fixed function name
    void deleteTransaction(int transaction_id);
    void exportTransactionsToCSV(const std::string& filename);
};

#endif // PAYMENT_H
