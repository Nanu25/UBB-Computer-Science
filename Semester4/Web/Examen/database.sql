CREATE DATABASE IF NOT EXISTS Examen;
USE Examen;

CREATE TABLE IF NOT EXISTS User (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Product (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name varchar(255),
    price int
);

create table if not EXISTS Order1 (
    id int AUTO_INCREMENT PRIMARY KEY,
    userId int,
    totalPrice int,
    FOREIGN KEY (userId) REFERENCES User(id)
    );

create table if not EXISTS OrderItem (
    id int AUTO_INCREMENT PRIMARY KEY,
    orderId int,
    productId int,
    FOREIGN KEY (orderId) REFERENCES Order1(id),
    FOREIGN KEY (productId) REFERENCES Product(id)
    );


-- Insert sample data for testing
INSERT INTO User (username) VALUES
('Alex'),
('Ana');

INSERT INTO Product (name, price) VALUES
('FOOD-Mar', 1),
('FOOD-Pepene', 2), 
('CAR-Masina', 3500),
('CAR-Volvo', 5000),
('BOOK-MATH', 10);

INSERT INTO Order1 (userId, totalPrice) VALUES 
(1, 5),
(1, 5000),
(1, 12);

INSERT INTO OrderItem (orderId, productId) VALUES
(1, 1),
(1, 2),
(1, 2),
(2, 3),
(3, 5),
(3, 2);

