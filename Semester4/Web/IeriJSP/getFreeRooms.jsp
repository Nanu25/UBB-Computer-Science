<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>
<%@ page import="java.text.SimpleDateFormat" %>

<%
    String dateIn = request.getParameter("dateIn");
    String dateOut = request.getParameter("dateOut");
    
    String url = "jdbc:mysql://localhost:3306/Ieri";
    String dbUser = "root";
    String dbPassword = "";
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        String query = "SELECT * FROM HotelRoom";
        PreparedStatement stmt = conn.prepareStatement(query);
        ResultSet rs = stmt.executeQuery();

        while (rs.next()) {
            int roomId = rs.getInt("id");
            String roomNumber = rs.getString("roomNumber");
            int capacity = rs.getInt("capacity");
            
            // Check if this room has any conflicting reservations
            String query2 = "SELECT * FROM Reservation WHERE roomId = ? AND NOT (? >= checkOutDate OR ? <= checkInDate)";
            PreparedStatement stmt2 = conn.prepareStatement(query2);
            stmt2.setInt(1, roomId);
            stmt2.setString(2, dateIn);
            stmt2.setString(3, dateOut);
            ResultSet res = stmt2.executeQuery();

            // If no conflicting reservations found, room is free
            if (!res.next()) {
                out.println("<div class='project-card'>");
                out.println("<h4>Room ID: " + roomId + "</h4>");
                out.println("<h4>Room Number: " + roomNumber + "</h4>");
                out.println("<h4>Capacity: " + capacity + "</h4>");
                out.println("</div>");
            }
            
            res.close();
            stmt2.close();
        }
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading free rooms: " + e.getMessage() + "</div>");
    }
%>