<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Forum - Login</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="auth-container">
        <div class="auth-card">
            <h2 class="auth-title">Login to Forum</h2>
            
            <% String error = (String) request.getAttribute("error"); %>
            <% if (error != null) { %>
                <div class="alert alert-error">
                    <%= error %>
                </div>
            <% } %>
            
            <% String success = (String) request.getAttribute("success"); %>
            <% if (success != null) { %>
                <div class="alert alert-success">
                    <%= success %>
                </div>
            <% } %>
            
            <form action="login" method="post" onsubmit="return validateLoginForm()">
                <div class="form-group">
                    <label for="username">Username:</label>
                    <input type="text" id="username" name="username" class="form-control" 
                           value="${param.username}" required>
                    <div id="usernameError" class="error-message"></div>
                </div>
                
                <div class="form-group">
                    <label for="password">Password:</label>
                    <input type="password" id="password" name="password" class="form-control" required>
                    <div id="passwordError" class="error-message"></div>
                </div>
                
                <div class="form-group">
                    <button type="submit" class="btn btn-primary" style="width: 100%;">Login</button>
                </div>
            </form>
            
            <div class="auth-footer">
                Don't have an account? <a href="register">Register here</a>
            </div>
        </div>
    </div>

    <script>
        function validateLoginForm() {
            let isValid = true;
            const username = document.getElementById('username').value.trim();
            const password = document.getElementById('password').value;
            
            // Clear previous errors
            document.getElementById('usernameError').textContent = '';
            document.getElementById('passwordError').textContent = '';
            
            // Validate username
            if (username === '') {
                document.getElementById('usernameError').textContent = 'Username is required';
                isValid = false;
            } else if (username.length < 3) {
                document.getElementById('usernameError').textContent = 'Username must be at least 3 characters long';
                isValid = false;
            }
            
            // Validate password
            if (password === '') {
                document.getElementById('passwordError').textContent = 'Password is required';
                isValid = false;
            } else if (password.length < 6) {
                document.getElementById('passwordError').textContent = 'Password must be at least 6 characters long';
                isValid = false;
            }
            
            return isValid;
        }
    </script>
    
    <style>
        .error-message {
            color: #e74c3c;
            font-size: 12px;
            margin-top: 5px;
            display: block;
        }
    </style>
</body>
</html>
