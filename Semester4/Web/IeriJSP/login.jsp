<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Login - Hotel</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
            margin: 0;
        }
        .login-container {
            background: white;
            padding: 40px;
            border-radius: 15px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.3);
            width: 100%;
            max-width: 400px;
        }
        h1 {
            text-align: center;
            color: #333;
            margin-bottom: 30px;
            font-size: 28px;
        }
        .form-group {
            margin-bottom: 20px;
        }
        label {
            display: block;
            margin-bottom: 8px;
            font-weight: bold;
            color: #555;
        }
        input[type="text"] {
            width: 100%;
            padding: 12px;
            border: 2px solid #ddd;
            border-radius: 8px;
            font-size: 16px;
            transition: border-color 0.3s;
            box-sizing: border-box;
        }
        input[type="text"]:focus {
            outline: none;
            border-color: #667eea;
        }
        .login-btn {
            width: 100%;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 12px;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            font-weight: bold;
            cursor: pointer;
            transition: transform 0.2s;
        }
        .login-btn:hover {
            transform: translateY(-2px);
        }
        .error {
            color: #dc3545;
            background-color: #f8d7da;
            border: 1px solid #f5c6cb;
            padding: 10px;
            border-radius: 5px;
            margin-bottom: 20px;
            text-align: center;
        }
        .success {
            color: #155724;
            background-color: #d4edda;
            border: 1px solid #c3e6cb;
            padding: 10px;
            border-radius: 5px;
            margin-bottom: 20px;
            text-align: center;
        }
    </style>
</head>
<body>
    <div class="login-container">
        <h1>Movie System Login</h1>
        
        <%
            String message = "";
            String messageType = "";
            
            if (request.getMethod().equalsIgnoreCase("POST")) {
                String userName = request.getParameter("userName");
                String password = request.getParameter("password");
                
                if (userName != null && !userName.trim().isEmpty() && 
                    password != null && !password.trim().isEmpty()) {
                    
                    try {
                        // Connect to database
                        String url = "jdbc:mysql://localhost:3306/Ieri";
                        String dbUser = "root";
                        String dbPassword = "";
                        
                        Class.forName("com.mysql.cj.jdbc.Driver");
                        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
                        
                        String checkQuery = "SELECT * FROM User WHERE username = ? and password = ?";
                        PreparedStatement checkStmt = conn.prepareStatement(checkQuery);
                        checkStmt.setString(1, userName);
                        checkStmt.setString(2, password);
                        ResultSet rs = checkStmt.executeQuery();
                        
                        if (rs.next()) {
                            // Creation matches, login successful
                            session.setAttribute("userName", userName);
                            response.sendRedirect("index.jsp");
                            return;    
                        } else {
                            message = "Try again";
                            messageType = "error";
                        }
                        
                    } catch (Exception e) {
                        message = "Database error: " + e.getMessage();
                        messageType = "error";
                        e.printStackTrace(); // For debugging
                    }
                } else {
                    message = "Please fill in all fields.";
                    messageType = "error";
                }
            }
        %>
        
        <% if (!message.isEmpty()) { %>
            <div class="<%= messageType %>"><%= message %></div>
        <% } %>
        
        <form method="post" action="login.jsp">
            <div class="form-group">
                <label for="userName">Enter your name:</label>
                <input type="text" id="userName" name="userName" 
                       value="<%= request.getParameter("userName") != null ? request.getParameter("userName") : "" %>" 
                       required>
            </div>
            
            <div class="form-group">
                <label for="creation">Password:</label>
                <input type="password" id="creation" name="password" 
                       value="<%= request.getParameter("password") != null ? request.getParameter("password") : "" %>" 
                       required>
            </div>
            
            <button type="submit" class="login-btn">Login</button>
        </form>
    </div>
</body>
</html>