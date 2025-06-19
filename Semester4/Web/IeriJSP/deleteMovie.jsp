<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String movieName = request.getParameter("movieName");
    String userName = request.getParameter("userName");

    System.out.println("Received movieName: " + movieName);
    System.out.println("Received userName: " + userName);

    String url = "jdbc:mysql://localhost:3306/MoviesDocuments";
    String dbUser = "root";
    String dbPassword = "";
    
    String message = "";
    String messageType = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        // Delete from Movies table (using 'title' column based on your database schema)
        String deleteMovie = "DELETE FROM Movies WHERE title = ?";
        PreparedStatement delStmt = conn.prepareStatement(deleteMovie);
        delStmt.setString(1, movieName);
        delStmt.executeUpdate();
        
        // Get current movieList from Authors
        String movieListInitial = "SELECT movieList FROM Authors WHERE name = ?";
        PreparedStatement getMembersStmt = conn.prepareStatement(movieListInitial);
        getMembersStmt.setString(1, userName);
        ResultSet membersRs = getMembersStmt.executeQuery();

        if (membersRs.next()) {
            String movieList = membersRs.getString("movieList");
            String[] movies = movieList.trim().split("\\s+");
            String newMovieList = ""; // Initialize as empty string
            
            for (String movie : movies) {
                if (!movie.trim().equalsIgnoreCase(movieName.trim())) {
                    if (!newMovieList.isEmpty()) {
                        newMovieList += " ";
                    }
                    newMovieList += movie;
                }
            }
            
            // Update the Authors table
            String updateMov = "UPDATE Authors SET movieList = ? WHERE name = ?";
            PreparedStatement updateStmt = conn.prepareStatement(updateMov);
            updateStmt.setString(1, newMovieList.trim());
            updateStmt.setString(2, userName);
            updateStmt.executeUpdate();
            updateStmt.close();
        }
        
        membersRs.close();
        getMembersStmt.close();
        delStmt.close();
        conn.close();

        message = "Movie '" + movieName + "' has been deleted.";
        messageType = "success";

    } catch (Exception e) {
        message = "Error deleting movie: " + e.getMessage();
        messageType = "error";
        e.printStackTrace(); // For debugging
    }
%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Delete Result</title>
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
        <h1>Delete Result</h1>
        <p class="<%= messageType %>"><%= message %></p>
        <button onclick="window.location.href='index.jsp'">Back to Main Page</button>
    </div>
</body>
</html>