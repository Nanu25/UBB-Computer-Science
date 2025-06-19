<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Movie Management System</title>
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
        .user-info {
            background-color: #e9ecef;
            padding: 15px;
            border-radius: 5px;
            margin-bottom: 20px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        .logout-btn {
            background-color: #dc3545;
            color: white;
            padding: 8px 15px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 14px;
        }
        .logout-btn:hover {
            background-color: #c82333;
        }
    </style>
</head>
<body>
    <%
        String userName = (String) session.getAttribute("userName");
        
        // Redirect to login if no user session
        if (userName == null) {
            response.sendRedirect("login.jsp");
            return;
        }
    %>

    <div class="container">
        <h1>Movie/Document Management System</h1>
        
        <div class="user-info">
            <div>
                <strong>Welcome, <%= userName %>!</strong>
            </div>
            <form method="post" action="logout.jsp" style="margin: 0;">
                <button type="submit" class="logout-btn">Logout</button>
            </form>
        </div>
    </div>

    <div class="container">
        <h2>Actions</h2>
        <button onclick="showAllCreations()">Show All Creations</button>
        <button onclick="showMyMovies()">Show My Movies</button>
        <button onclick="showAssignDeveloper()">Add Document</button>
        <button onclick="showAllDevelopers()">Document with the most Authors</button>
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
        <h2>Add Document</h2>
        <form action="addDocument.jsp" method="post">
            <div class="form-group">
                <label for="documentName">Document Name:</label>
                <input type="text" id="documentName" name="documentName" required>
                <label for="content">Content:</label>
                <input type="text" id="content" name="content" required>
                <input type ="hidden" name ="userName" value= <%= userName %> >
            </div>
            <button type="submit">Add Document</button>
        </form>
    </div>

    <!-- All Developers Section -->
    <div id="allDevelopersSection" class="container hidden">
        <h2>Document with the most authors</h2>
        <div id="allDevelopersList"></div>
    </div>

    <script>
        let documentMost = [];
        
        function showAllCreations() {
            hideAllSections();
            document.getElementById('allProjectsSection').classList.remove('hidden');
            loadAllCreations();
        }
        
        function showMyMovies() {
            hideAllSections();
            document.getElementById('myProjectsSection').classList.remove('hidden');
            loadMyMovies();
        }
        
        function showAssignDeveloper() {
            hideAllSections();
            document.getElementById('assignDeveloperSection').classList.remove('hidden');
            //loadProjectCheckboxes();
        }
        
        function showAllDevelopers() {
            hideAllSections();
            document.getElementById('allDevelopersSection').classList.remove('hidden');
            loadTheMostAuthorsDocument();
        }
        
        function hideAllSections() {
            document.getElementById('allProjectsSection').classList.add('hidden');
            document.getElementById('myProjectsSection').classList.add('hidden');
            document.getElementById('assignDeveloperSection').classList.add('hidden');
            document.getElementById('allDevelopersSection').classList.add('hidden');
        }
        
        function  loadAllCreations() {
            fetch('getAllCreations.jsp?userName=<%= userName %>')
                .then(response => response.text())
                .then(data => {
                    document.getElementById('allProjectsList').innerHTML = data;
                });
        }
        
        function loadMyMovies() {
            fetch('getMyMovies.jsp?userName=<%= userName %>')
                .then(response => response.text())
                .then(data => {
                    document.getElementById('myProjectsList').innerHTML = data;
                });
        }
        

        
        function loadTheMostAuthorsDocument() {
            fetch('getDocumentMostAuthors.jsp')
                .then(response => {
                    console.log('Response status:', response.status);
                    return response.text();
                })
                .then(text => {
                    console.log('Raw response:', text);
                    try {
                        const data = JSON.parse(text);
                        documentMost = data;
                        displayDocumentMostAuthors(documentMost);
                    } catch (e) {
                        console.error('JSON parse error:', e);
                        document.getElementById('allDevelopersList').innerHTML = '<div class="error">Error parsing developer data: ' + e.message + '</div>';
                    }
                })
                .catch(error => {
                    console.error('Fetch error:', error);
                    document.getElementById('allDevelopersList').innerHTML = '<div class="error">Error loading documentAuthors: ' + error.message + '</div>';
                });
        }
        
        function displayDocumentMostAuthors(documentAuthors) {
            console.log('Displaying documentAuthors:', documentAuthors);
            let html = '';
            if (documentAuthors && documentAuthors.length > 0) {
                documentAuthors.forEach(doc => {
                    
                    
                    html += '<div class="developer-card">';
                    html += '<h4>Most Popular Document: ' + doc.document + '</h4>';
                    html += '<p><strong>Number of Authors:</strong> ' + doc.authorCount + '</p>';
                    html += '<p><strong>Details:</strong> ' + doc.message + '</p>';
                
                    html += '</div>';
                });
            } else {
                html = '<div class="error">No documentAuthors found</div>';
            }
            document.getElementById('allDevelopersList').innerHTML = html;
        }
        
        function filterDevelopers() {
            const skill = document.getElementById('skillFilter').value.toLowerCase();
            if (skill === '') {
                displayDocumentMostAuthors(documentMost);
            } else {
                const filtered = documentMost.filter(doc => 
                    doc.skills.toLowerCase().includes(skill)
                );
                displayDocumentMostAuthors(filtered);
            }
        }

        function deleteMovie(movieName, userName) {
            if (confirm('Are you sure you want to delete the movie "' + movieName + " for the user " + userName + '" ?')) {
                fetch('deleteMovie.jsp', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded',
                    },
                    body: 'movieName=' + encodeURIComponent(movieName) + '&userName=' + encodeURIComponent(userName)

                })
                .then(response => response.text())
                .then(result => {
                    loadMyMovies(); // Reload the movies list
                })
                .catch(error => {
                    console.error('Error:', error);
                    alert('Error deleting movie');
                });
            }
        }

    </script>
</body>
</html>