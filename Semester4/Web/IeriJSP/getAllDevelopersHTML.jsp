<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String url = "jdbc:mysql://localhost:3306/examphp?useSSL=false&serverTimezone=UTC";
    String dbUser = "root";
    String dbPassword = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        String query = "SELECT id, name, age, skills FROM softwaredeveloper ORDER BY name";
        PreparedStatement stmt = conn.prepareStatement(query);
        ResultSet rs = stmt.executeQuery();
        
        while (rs.next()) {
            out.println("<div class='developer-card'>");
            out.println("<h4>Developer: " + rs.getString("name") + "</h4>");
            out.println("<p><strong>ID:</strong> " + rs.getInt("id") + "</p>");
            out.println("<p><strong>Age:</strong> " + rs.getInt("age") + "</p>");
            out.println("<p><strong>Skills:</strong> " + (rs.getString("skills") != null ? rs.getString("skills") : "No skills listed") + "</p>");
            out.println("</div>");
        }
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading developers: " + e.getMessage() + "</div>");
    }
%>
