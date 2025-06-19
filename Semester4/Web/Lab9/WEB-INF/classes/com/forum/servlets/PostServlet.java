package com.forum.servlets;

import com.forum.dao.PostDAO;
import com.forum.models.Post;
import com.forum.models.User;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class PostServlet extends HttpServlet {
    private PostDAO postDAO;
    
    @Override
    public void init() throws ServletException {
        postDAO = new PostDAO();
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
        
        if ("delete".equals(action)) {
            deletePost(request, response, session);
        } else if ("edit".equals(action)) {
            editPost(request, response, session);
        } else {
            response.sendRedirect(request.getContextPath() + "/forum");
        }
    }
    
    private void deletePost(HttpServletRequest request, HttpServletResponse response, 
                           HttpSession session) throws ServletException, IOException {
        
        String postIdStr = request.getParameter("postId");
        String topicIdStr = request.getParameter("topicId");
        
        if (postIdStr == null || postIdStr.trim().isEmpty() ||
            topicIdStr == null || topicIdStr.trim().isEmpty()) {
            response.sendRedirect(request.getContextPath() + "/forum");
            return;
        }
        
        try {
            int postId = Integer.parseInt(postIdStr);
            int topicId = Integer.parseInt(topicIdStr);
            User user = (User) session.getAttribute("user");
            
            if (postDAO.deletePost(postId, user.getId())) {
                request.getSession().setAttribute("success", "Post deleted successfully!");
            } else {
                request.getSession().setAttribute("error", "Failed to delete post. You can only delete your own posts.");
            }
            
            response.sendRedirect(request.getContextPath() + "/topic?id=" + topicId);
            
        } catch (NumberFormatException e) {
            response.sendRedirect(request.getContextPath() + "/forum");
        }
    }
    
    private void editPost(HttpServletRequest request, HttpServletResponse response, 
                         HttpSession session) throws ServletException, IOException {
        
        String postIdStr = request.getParameter("postId");
        String topicIdStr = request.getParameter("topicId");
        String content = request.getParameter("content");
        
        if (postIdStr == null || postIdStr.trim().isEmpty() ||
            topicIdStr == null || topicIdStr.trim().isEmpty() ||
            content == null || content.trim().isEmpty()) {
            response.sendRedirect(request.getContextPath() + "/forum");
            return;
        }
        
        // Input validation
        if (content.trim().length() < 5) {
            request.getSession().setAttribute("error", "Post content must be at least 5 characters long.");
            response.sendRedirect(request.getContextPath() + "/topic?id=" + topicIdStr);
            return;
        }
        
        try {
            int postId = Integer.parseInt(postIdStr);
            int topicId = Integer.parseInt(topicIdStr);
            User user = (User) session.getAttribute("user");
            
            if (postDAO.updatePost(postId, content.trim(), user.getId())) {
                request.getSession().setAttribute("success", "Post updated successfully!");
            } else {
                request.getSession().setAttribute("error", "Failed to update post. You can only edit your own posts.");
            }
            
            response.sendRedirect(request.getContextPath() + "/topic?id=" + topicId);
            
        } catch (NumberFormatException e) {
            response.sendRedirect(request.getContextPath() + "/forum");
        }
    }
}
