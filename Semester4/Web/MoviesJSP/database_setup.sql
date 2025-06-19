-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS MoviesDocuments;
USE MoviesDocuments;

CREATE TABLE IF NOT EXISTS Authors (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name varchar(50),
    documentList varchar(255),
    movieList varchar(255)
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Documents (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name varchar(255),
    content varchar(50)
);

create table if not EXISTS Movies (
    id int AUTO_INCREMENT PRIMARY KEY,
    title varchar(250),
    duration int
);

-- Insert sample data for testing
INSERT INTO Authors (name, documentList, movieList) VALUES
('Alex', 'Document1 Document3', 'Movie1 Movie2'),
('Ion', 'Document1', 'Movie3 Movie4');

INSERT INTO Documents (name, content) VALUES
('Document1', 'Aaaa'),
('Document2', 'Bbbb'),
('Document3', 'Cccc'),
('Document4', 'dddd');


INSERT INTO Movies (title, duration) VALUES
('Movie1', 50),
('Movie2', 52),
('Movie3', 55),
('Movie4', 60);


