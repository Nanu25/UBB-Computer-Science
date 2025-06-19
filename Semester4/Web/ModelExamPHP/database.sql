-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS examphp;
USE examphp;

-- Create SoftwareDeveloper table
CREATE TABLE IF NOT EXISTS SoftwareDeveloper (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    age INT,
    skills TEXT
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Project (
    id INT AUTO_INCREMENT PRIMARY KEY,
    ProjectManagerID INT,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    members TEXT,
    FOREIGN KEY (ProjectManagerID) REFERENCES SoftwareDeveloper(id)
);

-- Insert sample data for testing
INSERT INTO SoftwareDeveloper (name, age, skills) VALUES
('John Doe', 30, 'Java, Python, JavaScript'),
('Jane Smith', 28, 'C#, Java, SQL'),
('Bob Johnson', 32, 'Python, Django, PostgreSQL'),
('Alice Brown', 26, 'JavaScript, React, Node.js'),
('Charlie Wilson', 35, 'Java, Spring, Hibernate');

INSERT INTO Project (ProjectManagerID, name, description, members) VALUES
(1, 'E-commerce Platform', 'Building a modern e-commerce solution', 'John Doe,Jane Smith,Bob Johnson'),
(2, 'Mobile Banking App', 'Secure mobile banking application', 'Jane Smith,Alice Brown'),
(3, 'Data Analytics Dashboard', 'Real-time analytics dashboard', 'Bob Johnson,Charlie Wilson,John Doe');
