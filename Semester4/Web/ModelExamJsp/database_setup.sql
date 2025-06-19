-- Create database if it doesn't exist
-- Note: The database 'examphp' should already exist as mentioned by the user

-- Use the existing database
USE examphp;

-- Create SoftwareDeveloper table
CREATE TABLE IF NOT EXISTS SoftwareDeveloper (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    age INT NOT NULL,
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

-- Insert sample data for SoftwareDeveloper
INSERT INTO SoftwareDeveloper (name, age, skills) VALUES
('John Smith', 28, 'Java, Spring, MySQL'),
('Sarah Johnson', 32, 'JavaScript, React, Node.js'),
('Mike Brown', 25, 'Python, Django, PostgreSQL'),
('Lisa Wilson', 30, 'Java, Hibernate, Oracle'),
('David Lee', 35, 'C#, .NET, SQL Server'),
('Emma Davis', 27, 'JavaScript, Vue.js, MongoDB'),
('Tom Anderson', 29, 'PHP, Laravel, MySQL'),
('Jessica White', 31, 'Python, Flask, Redis');

-- Insert sample data for Project
INSERT INTO Project (ProjectManagerID, name, description, members) VALUES
(1, 'E-Commerce Platform', 'Online shopping platform with modern UI', 'John Smith, Sarah Johnson'),
(2, 'Mobile Banking App', 'Secure mobile banking application', 'Sarah Johnson, Mike Brown'),
(3, 'Data Analytics Dashboard', 'Real-time data visualization tool', 'Mike Brown, Lisa Wilson'),
(4, 'CRM System', 'Customer relationship management system', 'Lisa Wilson, David Lee'),
(5, 'Inventory Management', 'Warehouse inventory tracking system', 'David Lee, Emma Davis'),
(6, 'Social Media Platform', 'Community-based social networking site', 'Emma Davis, Tom Anderson'),
(NULL, 'Content Management System', 'Blog and news website CMS', 'Tom Anderson, Jessica White'),
(8, 'Learning Management System', 'Online education platform', 'Jessica White, John Smith');
