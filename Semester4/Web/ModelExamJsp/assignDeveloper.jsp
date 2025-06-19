<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String developerName = request.getParameter("developerName");
    String[] projectIds = request.getParameterValues("projectIds");
    String newProjectName = request.getParameter("newProjectName");
    
    String url = "jdbc:mysql://localhost:3306/examphp";
    String dbUser = "root";
    String dbPassword = "";
    
    String message = "";
    String messageType = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        // Check if developer exists
        String checkDeveloperQuery = "SELECT id FROM SoftwareDeveloper WHERE name = ?";
        PreparedStatement checkStmt = conn.prepareStatement(checkDeveloperQuery);
        checkStmt.setString(1, developerName);
        ResultSet rs = checkStmt.executeQuery();
        
        if (!rs.next()) {
            message = "Developer '" + developerName + "' does not exist in the database.";
            messageType = "error";
        } else {
            // Developer exists, proceed with assignment
            List<Integer> projectsToUpdate = new ArrayList<>();
            
            // Add existing projects
            if (projectIds != null) {
                for (String projectId : projectIds) {
                    projectsToUpdate.add(Integer.parseInt(projectId));
                }
            }
            
            // Create new project if specified
            if (newProjectName != null && !newProjectName.trim().isEmpty()) {
                String insertProjectQuery = "INSERT INTO Project (name, description, members) VALUES (?, '', ?)";
                PreparedStatement insertStmt = conn.prepareStatement(insertProjectQuery, Statement.RETURN_GENERATED_KEYS);
                insertStmt.setString(1, newProjectName);
                insertStmt.setString(2, developerName);
                insertStmt.executeUpdate();
                
                ResultSet generatedKeys = insertStmt.getGeneratedKeys();
                if (generatedKeys.next()) {
                    projectsToUpdate.add(generatedKeys.getInt(1));
                }
                insertStmt.close();
            }
            
            // Update existing projects
            for (Integer projectId : projectsToUpdate) {
                // Get current members
                String getMembersQuery = "SELECT members FROM Project WHERE id = ?";
                PreparedStatement getMembersStmt = conn.prepareStatement(getMembersQuery);
                getMembersStmt.setInt(1, projectId);
                ResultSet membersRs = getMembersStmt.executeQuery();
                
                if (membersRs.next()) {
                    String currentMembers = membersRs.getString("members");
                    String newMembers;
                      if (currentMembers == null || currentMembers.trim().isEmpty()) {
                        newMembers = developerName;
                    } else if (!currentMembers.contains(developerName)) {
                        newMembers = currentMembers + ", " + developerName;
                    } else {
                        // Developer already in project, skip
                        continue;
                    }
                    
                    // Update project members
                    String updateMembersQuery = "UPDATE Project SET members = ? WHERE id = ?";
                    PreparedStatement updateStmt = conn.prepareStatement(updateMembersQuery);
                    updateStmt.setString(1, newMembers);
                    updateStmt.setInt(2, projectId);
                    updateStmt.executeUpdate();
                    updateStmt.close();
                }
                
                getMembersStmt.close();
            }
            
            message = "Developer '" + developerName + "' has been assigned to the selected projects.";
            messageType = "success";
        }
        
        rs.close();
        checkStmt.close();
        conn.close();
        
    } catch (Exception e) {
        message = "Error assigning developer: " + e.getMessage();
        messageType = "error";
    }
%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Assignment Result</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .container {
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            text-align: center;
        }
        .success {
            color: green;
            font-weight: bold;
            font-size: 18px;
        }
        .error {
            color: red;
            font-weight: bold;
            font-size: 18px;
        }
        button {
            background-color: #007bff;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            margin-top: 20px;
        }
        button:hover {
            background-color: #0056b3;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Assignment Result</h1>
        <p class="<%= messageType %>"><%= message %></p>
        <button onclick="window.location.href='index.jsp'">Back to Main Page</button>
    </div>
</body>
</html>
