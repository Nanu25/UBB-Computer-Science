<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String userName = request.getParameter("userName");
    
    if (userName == null || userName.trim().isEmpty()) {
        out.println("<div class='error'>User name is required</div>");
        return;
    }
    
    String url = "jdbc:mysql://localhost:3306/Ieri";
    String dbUser = "root";
    String dbPassword = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        String query = "SELECT * FROM User WHERE username LIKE ?";
        PreparedStatement stmt = conn.prepareStatement(query);
        stmt.setString(1, "%" + userName + "%");
        ResultSet rs = stmt.executeQuery();

        rs.next();

        String query1 = "SELECT * FROM Reservation WHERE userId = ?";
        PreparedStatement stmt1 = conn.prepareStatement(query1);
        stmt1.setString(1,rs.getString("id"));
        ResultSet rs1 = stmt1.executeQuery(); 

        while (rs1.next()) {
            out.println("<div class='project-card'>");
            out.println("<h4>" + rs1.getString("checkInDate") + "</h4>");
            out.println("<h4>" + rs1.getString("checkOutDate") + "</h4>");
            out.println("<h4>" + rs1.getInt("numberOfGuests") + "</h4>");
            out.println("<h4>" + rs1.getInt("totalPrice") + "</h4>");


            out.println("</div>");
            
        }
        
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading your projects: " + e.getMessage() + "</div>");
    }
%>
