package com.forum.dao;

import com.forum.models.Topic;
import com.forum.utils.DatabaseUtil;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class TopicDAO {
    
    public boolean createTopic(Topic topic) {
        String sql = "INSERT INTO topics (title, description, user_id) VALUES (?, ?, ?)";
        Connection conn = null;
        PreparedStatement pstmt = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, topic.getTitle());
            pstmt.setString(2, topic.getDescription());
            pstmt.setInt(3, topic.getUserId());
            
            int result = pstmt.executeUpdate();
            return result > 0;
            
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            DatabaseUtil.closeStatement(pstmt);
            DatabaseUtil.closeConnection(conn);
        }
    }
    
    public List<Topic> getAllTopics() {
        String sql = "SELECT t.*, u.username, " +
                    "(SELECT COUNT(*) FROM posts p WHERE p.topic_id = t.id) as post_count " +
                    "FROM topics t " +
                    "JOIN users u ON t.user_id = u.id " +
                    "ORDER BY t.created_at DESC";
        
        List<Topic> topics = new ArrayList<>();
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            pstmt = conn.prepareStatement(sql);
            rs = pstmt.executeQuery();
            
            while (rs.next()) {
                Topic topic = new Topic();
                topic.setId(rs.getInt("id"));
                topic.setTitle(rs.getString("title"));
                topic.setDescription(rs.getString("description"));
                topic.setUserId(rs.getInt("user_id"));
                topic.setUsername(rs.getString("username"));
                topic.setCreatedAt(rs.getTimestamp("created_at"));
                topic.setPostCount(rs.getInt("post_count"));
                topics.add(topic);
            }
            
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DatabaseUtil.closeResultSet(rs);
            DatabaseUtil.closeStatement(pstmt);
            DatabaseUtil.closeConnection(conn);
        }
        
        return topics;
    }
    
    public Topic getTopicById(int topicId) {
        String sql = "SELECT t.*, u.username FROM topics t " +
                    "JOIN users u ON t.user_id = u.id " +
                    "WHERE t.id = ?";
        
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, topicId);
            rs = pstmt.executeQuery();
            
            if (rs.next()) {
                Topic topic = new Topic();
                topic.setId(rs.getInt("id"));
                topic.setTitle(rs.getString("title"));
                topic.setDescription(rs.getString("description"));
                topic.setUserId(rs.getInt("user_id"));
                topic.setUsername(rs.getString("username"));
                topic.setCreatedAt(rs.getTimestamp("created_at"));
                return topic;
            }
            
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DatabaseUtil.closeResultSet(rs);
            DatabaseUtil.closeStatement(pstmt);
            DatabaseUtil.closeConnection(conn);
        }
        
        return null;
    }
    
    public boolean deleteTopic(int topicId, int userId) {
        String sql = "DELETE FROM topics WHERE id = ? AND user_id = ?";
        Connection conn = null;
        PreparedStatement pstmt = null;
        
        try {
            conn = DatabaseUtil.getConnection();
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, topicId);
            pstmt.setInt(2, userId);
            
            int result = pstmt.executeUpdate();
            return result > 0;
            
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            DatabaseUtil.closeStatement(pstmt);
            DatabaseUtil.closeConnection(conn);
        }
    }
}
