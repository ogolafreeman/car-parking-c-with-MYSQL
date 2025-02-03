#ifndef PARKINGSLOTS_H
#define PARKINGSLOTS_H

#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <conio.h>
#include <sstream>

class ParkingSlots {
private:
    MYSQL *conn;
public:
    ParkingSlots();  // Constructor
    ~ParkingSlots(); // Destructor

    void viewSlots();  // View all slots
    void addSlot(const std::string &location, const std::string &status, double price); // ✅ FIXED
    void updateSlotStatus(int slot_id, const std::string &new_status); // Update slot status
    void deleteSlot(int slot_id); // Delete a slot
};

#endif
