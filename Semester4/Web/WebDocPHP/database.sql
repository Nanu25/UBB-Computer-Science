-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS examwebdev;
USE examwebdev;

-- Create SoftwareDeveloper table
CREATE TABLE IF NOT EXISTS Websites (
    id INT AUTO_INCREMENT PRIMARY KEY,
    URL VARCHAR(255)
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Documents (
    id INT AUTO_INCREMENT PRIMARY KEY,
    idWebSite INT,
    keyword1 VARCHAR(255),
    keyword2 VARCHAR(255),
    keyword3 VARCHAR(255),
    keyword4 VARCHAR(255),
    keyword5 VARCHAR(255),
    FOREIGN KEY (idWebSite) REFERENCES Websites(id)
);

-- Insert sample data for testing
INSERT INTO Websites (URL) VALUES
('http://example.com'),
('http://testsite.com'),
('http://mywebsite.org');

INSERT INTO Documents (idWebSite, keyword1, keyword2, keyword3, keyword4, keyword5) VALUES
(1, 'dog', 'cat', 'fish', 'bird', 'hamster'),
(2, 'apple', 'banana', 'orange', 'grape', 'kiwi'),
(3, 'car', 'bike', 'bus', 'train', 'plane'),
(1, 'sun', 'moon', 'star', 'planet', 'galaxy');