DROP DATABASE IF EXISTS JournalArticle;

CREATE DATABASE IF NOT EXISTS JournalArticle;
USE JournalArticle;

-- Create Journals table
CREATE TABLE IF NOT EXISTS Journals (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL
);

-- Create Articles table
CREATE TABLE IF NOT EXISTS Articles (
    id INT AUTO_INCREMENT PRIMARY KEY,
    journalid INT,
    user VARCHAR(255) NOT NULL,
    summary VARCHAR(255) NOT NULL,
    date DATE,
    FOREIGN KEY (journalid) REFERENCES Journals(id)
);

-- Insert sample data for Journals
INSERT INTO Journals (name) VALUES
('Steaua best team!'),
('Running'),
('Make exercises'),
('Healthy food');

-- Insert sample data for Articles (added user field and corrected 'summary')
INSERT INTO Articles (journalid, user, summary, date) VALUES
(1, 'Alex', 'Really the best team', '2020-02-03'),
(2, 'Mihai', 'I like running', '2022-05-01'),
(3, 'Ana', 'Aaaa', '2010-10-03'),
(1, 'Alex', 'Really the best team in the world', '2025-02-03');
