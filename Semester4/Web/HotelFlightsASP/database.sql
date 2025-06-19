-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS HotelFlights;
USE HotelFlights;

CREATE TABLE IF NOT EXISTS Flights (
    flightID INT AUTO_INCREMENT PRIMARY KEY,
    date varchar(50),
    destinationCity varchar(50),
    availableSeats int
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Hotels (
    hotelId INT AUTO_INCREMENT PRIMARY KEY,
    hotelName varchar(255),
    date varchar(50),
    city varchar(255),
    availableRooms int
);

create table if not EXISTS Reservations (
    id int AUTO_INCREMENT PRIMARY KEY,
    person varchar(250),
    type varchar(250),
    idReservedResource int
);

-- Insert sample data for testing
INSERT INTO Flights (date, destinationCity, availableSeats) VALUES
('2025-06-15', 'Mizil', '5'),
('2025-06-16', 'Barcelona', '4'),
('2025-06-15', 'Cluj', '1'),
('2025-06-15', 'Mizil', '0');

INSERT INTO Hotels (hotelName, date, city, availableRooms) VALUES
('Hotel Best', '2025-06-15', 'Mizil', 3),
('Hotel The Best', '2025-06-16', 'Barcelona', 1),
('Hotel Royal', '2025-06-15', 'Cluj', 1),
('Motel', '2025-06-15', 'Mizil', 0);


INSERT INTO Reservations (person, type, idReservedResource) VALUES
('Alex', 'Flight', 1);

