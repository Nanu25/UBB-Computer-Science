<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String url = "jdbc:mysql://localhost:3306/examphp";
    String dbUser = "root";
    String dbPassword = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        String query = "SELECT id, name FROM Project ORDER BY name";
        PreparedStatement stmt = conn.prepareStatement(query);
        ResultSet rs = stmt.executeQuery();
        
        while (rs.next()) {
            out.println("<div class='checkbox-item'>");
            out.println("<input type='checkbox' name='projectIds' value='" + rs.getInt("id") + "' id='project_" + rs.getInt("id") + "'>");
            out.println("<label for='project_" + rs.getInt("id") + "'>" + rs.getString("name") + "</label>");
            out.println("</div>");
        }
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading projects: " + e.getMessage() + "</div>");
    }
%>
