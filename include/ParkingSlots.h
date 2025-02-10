#ifndef PARKINGSLOTS_H
#define PARKINGSLOTS_H

#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>  // Include for file handling

class ParkingSlots {
private:
    MYSQL *conn;
public:
    ParkingSlots();
    ~ParkingSlots();
    void viewSlots();
    void addSlot(const std::string &location, const std::string &status, double price);
    void updateSlotStatus(int slot_id, const std::string &new_status);
    void deleteSlot(int slot_id);

    // New function to export parking slots to CSV
    void exportSlotsToCSV(const std::string &filename);
};

#endif
