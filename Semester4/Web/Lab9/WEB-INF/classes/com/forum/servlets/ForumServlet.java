package com.forum.servlets;

import com.forum.dao.TopicDAO;
import com.forum.models.Topic;
import com.forum.models.User;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.List;

public class ForumServlet extends HttpServlet {
    private TopicDAO topicDAO;
    
    @Override
    public void init() throws ServletException {
        topicDAO = new TopicDAO();
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Check if user is logged in
        HttpSession session = request.getSession(false);
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect(request.getContextPath() + "/login.jsp");
            return;
        }
        
        // Get all topics
        List<Topic> topics = topicDAO.getAllTopics();
        request.setAttribute("topics", topics);
        
        request.getRequestDispatcher("/forum.jsp").forward(request, response);
    }
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Check if user is logged in
        HttpSession session = request.getSession(false);
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect(request.getContextPath() + "/login.jsp");
            return;
        }
        
        String action = request.getParameter("action");
        
        if ("create".equals(action)) {
            createTopic(request, response, session);
        } else if ("delete".equals(action)) {
            deleteTopic(request, response, session);
        } else {
            doGet(request, response);
        }
    }
    
    private void createTopic(HttpServletRequest request, HttpServletResponse response, 
                           HttpSession session) throws ServletException, IOException {
        
        String title = request.getParameter("title");
        String description = request.getParameter("description");
        
        // Input validation
        StringBuilder errors = new StringBuilder();
        
        if (title == null || title.trim().isEmpty()) {
            errors.append("Title is required. ");
        } else if (title.trim().length() < 5) {
            errors.append("Title must be at least 5 characters long. ");
        } else if (title.trim().length() > 255) {
            errors.append("Title must be no more than 255 characters long. ");
        }
        
        if (description == null || description.trim().isEmpty()) {
            errors.append("Description is required. ");
        } else if (description.trim().length() < 10) {
            errors.append("Description must be at least 10 characters long. ");
        }
        
        if (errors.length() > 0) {
            request.setAttribute("error", errors.toString().trim());
            request.setAttribute("title", title);
            request.setAttribute("description", description);
            doGet(request, response);
            return;
        }
        
        User user = (User) session.getAttribute("user");
        Topic topic = new Topic(title.trim(), description.trim(), user.getId());
        
        if (topicDAO.createTopic(topic)) {
            request.setAttribute("success", "Topic created successfully!");
        } else {
            request.setAttribute("error", "Failed to create topic. Please try again.");
        }
        
        doGet(request, response);
    }
    
    private void deleteTopic(HttpServletRequest request, HttpServletResponse response, 
                           HttpSession session) throws ServletException, IOException {
        
        String topicIdStr = request.getParameter("topicId");
        
        if (topicIdStr == null || topicIdStr.trim().isEmpty()) {
            request.setAttribute("error", "Invalid topic ID.");
            doGet(request, response);
            return;
        }
        
        try {
            int topicId = Integer.parseInt(topicIdStr);
            User user = (User) session.getAttribute("user");
            
            if (topicDAO.deleteTopic(topicId, user.getId())) {
                request.setAttribute("success", "Topic deleted successfully!");
            } else {
                request.setAttribute("error", "Failed to delete topic. You can only delete your own topics.");
            }
            
        } catch (NumberFormatException e) {
            request.setAttribute("error", "Invalid topic ID.");
        }
        
        doGet(request, response);
    }
}
