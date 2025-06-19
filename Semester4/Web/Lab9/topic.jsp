<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.util.List" %>
<%@ page import="com.forum.models.Topic" %>
<%@ page import="com.forum.models.Post" %>
<%@ page import="com.forum.models.User" %>
<%
    // Check if user is logged in
    User currentUser = (User) session.getAttribute("user");
    if (currentUser == null) {
        response.sendRedirect("login.jsp");
        return;
    }
    
    Topic topic = (Topic) request.getAttribute("topic");
    if (topic == null) {
        response.sendRedirect("forum");
        return;
    }
%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Forum - <%= topic.getTitle() %></title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <!-- Header -->
    <div class="header">
        <div class="header-content">
            <h1><a href="forum" style="color: white; text-decoration: none;">Community Forum</a></h1>
            <div class="user-info">
                <span>Welcome, <%= currentUser.getUsername() %>!</span>
                <a href="logout" class="btn btn-secondary">Logout</a>
            </div>
        </div>
    </div>

    <div class="container">
        <!-- Navigation -->
        <div style="margin-bottom: 1rem;">
            <a href="forum" class="btn btn-secondary">← Back to Forum</a>
        </div>

        <!-- Messages -->
        <% String error = (String) request.getAttribute("error"); %>
        <% String sessionError = (String) session.getAttribute("error"); %>
        <% if (error != null || sessionError != null) { %>
            <div class="alert alert-error">
                <%= error != null ? error : sessionError %>
            </div>
            <% session.removeAttribute("error"); %>
        <% } %>
        
        <% String success = (String) request.getAttribute("success"); %>
        <% String sessionSuccess = (String) session.getAttribute("success"); %>
        <% if (success != null || sessionSuccess != null) { %>
            <div class="alert alert-success">
                <%= success != null ? success : sessionSuccess %>
            </div>
            <% session.removeAttribute("success"); %>
        <% } %>

        <!-- Topic Header -->
        <div class="card">
            <div class="card-header">
                <h2><%= topic.getTitle() %></h2>
            </div>
            <div class="card-body">
                <p><%= topic.getDescription() %></p>
            </div>
            <div class="card-footer">
                Created by <strong><%= topic.getUsername() %></strong> on <%= topic.getCreatedAt() %>
            </div>
        </div>

        <!-- Posts -->
        <div class="card">
            <div class="card-header">
                <h3>Posts</h3>
            </div>
            <div class="card-body">
                <%
                    @SuppressWarnings("unchecked")
                    List<Post> posts = (List<Post>) request.getAttribute("posts");
                    if (posts != null && !posts.isEmpty()) {
                %>
                    <% for (Post post : posts) { %>
                        <div class="card post-item">
                            <div class="card-body">
                                <div class="post-content" id="post-content-<%= post.getId() %>">
                                    <%= post.getContent().replace("\n", "<br>") %>
                                </div>
                                
                                <!-- Edit form (hidden by default) -->
                                <div id="edit-form-<%= post.getId() %>" style="display: none;">
                                    <form action="post" method="post" onsubmit="return validatePostEdit(<%= post.getId() %>)">
                                        <input type="hidden" name="action" value="edit">
                                        <input type="hidden" name="postId" value="<%= post.getId() %>">
                                        <input type="hidden" name="topicId" value="<%= topic.getId() %>">
                                        <div class="form-group">
                                            <textarea name="content" id="edit-content-<%= post.getId() %>" 
                                                      class="form-control" rows="4" required><%= post.getContent() %></textarea>
                                            <div id="editError-<%= post.getId() %>" class="error-message"></div>
                                        </div>
                                        <div class="post-actions">
                                            <button type="submit" class="btn btn-success btn-small">Save</button>
                                            <button type="button" class="btn btn-secondary btn-small" 
                                                    onclick="cancelEdit(<%= post.getId() %>)">Cancel</button>
                                        </div>
                                    </form>
                                </div>
                            </div>
                            <div class="card-footer">
                                <div style="display: flex; justify-content: space-between; align-items: center;">
                                    <span>By <strong><%= post.getUsername() %></strong> on <%= post.getCreatedAt() %></span>
                                    <% if (post.getUserId() == currentUser.getId()) { %>
                                        <div class="post-actions" id="post-actions-<%= post.getId() %>">
                                            <button onclick="editPost(<%= post.getId() %>)" 
                                                    class="btn btn-primary btn-small">Edit</button>
                                            <button onclick="deletePost(<%= post.getId() %>, <%= topic.getId() %>)" 
                                                    class="btn btn-danger btn-small">Delete</button>
                                        </div>
                                    <% } %>
                                </div>
                            </div>
                        </div>
                    <% } %>
                <%
                    } else {
                %>
                    <p>No posts yet. Be the first to comment!</p>
                <%
                    }
                %>
            </div>
        </div>

        <!-- Add New Post -->
        <div class="form-container">
            <h3>Add a Post</h3>
            <form action="topic" method="post" onsubmit="return validatePostForm()">
                <input type="hidden" name="action" value="addPost">
                <input type="hidden" name="topicId" value="<%= topic.getId() %>">
                
                <div class="form-group">
                    <label for="content">Your Post:</label>
                    <textarea id="content" name="content" class="form-control" 
                              rows="5" placeholder="Write your post here..." required>${param.content}</textarea>
                    <div id="contentError" class="error-message"></div>
                </div>
                
                <div class="form-group">
                    <button type="submit" class="btn btn-success">Add Post</button>
                </div>
            </form>
        </div>
    </div>

    <!-- Delete Confirmation Modal -->
    <div id="deleteModal" class="modal">
        <div class="modal-content">
            <div class="modal-header">
                <h4>Confirm Delete</h4>
                <span class="close" onclick="closeDeleteModal()">&times;</span>
            </div>
            <div class="modal-body">
                <p>Are you sure you want to delete this post? This action cannot be undone.</p>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-secondary" onclick="closeDeleteModal()">Cancel</button>
                <form id="deleteForm" action="post" method="post" style="display: inline;">
                    <input type="hidden" name="action" value="delete">
                    <input type="hidden" name="postId" id="deletePostId">
                    <input type="hidden" name="topicId" id="deleteTopicId">
                    <button type="submit" class="btn btn-danger">Delete</button>
                </form>
            </div>
        </div>
    </div>

    <script>
        function validatePostForm() {
            const content = document.getElementById('content').value.trim();
            
            // Clear previous errors
            document.getElementById('contentError').textContent = '';
            
            // Validate content
            if (content === '') {
                document.getElementById('contentError').textContent = 'Post content is required';
                return false;
            } else if (content.length < 5) {
                document.getElementById('contentError').textContent = 'Post content must be at least 5 characters long';
                return false;
            }
            
            return true;
        }

        function validatePostEdit(postId) {
            const content = document.getElementById('edit-content-' + postId).value.trim();
            
            // Clear previous errors
            document.getElementById('editError-' + postId).textContent = '';
            
            // Validate content
            if (content === '') {
                document.getElementById('editError-' + postId).textContent = 'Post content is required';
                return false;
            } else if (content.length < 5) {
                document.getElementById('editError-' + postId).textContent = 'Post content must be at least 5 characters long';
                return false;
            }
            
            return true;
        }

        function editPost(postId) {
            document.getElementById('post-content-' + postId).style.display = 'none';
            document.getElementById('post-actions-' + postId).style.display = 'none';
            document.getElementById('edit-form-' + postId).style.display = 'block';
        }

        function cancelEdit(postId) {
            document.getElementById('post-content-' + postId).style.display = 'block';
            document.getElementById('post-actions-' + postId).style.display = 'block';
            document.getElementById('edit-form-' + postId).style.display = 'none';
        }

        function deletePost(postId, topicId) {
            document.getElementById('deletePostId').value = postId;
            document.getElementById('deleteTopicId').value = topicId;
            document.getElementById('deleteModal').style.display = 'block';
        }

        function closeDeleteModal() {
            document.getElementById('deleteModal').style.display = 'none';
        }

        // Close modal when clicking outside of it
        window.onclick = function(event) {
            const modal = document.getElementById('deleteModal');
            if (event.target == modal) {
                modal.style.display = 'none';
            }
        }
    </script>
    
    <style>
        .error-message {
            color: #e74c3c;
            font-size: 12px;
            margin-top: 5px;
            display: block;
        }
    </style>
</body>
</html>
