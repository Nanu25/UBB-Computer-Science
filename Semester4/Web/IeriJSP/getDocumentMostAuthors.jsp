<%@ page language="java" contentType="application/json; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="java.util.*" %>

<%
    String url = "jdbc:mysql://localhost:3306/MoviesDocuments?useSSL=false&serverTimezone=UTC";
    String dbUser = "root";
    String dbPassword = "";
    
    response.setContentType("application/json");
    response.setCharacterEncoding("UTF-8");
    
    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
        
        // Get all documents
        String query = "SELECT name FROM Documents";
        PreparedStatement stmt = conn.prepareStatement(query);
        ResultSet rs = stmt.executeQuery();
        
        String maxDocument = "";
        int maxCount = 0;
        
        // Iterate through each document
        while (rs.next()) {
            String documentName = rs.getString("name");
            
            // Get all authors and count how many have this document
            String authorsQuery = "SELECT * FROM Authors";
            PreparedStatement authorsStmt = conn.prepareStatement(authorsQuery);
            ResultSet authorsRs = authorsStmt.executeQuery();
            
            int count = 0;
            
            while (authorsRs.next()) {
                String documentList = authorsRs.getString("documentList");
                
                if (documentList != null && !documentList.trim().isEmpty()) {
                    String[] documents = documentList.trim().split("\\s+");
                    for (String doc : documents) {
                        if (doc.trim().equalsIgnoreCase(documentName.trim())) {
                            count++;
                            break; // Found it, no need to check other documents for this author
                        }
                    }
                }
            }
            
            // Check if this document has more authors than current max
            if (count > maxCount) {
                maxCount = count;
                maxDocument = documentName;
            }
            
            authorsRs.close();
            authorsStmt.close();
        }
        
        // Output result
        out.print("[{");
        out.print("\"document\":\"" + maxDocument + "\",");
        out.print("\"authorCount\":" + maxCount + ",");
        out.print("\"message\":\"Document '" + maxDocument + "' appears in " + maxCount + " authors' document lists\"");
        out.print("}]");
        
        rs.close();
        stmt.close();
        conn.close();
        
    } catch (Exception e) {
        out.print("[{\"error\":\"" + e.getMessage().replace("\"", "\\\"") + "\"}]");
    }
%>