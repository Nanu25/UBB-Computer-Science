<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Journal Article</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .container {
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            margin-bottom: 20px;
        }
        h1 {
            color: #333;
            text-align: center;
            margin-bottom: 30px;
        }
        h2 {
            color: #555;
            border-bottom: 2px solid #007bff;
            padding-bottom: 10px;
        }
        .form-group {
            margin-bottom: 15px;
        }
        label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
            color: #333;
        }
        input[type="text"], textarea, select {
            width: 100%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 5px;
            font-size: 14px;
        }
        button {
            background-color: #007bff;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 14px;
            margin-right: 10px;
        }
        button:hover {
            background-color: #0056b3;
        }
        .project-card, .developer-card {
            border: 1px solid #ddd;
            padding: 15px;
            margin-bottom: 10px;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .hidden {
            display: none;
        }
        .checkbox-group {
            max-height: 200px;
            overflow-y: auto;
            border: 1px solid #ddd;
            padding: 10px;
            border-radius: 5px;
        }
        .checkbox-item {
            margin-bottom: 5px;
        }
        .error {
            color: red;
            font-weight: bold;
        }
        .success {
            color: green;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Journal Article Manager</h1>
        
        <!-- User Login Section -->
        <h2>User Login</h2>
        <form action="index.jsp" method="post">
            <div class="form-group">
                <label for="userName">Enter your name:</label>
                <input type="text" id="userName" name="userName" value="<%= session.getAttribute("userName") != null ? session.getAttribute("userName") : "" %>" required>
            </div>
            <button type="submit" name="action" value="login">Login</button>
        </form>
        
        <%
            String userName = request.getParameter("userName");
            if (userName != null && !userName.trim().isEmpty()) {
                session.setAttribute("userName", userName);
            }
            userName = (String) session.getAttribute("userName");
        %>
        
        <% if (userName != null) { %>
            <p><strong>Welcome, <%= userName %>!</strong></p>
        <% } %>
    </div>

    <% if (userName != null) { %>
    <div class="container">
        <h2>Actions</h2>
        <button onclick="showMyArticle()">Show My Article</button>
        <button onclick="showAddArticle()">Add Article</button>
        <button onclick="showAllJournals()">Show All Journals</button>
    </div>

    <!-- All Projects Section -->
    <div id="allProjectsSection" class="container hidden">
        <h2>All Projects</h2>
        <div id="allProjectsList"></div>
    </div>

    <!-- My Projects Section -->
    <div id="myProjectsSection" class="container hidden">
        <h2>My Projects</h2>
        <div id="myProjectsList"></div>
    </div>

    <!-- Assign Developer Section -->
    <div id="assignDeveloperSection" class="container hidden">
        <h2>Add New Article</h2>
        <form action="addArticle.jsp" method="post">
            <input type="hidden" name="userName" value="<%= userName %>">
            <div class="form-group">
                <label for="articleSummary">Article Summary:</label>
                <input type="text" id="articleSummary" name="articleSummary" required>
            </div>
            <div class="form-group">
                <label for="journalName">Journal Name:</label>
                <input type="text" id="journalName" name="journalName" placeholder="Enter journal name" required>
                <small style="color: #666;">If the journal doesn't exist, it will be created automatically.</small>
            </div>
            <button type="submit">Add Article</button>
        </form>
    </div>

    <!-- All Developers Section -->
    <div id="allDevelopersSection" class="container hidden">
        <h2>All Developers</h2>
        <div id="allDevelopersList"></div>
    </div>
    <% } %>

    <script>
        let allDevelopers = [];
        
        function showAllProjects() {
            hideAllSections();
            document.getElementById('allProjectsSection').classList.remove('hidden');
            loadAllProjects();
        }
        
        function showMyArticle() {
            hideAllSections();
            document.getElementById('myProjectsSection').classList.remove('hidden');
            loadMyArticles();
        }
        
        function showAddArticle() {
            hideAllSections();
            document.getElementById('assignDeveloperSection').classList.remove('hidden');
            loadProjectCheckboxes();
        }
        
        function showAllJournals() {
            hideAllSections();
            document.getElementById('allDevelopersSection').classList.remove('hidden');
            loadAllJournals();
        }
        
        function hideAllSections() {
            document.getElementById('allProjectsSection').classList.add('hidden');
            document.getElementById('myProjectsSection').classList.add('hidden');
            document.getElementById('assignDeveloperSection').classList.add('hidden');
            document.getElementById('allDevelopersSection').classList.add('hidden');
        }
        
        function loadAllProjects() {
            fetch('getAllProjects.jsp')
                .then(response => response.text())
                .then(data => {
                    document.getElementById('allProjectsList').innerHTML = data;
                });
        }
        
        function loadMyArticles() {
            fetch('getMyArticles.jsp?userName=<%= userName %>')
                .then(response => response.text())
                .then(data => {
                    console.log(data);
                    document.getElementById('myProjectsList').innerHTML = data;
                });
        }
          function loadProjectCheckboxes() {
            fetch('getJournalCheckboxes.jsp')
                .then(response => response.text())
                .then(data => {
                    document.getElementById('projectCheckboxes').innerHTML = data;
                });
        }
        
        function loadAllJournals() {
            fetch('getAllJournals.jsp')
                .then(response => {
                    console.log('Response status:', response.status);
                    return response.text();
                })
                .then(text => {
                    console.log('Raw response:', text);
                    try {
                        const data = JSON.parse(text);
                        console.log('Parsed data:', data);
                        allDevelopers = data;
                        displayJournals(allDevelopers);
                    } catch (e) {
                        console.error('JSON parse error:', e);
                        document.getElementById('allDevelopersList').innerHTML = '<div class="error">Error parsing developer data: ' + e.message + '</div>';
                    }
                })                .catch(error => {
                    console.error('Fetch error:', error);
                    document.getElementById('allDevelopersList').innerHTML = '<div class="error">Error loading developers: ' + error.message + '</div>';
                });
        }
          function displayJournals(journals) {
            let html = '';
            if (journals && journals.length > 0) {
                journals.forEach(jou => {
        
                    const name = jou.name || 'Unknown';
                    const id = jou.id !== undefined ? jou.id : 'N/A';
                    

                    html += '<div class="developer-card">';
                    html += '<h4>Name: ' + name + '</h4>';
                    html += '<p><strong>ID:</strong> ' + id + '</p>';
                    html += '</div>';
                });
            } else {
                html = '<div class="error">No journals found</div>';
            }
            document.getElementById('allDevelopersList').innerHTML = html;
        }
        
    </script>
</body>
</html>
