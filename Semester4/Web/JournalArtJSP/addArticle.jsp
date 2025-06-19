<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>
<%@ page import="java.time.LocalDate" %>

<%
    String userName = request.getParameter("userName");
    String articleSummary = request.getParameter("articleSummary");
    String journalName = request.getParameter("journalName");
    
    String url = "jdbc:mysql://localhost:3306/JournalArticle";
    String dbUser = "root";
    String dbPassword = "";
    
    String message = "";
    String messageType = "";
    
    if (userName == null || articleSummary == null || journalName == null || 
        userName.trim().isEmpty() || articleSummary.trim().isEmpty() || journalName.trim().isEmpty()) {
        message = "Please fill in all required fields.";
        messageType = "error";
    } else {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
            
            int journalId = -1;
            
            // First, check if journal exists
            String checkJournalQuery = "SELECT id FROM Journals WHERE name = ?";
            PreparedStatement checkStmt = conn.prepareStatement(checkJournalQuery);
            checkStmt.setString(1, journalName.trim());
            ResultSet rs = checkStmt.executeQuery();
            
            if (rs.next()) {
                // Journal exists, get its ID
                journalId = rs.getInt("id");
                message = "Article added to existing journal: " + journalName;
            } else {
                // Journal doesn't exist, create new one
                String insertJournalQuery = "INSERT INTO Journals (name) VALUES (?)";
                PreparedStatement insertJournalStmt = conn.prepareStatement(insertJournalQuery, Statement.RETURN_GENERATED_KEYS);
                insertJournalStmt.setString(1, journalName.trim());
                
                int journalResult = insertJournalStmt.executeUpdate();
                if (journalResult > 0) {
                    ResultSet generatedKeys = insertJournalStmt.getGeneratedKeys();
                    if (generatedKeys.next()) {
                        journalId = generatedKeys.getInt(1);
                        message = "New journal created and article added: " + journalName;
                    }
                    generatedKeys.close();
                }
                insertJournalStmt.close();
            }
            
            rs.close();
            checkStmt.close();
            
            // Now insert the article if we have a valid journal ID
            if (journalId > 0) {
                String insertArticleQuery = "INSERT INTO Articles (journalid, user, summary, date) VALUES (?, ?, ?, ?)";
                PreparedStatement articleStmt = conn.prepareStatement(insertArticleQuery);
                articleStmt.setInt(1, journalId);
                articleStmt.setString(2, userName);
                articleStmt.setString(3, articleSummary);
                articleStmt.setDate(4, java.sql.Date.valueOf(LocalDate.now()));
                
                int articleResult = articleStmt.executeUpdate();
                
                if (articleResult > 0) {
                    messageType = "success";
                } else {
                    message = "Failed to add article.";
                    messageType = "error";
                }
                
                articleStmt.close();
            } else {
                message = "Failed to create or find journal.";
                messageType = "error";
            }
            
            conn.close();
            
        } catch (Exception e) {
            message = "Error adding article: " + e.getMessage();
            messageType = "error";
        }
    }
%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Add Article Result</title>
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
        <h1>Add Article Result</h1>
        <p class="<%= messageType %>"><%= message %></p>
        <button onclick="window.location.href='index.jsp'">Back to Main Page</button>
    </div>
</body>
</html>