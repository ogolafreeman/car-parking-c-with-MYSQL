# Car Parking Management System

## Overview

The **Car Parking Management System** is a C++ application designed to manage parking slots, user registrations, bookings, and transactions for a car parking facility. The system provides an intuitive interface for administrators and users to interact with the parking system efficiently.

This project demonstrates the use of **MySQL** for database management, **C++** for backend logic, and modular programming principles to create a scalable and maintainable system.

---

## Features

### **1. User Management**
- **Registration**: Users can register with their name, email, password, and role (Admin or User).
- **Login**: Registered users can log in to access the system.
- **Role-Based Access**:
  - **Admin**: Full access to manage parking slots, view reports, and manage users.
  - **User**: Limited access to book parking slots and view their booking history.

### **2. Parking Slot Management**
- **Add/Edit/Delete Parking Slots**: Admins can manage parking slots, including location and pricing.
- **View Slot Availability**: Users can check the availability of parking slots in real-time.
- **Assign/Unassign Slots**: Admins can assign or unassign slots to users.

### **3. Booking & Reservation System**
- **Online Slot Reservation**: Users can book available parking slots.
- **Real-Time Availability**: Users can view real-time availability of slots.
- **Cancellation & Refunds**: Users can cancel bookings, and refunds are processed accordingly.

### **4. Payment & Billing Management**
- **Payment Methods**: Supports cash, credit/debit cards, and mobile payments.
- **Generate Invoices**: Automatically generates invoices for completed transactions.
- **Track Payments**: Admins can track pending and completed payments.

### **5. Reports & Analytics**
- **Parking Usage Reports**: Daily, weekly, and monthly reports on parking usage.
- **Revenue Reports**: Detailed revenue summaries for admins.
- **Peak Hours Analysis**: Identifies the busiest hours for parking.

### **6. Dashboard Overview**
- **Total Available/Occupied Slots**: Displays the current status of parking slots.
- **Revenue Summary**: Shows daily, weekly, and monthly revenue.
- **Live Slot Status**: Provides a visual representation of slot availability.

---

## Database Schema

The system uses a MySQL database named `carparking` with the following tables:

### **1. `users`**
- Stores user information (name, email, password, role, etc.).
- **Fields**:
  - `id` (Primary Key)
  - `name`
  - `email` (Unique)
  - `password` (Hashed using SHA-256)
  - `role` (Admin or User)
  - `created_at` (Timestamp)

### **2. `parking_spots`**
- Stores information about parking slots.
- **Fields**:
  - `id` (Primary Key)
  - `location`
  - `status` (Available or Occupied)
  - `price` (Decimal)

### **3. `bookings`**
- Stores booking information.
- **Fields**:
  - `id` (Primary Key)
  - `user_id` (Foreign Key to `users`)
  - `parking_id` (Foreign Key to `parking_spots`)
  - `booking_time` (Timestamp)
  - `status` (Active, Completed, Cancelled)

### **4. `transactions`**
- Stores payment information.
- **Fields**:
  - `id` (Primary Key)
  - `user_id` (Foreign Key to `users`)
  - `amount` (Decimal)
  - `transaction_time` (Timestamp)
  - `status` (Pending, Completed, Failed)

---

## How It Works

### **1. Database Connection**
- The system connects to the MySQL database using the `mysql.h` library.
- The connection is established in `main.cpp` and shared across modules to avoid redundancy.

### **2. User Authentication**
- Users can register and log in using their credentials.
- Passwords are hashed using SHA-256 for security.

### **3. Admin Dashboard**
- Admins can access the dashboard to:
  - View parking slot status.
  - Manage users and parking slots.
  - Generate reports and view revenue summaries.

### **4. User Dashboard**
- Users can:
  - Book available parking slots.
  - View their booking history.
  - Cancel bookings and request refunds.

### **5. Modular Design**
- The system is divided into modules:
  - `main.cpp`: Entry point of the application.
  - `database.cpp`: Handles database connection and queries.
  - `overview.cpp`: Displays the dashboard overview.
  - Other modules for user management, booking, payments, etc.

---

## Setup Instructions

### **1. Prerequisites**
- **MySQL Server**: Install and configure MySQL on your system.
- **C++ Compiler**: Use a compiler like GCC or MinGW.
- **MySQL Connector/C**: Install the MySQL C API library.

### **2. Database Setup**
1. Create the `carparking` database:
   ```sql
   CREATE DATABASE carparking;
   USE carparking;
   CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    role ENUM('Admin', 'User') NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```sql
CREATE TABLE parking_spots (
    id INT AUTO_INCREMENT PRIMARY KEY,
    location VARCHAR(255) NOT NULL,
    status ENUM('Available', 'Occupied') DEFAULT 'Available',
    price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE bookings (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    parking_id INT,
    booking_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('Active', 'Completed', 'Cancelled') DEFAULT 'Active',
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (parking_id) REFERENCES parking_spots(id)
);

CREATE TABLE transactions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    amount DECIMAL(10, 2) NOT NULL,
    transaction_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('Pending', 'Completed', 'Failed') DEFAULT 'Pending',
    FOREIGN KEY (user_id) REFERENCES users(id)
);
```
## Future Enhancements
Graphical User Interface (GUI):

Implement a GUI using libraries like Qt or GTK for a better user experience.
Email Notifications:

Send email notifications for booking confirmations, payment receipts, etc.
Mobile App Integration:

Develop a mobile app for users to book slots and manage their accounts.
Advanced Analytics:

Use machine learning to predict parking demand and optimize slot allocation.