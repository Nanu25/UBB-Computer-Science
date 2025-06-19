-- Database setup for ExamPHP application
CREATE DATABASE IF NOT EXISTS ChannelUser;
USE ChannelUser;

CREATE TABLE IF NOT EXISTS Person (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    password varchar(250) NOT NULL
);

-- Create Project table
CREATE TABLE IF NOT EXISTS Channels (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name varchar(255),
    description varchar(250),
    subscribers int
);

create table if not EXISTS PersonChannels (
    id int AUTO_INCREMENT PRIMARY KEY,
    idPerson int,
    idChannel int,
    FOREIGN KEY (idPerson) REFERENCES Person(id),
    FOREIGN KEY (idChannel) REFERENCES Channels(id)
);

-- Insert sample data for testing
INSERT INTO Person (name, password) VALUES
('Alex', 'aaaa'),
('Ion', 'Ion');

INSERT INTO Channels (name, description, subscribers) VALUES
('Mr Beast', 'the beast', 100000),
('Messi', 'the goat', 100000), 
('aaa', 'bbbb', 10);

INSERT INTO PersonChannels (idPerson, idChannel) VALUES
(1, 1),
(2, 1),
(1, 3);

