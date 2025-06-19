<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String userName = request.getParameter("userName");
    
    if (userName == null || userName.trim().isEmpty()) {
        out.println("<div class='error'>User name is required</div>");
        return;
    }
    
    String url = "jdbc:mysql://localhost:3306/JournalArticle";
    String dbUser = "root";
    String dbPassword = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        String query = "SELECT summary FROM Articles WHERE user LIKE ?";
        PreparedStatement stmt = conn.prepareStatement(query);
        stmt.setString(1, "%" + userName + "%");
        
        ResultSet rs = stmt.executeQuery();
        
        boolean hasProjects = false;
        while (rs.next()) {
            hasProjects = true;
            out.println("<div class='project-card'>");
            out.println("<h4>" + rs.getString("summary") + "</h4>");
            out.println("</div>");
        }
        
        if (!hasProjects) {
            out.println("<p>You are not a member of any projects.</p>");
        }
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading your projects: " + e.getMessage() + "</div>");
    }
%>
