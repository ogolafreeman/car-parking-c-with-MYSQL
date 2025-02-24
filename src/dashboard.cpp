#include "dashboard.h"
#include "parkingslots.h"
#include "overview.h"
#include "users.h"
#include "booking.h"
#include "vehicle.h"
#include"payment.h"

void dashboard(std::string role) {
    while (true) {
        system("cls"); // Clear screen (change to system("clear") for Linux/macOS)
        std::cout << "\n\n********** DASHBOARD **********\n";

        if (role == "Admin") {
            std::cout << "Welcome, Admin! You have full access.\n";
            std::cout << "\nPlease select an option:\n";
            std::cout << "1. Dashboard Overview\n";
            std::cout << "2. Parking Slot Management\n";
            std::cout << "3. User Management\n";
            std::cout << "4. Vehicle Entry & Exit Management\n";  // 🆕 New Option
            std::cout << "7. Bookings & Reservation\n";
            std::cout << "8. Payments & Transactions\n";
            std::cout << "11. Logout\n";

            int choice;
            std::cout << "\nEnter your choice: ";
            std::cin >> choice;

            if (std::cin.fail()) { // Handle invalid input
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid input! Please enter a number.\n";
                system("pause");
                continue;
            }

            switch (choice) {
                case 1: {
                    Overview overview;
                    overview.displayOverview();
                    system("pause");
                    break;
                }
                case 2: {
                    ParkingSlots ps;
                    while (true) {
                        system("cls");
                        std::cout << "\n----- Parking Slot Management -----\n";
                        std::cout << "1. View Parking Slots\n";
                        std::cout << "2. Add Parking Slot\n";
                        std::cout << "3. Edit Parking Slot\n";
                        std::cout << "4. Delete Parking Slot\n";
                        std::cout << "5. Back to Dashboard\n";
                        std::cout << "6. Download parking slots\n";
                        std::cout << "Enter your choice: ";
                        int option;
                        std::cin >> option;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cout << "Invalid input! Please enter a number.\n";
                            system("pause");
                            continue;
                        }

                        switch (option) {
                            case 1:
                                ps.viewSlots();
                                break;
                            case 2: {
                                std::string location, status;
                                double price;
                                std::cin.ignore();
                                std::cout << "Enter location: ";
                                std::getline(std::cin, location);
                                std::cout << "Enter status (Available/Occupied): ";
                                std::cin >> status;
                                std::cout << "Enter price: ";
                                std::cin >> price;
                                ps.addSlot(location, status, price);
                                break;
                            }
                            case 3: {
                                int id;
                                std::string new_status;
                                std::cout << "Enter slot ID to update: ";
                                std::cin >> id;
                                std::cout << "Enter new status (Available/Occupied): ";
                                std::cin >> new_status;
                                ps.updateSlotStatus(id, new_status);
                                break;
                            }
                            case 4: {
                                int id;
                                std::cout << "Enter slot ID to delete: ";
                                std::cin >> id;
                                ps.deleteSlot(id);
                                break;
                            }
                            case 5:
                                goto dashboard_loop;
                            default:
                                std::cout << "Invalid option! Try again.\n";
                                break;
                        }
                        system("pause");
                    }
                    break;
                }
                case 3: {
                    Users users;
                    while (true) {
                        system("cls");
                        std::cout << "\n----- User Management -----\n";
                        std::cout << "1. View Users\n";
                        std::cout << "2. Add User\n";
                        std::cout << "3. Edit User\n";
                        std::cout << "4. Delete User\n";
                        std::cout << "5. Back to Dashboard\n";
                        std::cout << "Enter your choice: ";
                        int userChoice;
                        std::cin >> userChoice;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cout << "Invalid input! Please enter a number.\n";
                            system("pause");
                            continue;
                        }

                        switch (userChoice) {
                            case 1:
                                users.viewUsers();
                                break;
                            case 2: {
                                std::string name, email, password, role;
                                std::cin.ignore();
                                std::cout << "Enter name: ";
                                std::getline(std::cin, name);
                                std::cout << "Enter email: ";
                                std::cin >> email;
                                std::cout << "Enter password: ";
                                std::cin >> password;
                                std::cout << "Enter role (Admin/User): ";
                                std::cin >> role;
                                users.addUser(name, email, password, role);
                                break;
                            }
                            case 3: {
                                int id;
                                std::string name, email, password, role;
                                std::cout << "Enter User ID to Edit: ";
                                std::cin >> id;
                                std::cin.ignore();
                                std::cout << "Enter new name: ";
                                std::getline(std::cin, name);
                                std::cout << "Enter new email: ";
                                std::cin >> email;
                                std::cout << "Enter new password: ";
                                std::cin >> password;
                                std::cout << "Enter new role (Admin/User): ";
                                std::cin >> role;
                                users.editUser(id, name, email, password, role);
                                break;
                            }
                            case 4: {
                                int id;
                                std::cout << "Enter User ID to Delete: ";
                                std::cin >> id;
                                users.deleteUser(id);
                                break;
                            }
                            case 5:
                                goto dashboard_loop;
                            default:
                                std::cout << "Invalid choice! Try again.\n";
                                break;
                        }
                        system("pause");
                    }
                    break;
                }

                // 🆕 New: Vehicle Entry & Exit Management
                case 4: {
                    Vehicle vehicle;
                    while (true) {
                        system("cls");
                        std::cout << "\n----- Vehicle Entry & Exit Management -----\n";
                        std::cout << "1. Register Vehicle Entry\n";
                        std::cout << "2. Register Vehicle Exit\n";
                        std::cout << "3. View Vehicle Logs\n";
                        std::cout << "4. Back to Dashboard\n";
                        std::cout << "Enter your choice: ";
                        int vehicleChoice;
                        std::cin >> vehicleChoice;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cout << "Invalid input! Please enter a number.\n";
                            system("pause");
                            continue;
                        }

                        switch (vehicleChoice) {
                            case 1: {
                                int booking_id;
                                std::string vehicle_plate;
                                std::cout << "Enter Booking ID: ";
                                std::cin >> booking_id;
                                std::cout << "Enter Vehicle Plate: ";
                                std::cin >> vehicle_plate;
                                vehicle.registerEntry(booking_id, vehicle_plate);
                                break;
                            }
                            case 2: {
                                int booking_id;
                                std::cout << "Enter Booking ID to Exit: ";
                                std::cin >> booking_id;
                                vehicle.registerExit(booking_id);
                                break;
                            }
                            case 3:
                                vehicle.viewVehicleLogs();
                                break;
                            case 4:
                                goto dashboard_loop;
                            default:
                                std::cout << "Invalid choice! Try again.\n";
                                break;
                        }
                        system("pause");
                    }
                    break;
                }

                case 7: { // Booking & Reservation System
    Booking booking;
    int bookingChoice;

    while (true) {
        system("cls");
        std::cout << "\n----- Booking & Reservation System -----\n";
        std::cout << "1. View Bookings\n";
        std::cout << "2. Add Booking\n";
        std::cout << "3. Update Booking Status\n";
        std::cout << "4. Delete Booking\n";
        std::cout << "5. View Available Parking Slots\n";
        std::cout << "6. Back to Dashboard\n";
        std::cout << "Enter your choice: ";
        std::cin >> bookingChoice;

        switch (bookingChoice) {
            case 1:
                booking.viewBookings();
                system("pause");
                break;
            case 2: {
                int user_id, parking_id;
                std::string name, phone, car_plate;
                std::cout << "Enter User ID: ";
                std::cin >> user_id;
                std::cout << "Enter Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Phone: ";
                std::cin >> phone;
                std::cout << "Enter Car Plate: ";
                std::cin >> car_plate;

                booking.viewAvailableSlots();
                std::cout << "Enter Parking ID: ";
                std::cin >> parking_id;
                booking.addBooking(user_id, name, phone, car_plate, parking_id);
                system("pause");
                break;
            }
            case 5:
                booking.viewAvailableSlots();
                system("pause");
                break;
            case 6:
                return;
        }
    }
}

                    // Booking system already implemented.
                    break;


case 8: {
    Payment payment;
    int paymentChoice;

    while (true) {
        system("cls");
        std::cout << "\n----- Payment & Billing Management -----\n";
        std::cout << "1. View Transactions\n";
        std::cout << "2. Process a Payment\n";
        std::cout << "3. Update Payment Status\n";
        std::cout << "4. Delete a Transaction\n";
        std::cout << "5. Back to Dashboard\n";
        std::cout << "6. Download payments\n";
        std::cout << "Enter your choice: ";
        std::cin >> paymentChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            system("pause");
            continue;
        }

        switch (paymentChoice) {
            case 1:
                payment.viewTransactions();
                system("pause");
                break;
            case 2: {
                int user_id, parking_id;
                double amount;
                std::string method, ref_number;

                std::cout << "Enter User ID: ";
                std::cin >> user_id;
                std::cout << "Enter Parking Slot ID: ";
                std::cin >> parking_id;
                std::cout << "Enter Amount: ";
                std::cin >> amount;
                std::cout << "Enter Payment Method (Cash/Credit Card/Mobile Payment): ";
                std::cin >> method;
                std::cout << "Enter Reference Number: ";
                std::cin >> ref_number;

                payment.processPayment(user_id, parking_id, amount, method, ref_number);
                system("pause");
                break;
            }
            case 3: {
                int transaction_id;
                std::string status;
                std::cout << "Enter Transaction ID: ";
                std::cin >> transaction_id;
                std::cout << "Enter New Status (Pending/Completed/Failed): ";
                std::cin >> status;

                payment.updateTransactionStatus(transaction_id, status);
                system("pause");
                break;
            }
            case 4: {
                int transaction_id;
                std::cout << "Enter Transaction ID to Delete: ";
                std::cin >> transaction_id;

                payment.deleteTransaction(transaction_id);
                system("pause");
                break;
            }
            case 6: {  // Assuming case 4 is for export
    std::string filename;
    std::cout << "Enter filename to save (e.g., transactions.csv): ";
    std::cin >> filename;

    payment.exportTransactionsToCSV(filename);
    system("pause");
    break;
}

            case 5:
                goto dashboard_loop;
            default:
                std::cout << "Invalid option! Try again.\n";
                system("pause");
                break;
        }
    }
    break;
}


                case 11:
                    std::cout << "\nLogging out...\n";
                    return;

                default:
                    std::cout << "\nInvalid choice! Please try again.\n";
                    system("pause");
                    break;
            }
        }
    dashboard_loop:
        continue;
    }
}
