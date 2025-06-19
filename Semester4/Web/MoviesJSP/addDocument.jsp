<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String documentName = request.getParameter("documentName");
    String content = request.getParameter("content");
    String userName = request.getParameter("userName");

    String url = "jdbc:mysql://localhost:3306/MoviesDocuments";
    String dbUser = "root";
    String dbPassword = "";
    
    String message = "";
    String messageType = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        
        String addDocument = "Insert into Documents (name, content) values (?, ?)";
        PreparedStatement addStmt = conn.prepareStatement(addDocument);
        addStmt.setString(1, documentName);
        addStmt.setString(2, content);
        addStmt.executeUpdate();

        String getDocumentList = "SELECT documentList FROM Authors WHERE name = ?";
        PreparedStatement getMembersStmt = conn.prepareStatement(getDocumentList);
        getMembersStmt.setString(1, userName);
        ResultSet membersRs = getMembersStmt.executeQuery();

        membersRs.next();       //e obligatoriu
        String newMembers = membersRs.getString("documentList");
        String updateDoc = "UPDATE Authors SET documentList = ? WHERE name = ?";
        PreparedStatement updateStmt = conn.prepareStatement (updateDoc);
        newMembers = newMembers + " " + documentName;

        updateStmt.setString(1, newMembers);
        updateStmt.setString(2, userName);
        updateStmt.executeUpdate();
        updateStmt.close();
        getMembersStmt.close();
            
            
            message = "Document '" + documentName + "' has been assigned to the selected projects.";
            messageType = "success";

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
