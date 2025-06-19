package com.forum.servlets;

import com.forum.dao.TopicDAO;
import com.forum.dao.PostDAO;
import com.forum.models.Topic;
import com.forum.models.Post;
import com.forum.models.User;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.List;

public class TopicServlet extends HttpServlet {
    private TopicDAO topicDAO;
    private PostDAO postDAO;
    
    @Override
    public void init() throws ServletException {
        topicDAO = new TopicDAO();
        postDAO = new PostDAO();
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
        
        String topicIdStr = request.getParameter("id");
        
        if (topicIdStr == null || topicIdStr.trim().isEmpty()) {
            response.sendRedirect(request.getContextPath() + "/forum");
            return;
        }
        
        try {
            int topicId = Integer.parseInt(topicIdStr);
            
            // Get topic details
            Topic topic = topicDAO.getTopicById(topicId);
            if (topic == null) {
                request.setAttribute("error", "Topic not found.");
                response.sendRedirect(request.getContextPath() + "/forum");
                return;
            }
            
            // Get all posts for this topic
            List<Post> posts = postDAO.getPostsByTopicId(topicId);
            
            request.setAttribute("topic", topic);
            request.setAttribute("posts", posts);
            request.getRequestDispatcher("/topic.jsp").forward(request, response);
            
        } catch (NumberFormatException e) {
            response.sendRedirect(request.getContextPath() + "/forum");
        }
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
        String topicIdStr = request.getParameter("topicId");
        
        if (topicIdStr == null || topicIdStr.trim().isEmpty()) {
            response.sendRedirect(request.getContextPath() + "/forum");
            return;
        }
        
        try {
            int topicId = Integer.parseInt(topicIdStr);
            
            if ("addPost".equals(action)) {
                addPost(request, response, session, topicId);
            } else {
                doGet(request, response);
            }
            
        } catch (NumberFormatException e) {
            response.sendRedirect(request.getContextPath() + "/forum");
        }
    }
    
    private void addPost(HttpServletRequest request, HttpServletResponse response, 
                        HttpSession session, int topicId) throws ServletException, IOException {
        
        String content = request.getParameter("content");
        
        // Input validation
        if (content == null || content.trim().isEmpty()) {
            request.setAttribute("error", "Post content is required.");
            request.getRequestDispatcher("/topic?id=" + topicId).forward(request, response);
            return;
        }
        
        if (content.trim().length() < 5) {
            request.setAttribute("error", "Post content must be at least 5 characters long.");
            request.setAttribute("content", content);
            request.getRequestDispatcher("/topic?id=" + topicId).forward(request, response);
            return;
        }
        
        User user = (User) session.getAttribute("user");
        Post post = new Post(content.trim(), topicId, user.getId());
        
        if (postDAO.createPost(post)) {
            request.setAttribute("success", "Post added successfully!");
        } else {
            request.setAttribute("error", "Failed to add post. Please try again.");
        }
        
        response.sendRedirect(request.getContextPath() + "/topic?id=" + topicId);
    }
}
