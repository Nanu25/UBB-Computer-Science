<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%    String url = "jdbc:mysql://localhost:3306/examphp?useSSL=false&serverTimezone=UTC";
    String dbUser = "root";
    String dbPassword = "";
      try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
          String query = "SELECT p.id, p.ProjectManagerID, p.name, p.description, p.members, sd.name as manager_name " +
                      "FROM project p LEFT JOIN softwaredeveloper sd ON p.ProjectManagerID = sd.id " +
                      "ORDER BY p.id";
        
        PreparedStatement stmt = conn.prepareStatement(query);
        ResultSet rs = stmt.executeQuery();
        
        while (rs.next()) {
            out.println("<div class='project-card'>");
            out.println("<h4>Project: " + rs.getString("name") + "</h4>");
            out.println("<p><strong>ID:</strong> " + rs.getInt("id") + "</p>");
            out.println("<p><strong>Description:</strong> " + (rs.getString("description") != null ? rs.getString("description") : "No description") + "</p>");
            out.println("<p><strong>Project Manager:</strong> " + (rs.getString("manager_name") != null ? rs.getString("manager_name") : "Not assigned") + "</p>");
            out.println("<p><strong>Members:</strong> " + (rs.getString("members") != null ? rs.getString("members") : "No members") + "</p>");
            out.println("</div>");
        }
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading projects: " + e.getMessage() + "</div>");
    }
%>
