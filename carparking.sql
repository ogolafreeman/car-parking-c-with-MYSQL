-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Feb 05, 2025 at 06:52 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.4.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `carparking`
--

-- --------------------------------------------------------

--
-- Table structure for table `bookings`
--

CREATE TABLE `bookings` (
  `id` int(11) NOT NULL,
  `user_id` int(11) DEFAULT NULL,
  `parking_id` int(11) DEFAULT NULL,
  `booking_time` timestamp NOT NULL DEFAULT current_timestamp(),
  `status` enum('Active','Completed','Cancelled') DEFAULT 'Active',
  `customer_name` varchar(255) NOT NULL,
  `phone` varchar(20) NOT NULL,
  `car_plate` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `bookings`
--

INSERT INTO `bookings` (`id`, `user_id`, `parking_id`, `booking_time`, `status`, `customer_name`, `phone`, `car_plate`) VALUES
(3, 1, 4, '2025-02-04 20:15:29', 'Active', 'Jack', '0723980082', 'kak');

-- --------------------------------------------------------

--
-- Table structure for table `parking_spots`
--

CREATE TABLE `parking_spots` (
  `id` int(11) NOT NULL,
  `location` varchar(255) NOT NULL,
  `status` enum('Available','Occupied') DEFAULT 'Available',
  `price` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `parking_spots`
--

INSERT INTO `parking_spots` (`id`, `location`, `status`, `price`) VALUES
(1, 'Zone A - 101', 'Occupied', '50.00'),
(3, 'Zone B - 201', 'Available', '60.00'),
(4, 'Zone A - 102', 'Occupied', '100.00');

-- --------------------------------------------------------

--
-- Table structure for table `transactions`
--

CREATE TABLE `transactions` (
  `id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `parking_id` int(11) NOT NULL,
  `amount` decimal(10,2) NOT NULL,
  `transaction_time` timestamp NOT NULL DEFAULT current_timestamp(),
  `payment_method` enum('Cash','Credit Card','Mobile Payment') NOT NULL,
  `reference_number` varchar(50) DEFAULT NULL,
  `status` enum('Pending','Completed','Failed') DEFAULT 'Pending'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `transactions`
--

INSERT INTO `transactions` (`id`, `user_id`, `parking_id`, `amount`, `transaction_time`, `payment_method`, `reference_number`, `status`) VALUES
(1, 1, 3, '100.00', '2025-02-05 17:49:48', 'Cash', '154524', 'Pending');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `role` enum('Admin','User') NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `name`, `email`, `password`, `role`, `created_at`) VALUES
(1, 'test', 'test@gmail.com', '1d28c120568c10e19b9d8abe8b66d0983fa3d2e11ee7751aca50f83c6f4a43aa', 'Admin', '2025-02-04 17:32:40'),
(2, 'Jack', 'jacktone@gmail.com', '147', 'User', '2025-02-04 18:25:00');

-- --------------------------------------------------------

--
-- Table structure for table `vehicle_logs`
--

CREATE TABLE `vehicle_logs` (
  `id` int(11) NOT NULL,
  `booking_id` int(11) DEFAULT NULL,
  `vehicle_plate` varchar(20) NOT NULL,
  `entry_time` timestamp NOT NULL DEFAULT current_timestamp(),
  `exit_time` timestamp NULL DEFAULT NULL,
  `status` enum('Entered','Exited') DEFAULT 'Entered'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `vehicle_logs`
--

INSERT INTO `vehicle_logs` (`id`, `booking_id`, `vehicle_plate`, `entry_time`, `exit_time`, `status`) VALUES
(1, 3, 'kak', '2025-02-05 09:43:42', '2025-02-05 09:44:01', 'Exited');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `bookings`
--
ALTER TABLE `bookings`
  ADD PRIMARY KEY (`id`),
  ADD KEY `user_id` (`user_id`),
  ADD KEY `parking_id` (`parking_id`);

--
-- Indexes for table `parking_spots`
--
ALTER TABLE `parking_spots`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `transactions`
--
ALTER TABLE `transactions`
  ADD PRIMARY KEY (`id`),
  ADD KEY `user_id` (`user_id`),
  ADD KEY `parking_id` (`parking_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `email` (`email`);

--
-- Indexes for table `vehicle_logs`
--
ALTER TABLE `vehicle_logs`
  ADD PRIMARY KEY (`id`),
  ADD KEY `booking_id` (`booking_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `bookings`
--
ALTER TABLE `bookings`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `parking_spots`
--
ALTER TABLE `parking_spots`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `transactions`
--
ALTER TABLE `transactions`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `vehicle_logs`
--
ALTER TABLE `vehicle_logs`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `bookings`
--
ALTER TABLE `bookings`
  ADD CONSTRAINT `bookings_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`),
  ADD CONSTRAINT `bookings_ibfk_2` FOREIGN KEY (`parking_id`) REFERENCES `parking_spots` (`id`);

--
-- Constraints for table `transactions`
--
ALTER TABLE `transactions`
  ADD CONSTRAINT `transactions_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `transactions_ibfk_2` FOREIGN KEY (`parking_id`) REFERENCES `parking_spots` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `vehicle_logs`
--
ALTER TABLE `vehicle_logs`
  ADD CONSTRAINT `vehicle_logs_ibfk_1` FOREIGN KEY (`booking_id`) REFERENCES `bookings` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
