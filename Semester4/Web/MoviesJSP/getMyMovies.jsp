<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String userName = request.getParameter("userName");
    
    if (userName == null || userName.trim().isEmpty()) {
        out.println("<div class='error'>User name is required</div>");
        return;
    }
    
    String url = "jdbc:mysql://localhost:3306/MoviesDocuments";
    String dbUser = "root";
    String dbPassword = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        String query = "SELECT * FROM Authors WHERE name LIKE ?";
        PreparedStatement stmt = conn.prepareStatement(query);
        stmt.setString(1, "%" + userName + "%");
        ResultSet rs = stmt.executeQuery();
        while (rs.next()) {
            String movieList = rs.getString("movieList");
            String[] movies = movieList.trim().split("\\s+");
            
            for (String movie : movies) {
                    out.println("<div class='project-card'>");
                    out.println("<h4>" + movie + "</h4>");
                   out.println("<button onclick=\"deleteMovie('" + movie + "', '" + userName + "')\" class=\"btn btn-danger btn-small\">Delete</button>");

                    out.println("</div>");
            }
        }
        
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading your projects: " + e.getMessage() + "</div>");
    }
%>
