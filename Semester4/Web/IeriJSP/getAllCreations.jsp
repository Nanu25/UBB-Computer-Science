<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%    
    String userName = request.getParameter("userName");
    
    if (userName == null || userName.trim().isEmpty()) {
        out.println("<div class='error'>User name is required</div>");
        return;
    }   
    String url = "jdbc:mysql://localhost:3306/MoviesDocuments?useSSL=false&serverTimezone=UTC";
    String dbUser = "root";
    String dbPassword = "";
      try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);

        String query = "SELECT * FROM Authors WHERE name LIKE ?";
        PreparedStatement stmt = conn.prepareStatement(query);
        stmt.setString(1, "%" + userName + "%");
        ResultSet rs = stmt.executeQuery();
        

            out.println("<div class='project-card'>");
        while (rs.next()) {
            String docList = rs.getString("documentList");
            String movieList = rs.getString("movieList");

            String[] documents = docList.trim().split("\\s+");
            String[] movies = movieList.trim().split("\\s+");

            int i = 0, j = 0, step = 0;
            while(i < documents.length && j < movies.length) {
                if(step % 2 == 0) {
                    out.println("<h4>Document: " + documents[i] + "</h4>");
                    i += 1;
                }else {
                    out.println("<h4>Movie List: " + movies[j] + "</h4>");
                    j += 1;
                }
                step += 1;
            }
            while(i < documents.length) {
                out.println("<h4>Document: " + documents[i] + "</h4>");
                i+= 1;  
            }

            while(j < movies.length) {
                    out.println("<h4>Movie List: " + movies[j] + "</h4>");
                    j += 1;        
            }

        }
            out.println("</div>");
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.println("<div class='error'>Error loading projects: " + e.getMessage() + "</div>");
    }
%>
