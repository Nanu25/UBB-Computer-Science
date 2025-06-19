<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Login - Movie Management System</title>
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
                String creation = request.getParameter("creation");
                
                if (userName != null && !userName.trim().isEmpty() && 
                    creation != null && !creation.trim().isEmpty()) {
                    
                    try {
                        // Connect to database
                        String url = "jdbc:mysql://localhost:3306/MoviesDocuments";
                        String dbUser = "root";
                        String dbPassword = "";
                        
                        Class.forName("com.mysql.cj.jdbc.Driver");
                        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
                        
                        // Check if user exists in Authors table
                        String checkQuery = "SELECT * FROM Authors WHERE name = ?";
                        PreparedStatement checkStmt = conn.prepareStatement(checkQuery);
                        checkStmt.setString(1, userName);
                        ResultSet rs = checkStmt.executeQuery();
                        
                        if (rs.next()) {
                            // User exists, check if creation matches their documents or movies
                            String documentList = rs.getString("documentList");
                            String movieList = rs.getString("movieList");
                            
                            boolean creationFound = false;
                            
                            // Check documents
                            if (documentList != null && !documentList.trim().isEmpty()) {
                                String[] documents = documentList.trim().split("\\s+");
                                for (String doc : documents) {
                                    if (doc.trim().equalsIgnoreCase(creation.trim())) {
                                        creationFound = true;
                                        break;
                                    }
                                }
                            }
                            
                            // Check movies if not found in documents
                            if (!creationFound && movieList != null && !movieList.trim().isEmpty()) {
                                String[] movies = movieList.trim().split("\\s+");
                                for (String movie : movies) {
                                    if (movie.trim().equalsIgnoreCase(creation.trim())) {
                                        creationFound = true;
                                        break;
                                    }
                                }
                            }
                            
                            if (creationFound) {
                                // Creation matches, login successful
                                session.setAttribute("userName", userName);
                                response.sendRedirect("index.jsp");
                                return;
                            } else {
                                // User exists but creation doesn't match
                                message = "The creation '" + creation + "' is not associated with user '" + userName + "'. Please check your input.";
                                messageType = "error";
                            }
                            
                        } else {
                            message = "The user doesn t exist";
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
                <label for="creation">Enter a document/movie name that you wrote:</label>
                <input type="text" id="creation" name="creation" 
                       value="<%= request.getParameter("creation") != null ? request.getParameter("creation") : "" %>" 
                       required>
            </div>
            
            <button type="submit" class="login-btn">Login</button>
        </form>
    </div>
</body>
</html>