-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS TeachersCourses;
USE TeachersCourses;

CREATE TABLE IF NOT EXISTS Teachers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name varchar(50),
    courseList varchar(50),
    projectList varchar(50)
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Courses (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title varchar(255),
    description varchar(50)
);

create table if not EXISTS Projects (
    id int AUTO_INCREMENT PRIMARY KEY,
    name varchar(250),
    duration int
);

-- Insert sample data for testing
INSERT INTO Teachers (name, courseList, projectList) VALUES
('Alex', 'Mate Info Sport', 'Steaua DSA'),
('Ion', 'Romana DSA SD', 'Algoritmi');

INSERT INTO Courses (title, description) VALUES
('Mate', 'You know C'),
('Info', 'You don t know C!'),
('Sport', 'Forta Steaua'),
('SD', 'Simga');

INSERT INTO Projects (name, duration) VALUES
('Steaua', 28),
('DSA', 120),
('Algoritmi', 10);

