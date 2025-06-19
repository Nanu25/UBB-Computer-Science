package com.forum.servlets;

import com.forum.dao.UserDAO;
import com.forum.models.User;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.regex.Pattern;

public class RegisterServlet extends HttpServlet {
    private UserDAO userDAO;
    
    @Override
    public void init() throws ServletException {
        userDAO = new UserDAO();
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        request.getRequestDispatcher("/register.jsp").forward(request, response);
    }
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String confirmPassword = request.getParameter("confirmPassword");
        String email = request.getParameter("email");
        
        // Input validation
        StringBuilder errors = new StringBuilder();
        
        if (username == null || username.trim().isEmpty()) {
            errors.append("Username is required. ");
        } else if (username.trim().length() < 3) {
            errors.append("Username must be at least 3 characters long. ");
        } else if (username.trim().length() > 50) {
            errors.append("Username must be no more than 50 characters long. ");
        }
        
        if (password == null || password.isEmpty()) {
            errors.append("Password is required. ");
        } else if (password.length() < 6) {
            errors.append("Password must be at least 6 characters long. ");
        }
        
        if (confirmPassword == null || !password.equals(confirmPassword)) {
            errors.append("Passwords do not match. ");
        }
        
        if (email == null || email.trim().isEmpty()) {
            errors.append("Email is required. ");
        } else if (!isValidEmail(email.trim())) {
            errors.append("Please enter a valid email address. ");
        }
        
        // Check if username already exists
        if (errors.length() == 0 && userDAO.userExists(username.trim())) {
            errors.append("Username already exists. Please choose another one. ");
        }
        
        if (errors.length() > 0) {
            request.setAttribute("error", errors.toString().trim());
            request.setAttribute("username", username);
            request.setAttribute("email", email);
            request.getRequestDispatcher("/register.jsp").forward(request, response);
            return;
        }
        
        // Create new user
        User user = new User(username.trim(), password, email.trim());
        
        if (userDAO.createUser(user)) {
            request.setAttribute("success", "Registration successful! Please login with your credentials.");
            request.getRequestDispatcher("/login.jsp").forward(request, response);
        } else {
            request.setAttribute("error", "Registration failed. Please try again.");
            request.setAttribute("username", username);
            request.setAttribute("email", email);
            request.getRequestDispatcher("/register.jsp").forward(request, response);
        }
    }
    
    private boolean isValidEmail(String email) {
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@" +
                           "(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
        Pattern pattern = Pattern.compile(emailRegex);
        return pattern.matcher(email).matches();
    }
}
