<%@ page language="java" contentType="application/json; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String url = "jdbc:mysql://localhost:3306/examphp?useSSL=false&serverTimezone=UTC";
    String dbUser = "root";
    String dbPassword = "";
    
    response.setContentType("application/json");
    response.setCharacterEncoding("UTF-8");
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        String query = "SELECT id, name, age, skills FROM softwaredeveloper ORDER BY name";
        PreparedStatement stmt = conn.prepareStatement(query);
        ResultSet rs = stmt.executeQuery();
        
        out.print("[");
        boolean first = true;
        while (rs.next()) {
            if (!first) out.print(",");
            out.print("{");
            out.print("\"id\":" + rs.getInt("id") + ",");
            out.print("\"name\":\"" + (rs.getString("name") != null ? rs.getString("name").replace("\"", "\\\"") : "") + "\",");
            out.print("\"age\":" + rs.getInt("age") + ",");
            out.print("\"skills\":\"" + (rs.getString("skills") != null ? rs.getString("skills").replace("\"", "\\\"") : "") + "\"");
            out.print("}");
            first = false;
        }
        out.print("]");
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.print("[{\"error\":\"" + e.getMessage().replace("\"", "\\\"") + "\"}]");
    }
%>
