-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS Ieri;
USE Ieri;

CREATE TABLE IF NOT EXISTS User (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username varchar(50),
    password varchar(255)
);

-- Create Project table
CREATE TABLE IF NOT EXISTS HotelRoom (
    id INT AUTO_INCREMENT PRIMARY KEY,
    roomNumber varchar(255),
    capacity int,
    basePrice int
);

create table if not EXISTS Reservation (
    id int AUTO_INCREMENT PRIMARY KEY,
    userId int,
    roomId int,
    checkInDate date,
    checkOutDate date,
    numberOfGuests int,
    totalPrice int,
    FOREIGN KEY (userId) REFERENCES User(id),
    FOREIGN KEY (roomId) REFERENCES HotelRoom(id)
);

-- Insert sample data for testing
INSERT INTO User (username, password) VALUES
('Alex', 'aaaa'),
('Ion', 'aaaa');

INSERT INTO HotelRoom (roomNumber, capacity, basePrice) VALUES
('1', 2, 100),
('2',3, 150),
('3', 1, 50),
('4', 4, 400);


INSERT INTO Reservation (userId, roomId, checkInDate, checkOutDate, numberOfGuests, totalPrice) VALUES
(1, 1, '2025-06-10', '2025-06-20', 3, 150),
(2, 2, '2025-06-19', '2025-06-29', 1, 50);


