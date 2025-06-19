package com.forum.models;

import java.sql.Timestamp;

public class Topic {
    private int id;
    private String title;
    private String description;
    private int userId;
    private String username;
    private Timestamp createdAt;
    private int postCount;
    
    public Topic() {}
    
    public Topic(String title, String description, int userId) {
        this.title = title;
        this.description = description;
        this.userId = userId;
    }
    
    // Getters and Setters
    public int getId() {
        return id;
    }
    
    public void setId(int id) {
        this.id = id;
    }
    
    public String getTitle() {
        return title;
    }
    
    public void setTitle(String title) {
        this.title = title;
    }
    
    public String getDescription() {
        return description;
    }
    
    public void setDescription(String description) {
        this.description = description;
    }
    
    public int getUserId() {
        return userId;
    }
    
    public void setUserId(int userId) {
        this.userId = userId;
    }
    
    public String getUsername() {
        return username;
    }
    
    public void setUsername(String username) {
        this.username = username;
    }
    
    public Timestamp getCreatedAt() {
        return createdAt;
    }
    
    public void setCreatedAt(Timestamp createdAt) {
        this.createdAt = createdAt;
    }
    
    public int getPostCount() {
        return postCount;
    }
    
    public void setPostCount(int postCount) {
        this.postCount = postCount;
    }
}
