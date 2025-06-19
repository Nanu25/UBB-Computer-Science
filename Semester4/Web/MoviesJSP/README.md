# Software Developer Project Manager - JSP Application

This is a JSP web application for managing software developers and projects.

## Requirements

- Apache Tomcat Server
- MySQL Database
- MySQL Connector/J JDBC Driver
- Java Development Kit (JDK) 8 or higher

## Setup Instructions

### 1. Database Setup
1. Make sure MySQL is running
2. The database `examphp` should already exist
3. Run the SQL script `database_setup.sql` to create tables and insert sample data:
   ```sql
   mysql -u root -p examphp < database_setup.sql
   ```

### 2. JDBC Driver Setup
1. Download MySQL Connector/J from the official MySQL website
2. Copy the `mysql-connector-java-x.x.x.jar` file to your Tomcat's `lib` directory
   - For XAMPP: `XAMPP/tomcat/lib/`
   - For standalone Tomcat: `TOMCAT_HOME/lib/`

### 3. Web Application Deployment
1. Copy all JSP files to your web server directory:
   - For XAMPP: `XAMPP/htdocs/ExamJsp/`
   - For Tomcat: `TOMCAT_HOME/webapps/ExamJsp/`

### 4. Database Configuration
If your MySQL configuration is different, update the database connection details in each JSP file:
```java
String url = "jdbc:mysql://localhost:3306/examphp";
String dbUser = "root";
String dbPassword = "";
```

## Features

### 1. User Login (Required)
- Users must enter their name to access the application
- Name is stored in session for project membership tracking

### 2. View All Projects (2 points)
- Displays all projects from the database
- Shows project ID, name, description, project manager, and members

### 3. View My Projects (2.5 points)
- Shows only the project names where the current user is a member
- Filters based on the logged-in user's name

### 4. Assign Developer to Projects (3 points)
- Allows assigning existing developers to multiple projects in a single request
- If developer doesn't exist, no assignment occurs
- If project doesn't exist, it's automatically created with the specified name
- Supports both existing projects (via checkboxes) and new projects

### 5. View and Filter Developers (1.5 points)
- Server-side: Displays all developers from the database
- Client-side: JavaScript filtering by skills (e.g., "Java")
- Real-time filtering as user types

## Usage

1. Start your web server (Apache Tomcat)
2. Navigate to: `http://localhost:8080/ExamJsp/` (adjust port as needed)
3. Enter your name to login
4. Use the buttons to access different features:
   - **Show All Projects**: View complete project information
   - **Show My Projects**: View projects you're a member of
   - **Assign Developer to Projects**: Add developers to projects
   - **Show All Developers**: View and filter developer list

## Database Schema

### SoftwareDeveloper Table
- `id` (INT, Primary Key, Auto Increment)
- `name` (VARCHAR(255), NOT NULL)
- `age` (INT, NOT NULL)
- `skills` (TEXT)

### Project Table
- `id` (INT, Primary Key, Auto Increment)
- `ProjectManagerID` (INT, Foreign Key to SoftwareDeveloper.id)
- `name` (VARCHAR(255), NOT NULL)
- `description` (TEXT)
- `members` (TEXT) - Comma-separated list of developer names

## Sample Data

The application includes sample data with 8 developers and 8 projects to demonstrate all features.

## Troubleshooting

1. **Database Connection Issues**: Verify MySQL is running and credentials are correct
2. **JDBC Driver Issues**: Ensure MySQL Connector/J is in the correct lib directory
3. **Tomcat Issues**: Check Tomcat logs for deployment errors
4. **JSP Compilation Issues**: Ensure JDK is properly configured with Tomcat
