<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.util.List" %>
<%@ page import="com.forum.models.Topic" %>
<%@ page import="com.forum.models.User" %>
<%
    // Check if user is logged in
    User currentUser = (User) session.getAttribute("user");
    if (currentUser == null) {
        response.sendRedirect("login.jsp");
        return;
    }
%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Forum - Home</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <!-- Header -->
    <div class="header">
        <div class="header-content">
            <h1>Community Forum</h1>
            <div class="user-info">
                <span>Welcome, <%= currentUser.getUsername() %>!</span>
                <a href="logout" class="btn btn-secondary">Logout</a>
            </div>
        </div>
    </div>

    <div class="container">
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

        <!-- Create New Topic Section -->
        <div class="form-container">
            <h3>Create New Topic</h3>
            <form action="forum" method="post" onsubmit="return validateTopicForm()">
                <input type="hidden" name="action" value="create">
                
                <div class="form-group">
                    <label for="title">Topic Title:</label>
                    <input type="text" id="title" name="title" class="form-control" 
                           value="${param.title}" required>
                    <div id="titleError" class="error-message"></div>
                </div>
                
                <div class="form-group">
                    <label for="description">Description:</label>
                    <textarea id="description" name="description" class="form-control" 
                              rows="4" required>${param.description}</textarea>
                    <div id="descriptionError" class="error-message"></div>
                </div>
                
                <div class="form-group">
                    <button type="submit" class="btn btn-success">Create Topic</button>
                </div>
            </form>
        </div>

        <!-- Topics List -->
        <div class="card">
            <div class="card-header">
                <h3>Forum Topics</h3>
            </div>
            <div class="card-body">
                <%
                    @SuppressWarnings("unchecked")
                    List<Topic> topics = (List<Topic>) request.getAttribute("topics");
                    if (topics != null && !topics.isEmpty()) {
                %>
                    <% for (Topic topic : topics) { %>
                        <div class="card topic-item">
                            <div class="card-body">
                                <div class="topic-title">
                                    <a href="topic?id=<%= topic.getId() %>"><%= topic.getTitle() %></a>
                                </div>
                                <div class="topic-description">
                                    <%= topic.getDescription() %>
                                </div>
                                <div class="topic-meta">
                                    <span>By: <strong><%= topic.getUsername() %></strong> | 
                                          Posts: <%= topic.getPostCount() %> | 
                                          Created: <%= topic.getCreatedAt() %></span>
                                    <% if (topic.getUserId() == currentUser.getId()) { %>
                                        <button onclick="deleteTopic(<%= topic.getId() %>, '<%= topic.getTitle() %>')" 
                                                class="btn btn-danger btn-small">Delete</button>
                                    <% } %>
                                </div>
                            </div>
                        </div>
                    <% } %>
                <%
                    } else {
                %>
                    <p>No topics available. Be the first to create one!</p>
                <%
                    }
                %>
            </div>
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
                <p id="deleteMessage"></p>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-secondary" onclick="closeDeleteModal()">Cancel</button>
                <form id="deleteForm" method="post" style="display: inline;">
                    <input type="hidden" name="action" value="delete">
                    <input type="hidden" name="topicId" id="deleteTopicId">
                    <button type="submit" class="btn btn-danger">Delete</button>
                </form>
            </div>
        </div>
    </div>

    <script>
        function validateTopicForm() {
            let isValid = true;
            const title = document.getElementById('title').value.trim();
            const description = document.getElementById('description').value.trim();
            
            // Clear previous errors
            document.getElementById('titleError').textContent = '';
            document.getElementById('descriptionError').textContent = '';
            
            // Validate title
            if (title === '') {
                document.getElementById('titleError').textContent = 'Title is required';
                isValid = false;
            } else if (title.length < 5) {
                document.getElementById('titleError').textContent = 'Title must be at least 5 characters long';
                isValid = false;
            } else if (title.length > 255) {
                document.getElementById('titleError').textContent = 'Title must be no more than 255 characters long';
                isValid = false;
            }
            
            // Validate description
            if (description === '') {
                document.getElementById('descriptionError').textContent = 'Description is required';
                isValid = false;
            } else if (description.length < 10) {
                document.getElementById('descriptionError').textContent = 'Description must be at least 10 characters long';
                isValid = false;
            }
            
            return isValid;
        }

        function deleteTopic(topicId, topicTitle) {
            document.getElementById('deleteMessage').textContent = 
                'Are you sure you want to delete the topic "' + topicTitle + '"? This action cannot be undone.';
            document.getElementById('deleteTopicId').value = topicId;
            document.getElementById('deleteForm').action = 'forum';
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
