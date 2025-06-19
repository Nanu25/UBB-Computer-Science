-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS UserProperty;
USE UserProperty;

CREATE TABLE IF NOT EXISTS User (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    secretQuestion varchar(255) not null,
    secretAnswer varchar(255) not null
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Property (
    id INT AUTO_INCREMENT PRIMARY KEY,
    address varchar(255),
    description TEXT
);

create table if not EXISTS UserToProperty (
    id int AUTO_INCREMENT PRIMARY KEY,
    idUser int,
    idProprty int,
    FOREIGN KEY (idUser) REFERENCES User(id),
    FOREIGN KEY (idProprty) REFERENCES Property(id)
);

-- Insert sample data for testing
INSERT INTO User (name, secretQuestion, secretAnswer) VALUES
('Alex', 'Best Team', 'Steaua'),
('Ion', 'Favorite animal', 'dog');

INSERT INTO Property (description, address) VALUES
('The best', 'Mizil'),
('Wow', 'Alba'), 
('Messi', 'Buhusi');

INSERT INTO UserToProperty (idUser, idProprty) VALUES
(1, 1),
(2, 1),
(1, 3);

