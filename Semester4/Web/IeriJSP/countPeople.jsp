<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String date = request.getParameter("reservationDate");

    String url = "jdbc:mysql://localhost:3306/Ieri";
    String dbUser = "root";
    String dbPassword = "";
    
    String message = "";
    String messageType = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        
        String reservationList = "Select * from Reservation WHERE checkInDate <= ? and ? <= checkOutDate";
        PreparedStatement addStmt = conn.prepareStatement(reservationList);
        addStmt.setString(1, date);
        addStmt.setString(2, date);
        ResultSet membersRs = addStmt.executeQuery();
        int nr = 0;
        while(membersRs.next()) {       //e obligatoriu
            nr += 1;
        }

        out.println("<div class='project-card'>");
        out.println("<h4> Total: " + nr + "</h4>");
        out.println("</div>");
        message = "Count number '" + nr;
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
