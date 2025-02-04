#ifndef BOOKING_H
#define BOOKING_H

#include <windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <sstream>

class Booking {
private:
    MYSQL *conn;
public:
    Booking();
    ~Booking();

    void viewAvailableSlots();
    void addBooking(int user_id, const std::string &customer_name, const std::string &phone, const std::string &car_plate, int parking_id);
    void updateBooking(int booking_id, const std::string &status);  // Update status
    void deleteBooking(int booking_id);  // Delete booking
    void viewBookings();  // View all bookings
    void updateSlotStatus(int parking_id, const std::string &status);
};

#endif
