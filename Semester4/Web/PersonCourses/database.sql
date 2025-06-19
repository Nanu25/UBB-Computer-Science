-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS examPerCourses;
USE examPerCourses;

-- Create SoftwareDeveloper table
CREATE TABLE IF NOT EXISTS Persons (
    id INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(50),
    Role VARCHAR(50)
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Courses (
    id INT AUTO_INCREMENT PRIMARY KEY,
    professorId INT,
    courseName varchar(50),
    participants varchar(50),
    grades varchar(50),
    FOREIGN KEY (professorId) REFERENCES Persons(id)
);

-- Insert sample data for testing
INSERT INTO Persons (Name, Role) VALUES
('Alex', 'professor'),
('Ion', 'student'),
('Dan', 'student'),
('Maria', 'professor');

INSERT INTO Courses (professorId, courseName, participants, grades) VALUES
(1, 'WP', 'Ion Dan', '10 10 6'),
(1, 'MS', 'Ion', '4'),
(2, 'MAP', 'Dan', '8 5'),
(1, 'BE', 'Ion Dan', '5 6 7');