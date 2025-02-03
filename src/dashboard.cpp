#include "dashboard.h"
#include "overview.h"  // Include Overview class
#include "ParkingSlots.h"
#include <iostream>
#include <cstdlib> // For system("cls")

void dashboard(std::string role) {
    system("cls"); // Clears the console screen
    std::cout << "\n\n********** DASHBOARD **********\n";
    if (role == "Admin") {
        std::cout << "Welcome, Admin! You have full access.\n";

        // Display Admin Dashboard Options
        std::cout << "\nPlease select an option:\n";
        std::cout << "1. Dashboard Overview\n";
        std::cout << "2. Parking Slot Management\n";
        std::cout << "3. User Management\n";
        std::cout << "4. Vehicle Entry & Exit Management\n";
        std::cout << "5. Payment & Billing Management\n";
        std::cout << "6. Reports & Analytics\n";
        std::cout << "7. Booking & Reservation System\n";
        std::cout << "8. Notification & Alerts System\n";
        std::cout << "9. Security & Surveillance\n";
        std::cout << "10. System Settings & Configuration\n";
        std::cout << "11. Logout\n";

        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        // Handle Admin's choice
        switch (choice) {
            case 1:
                std::cout << "\nDashboard Overview Selected\n";
                {
                    Overview overview;
                    overview.displayOverview();
                }
                break;
            case 2:
                std::cout << "\nParking Slot Management Selected\n";
                {
                    ParkingSlots parking;
                    parking.viewSlots(); // Display parking slots
                }

                // Add functionality for Parking Slot Management
                break;
            case 3:
                std::cout << "\nUser Management Selected\n";
                // Add functionality for User Management
                break;
            case 4:
                std::cout << "\nVehicle Entry & Exit Management Selected\n";
                // Add functionality for Vehicle Entry & Exit Management
                break;
            case 5:
                std::cout << "\nPayment & Billing Management Selected\n";
                // Add functionality for Payment & Billing Management
                break;
            case 6:
                std::cout << "\nReports & Analytics Selected\n";
                // Add functionality for Reports & Analytics
                break;
            case 7:
                std::cout << "\nBooking & Reservation System Selected\n";
                // Add functionality for Booking & Reservation System
                break;
            case 8:
                std::cout << "\nNotification & Alerts System Selected\n";
                // Add functionality for Notification & Alerts System
                break;
            case 9:
                std::cout << "\nSecurity & Surveillance Selected\n";
                // Add functionality for Security & Surveillance
                break;
            case 10:
                std::cout << "\nSystem Settings & Configuration Selected\n";
                // Add functionality for System Settings & Configuration
                break;
            case 11:
                std::cout << "\nLogging out...\n";
                return; // Exit the dashboard
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
                break;
        }
    } else {
        std::cout << "Welcome, User! You have limited access.\n";
        // Add user-specific functionality here
    }
}
