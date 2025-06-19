/**
 * Frontend JavaScript for Software Developer Project Management System
 * Handles all API communication and UI interactions
 */

class ProjectManagementApp {
    constructor() {
        this.baseURL = 'http://localhost/ExamPHP/api';
        this.currentUser = '';
        this.allDevelopers = [];
        this.init();
    }

    init() {
        this.setupEventListeners();
        this.showAllProjects(); // Show all projects by default
    }

    setupEventListeners() {
        // Assign form submission
        document.getElementById('assignForm').addEventListener('submit', (e) => {
            e.preventDefault();
            this.assignDeveloper();
        });

        // Enter key for user input
        document.getElementById('userName').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.setUser();
            }
        });

        // Enter key for skill filter
        document.getElementById('skillFilter').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.filterDevelopersBySkill();
            }
        });
    }

    // Utility Methods
    showLoading(show = true) {
        document.getElementById('loading').style.display = show ? 'flex' : 'none';
    }

    showMessage(message, type = 'success') {
        const messagesContainer = document.getElementById('messages');
        const messageDiv = document.createElement('div');
        messageDiv.className = `message ${type}`;
        messageDiv.textContent = message;
        
        messagesContainer.appendChild(messageDiv);
        
        // Auto remove after 3 seconds
        setTimeout(() => {
            if (messageDiv.parentNode) {
                messageDiv.parentNode.removeChild(messageDiv);
            }
        }, 3000);
    }

    hideAllSections() {
        const sections = document.querySelectorAll('.content-section');
        sections.forEach(section => section.style.display = 'none');
    }

    async apiCall(endpoint, method = 'GET', data = null) {
        this.showLoading(true);
        
        try {
            const config = {
                method,
                headers: {
                    'Content-Type': 'application/json',
                }
            };

            if (data) {
                config.body = JSON.stringify(data);
            }

            const response = await fetch(`${this.baseURL}/${endpoint}`, config);
            const result = await response.json();

            if (!response.ok) {
                throw new Error(result.error || 'API request failed');
            }

            return result;
        } catch (error) {
            this.showMessage(error.message, 'error');
            throw error;
        } finally {
            this.showLoading(false);
        }
    }

    // User Management
    setUser() {
        const userName = document.getElementById('userName').value.trim();
        
        if (!userName) {
            this.showMessage('Please enter your name', 'warning');
            return;
        }

        this.currentUser = userName;
        document.getElementById('currentUser').innerHTML = `
            <strong>Current User:</strong> ${userName}
        `;
        
        // Enable user projects button
        document.getElementById('userProjectsBtn').disabled = false;
        
        this.showMessage(`Welcome, ${userName}!`);
    }

    // Project Management
    async showAllProjects() {
        this.hideAllSections();
        document.getElementById('allProjectsSection').style.display = 'block';


        try {
            const result = await this.apiCall('projects');
            this.displayAllProjects(result.projects);
            document.getElementById('totalProjectsCount').innerText = result.projects.length;
        } catch (error) {
            console.error('Error fetching projects:', error);
        }
    }

    displayAllProjects(projects) {
        const container = document.getElementById('allProjectsList');
        
        if (!projects || projects.length === 0) {
            container.innerHTML = '<p>No projects found.</p>';
            return;
        }

        container.innerHTML = projects.map(project => `
            <div class="project-item">
                <h3>${project.name}</h3>
                <p><strong>ID:</strong> ${project.id}</p>
                <p><strong>Description:</strong> ${project.description || 'No description'}</p>
                <p><strong>Project Manager:</strong> ${project.manager_name || 'Not assigned'}</p>
                <div class="members">
                    <strong>Members:</strong> ${project.members || 'No members assigned'}
                </div>
            </div>
        `).join('');
    }

    async showUserProjects() {
        if (!this.currentUser) {
            this.showMessage('Please set your name first', 'warning');
            return;
        }

        this.hideAllSections();
        document.getElementById('userProjectsSection').style.display = 'block';

        try {
            const result = await this.apiCall(`user-projects?user=${encodeURIComponent(this.currentUser)}`);
            this.displayUserProjects(result.projects);
        } catch (error) {
            console.error('Error fetching user projects:', error);
        }
    }

    displayUserProjects(projects) {
        const container = document.getElementById('userProjectsList');
        
        if (!projects || projects.length === 0) {
            container.innerHTML = `<p>You are not a member of any projects.</p>`;
            return;
        }

        container.innerHTML = projects.map(projectName => `
            <div class="simple-project-item">
                ${projectName}
            </div>
        `).join('');
    }

    // Developer Management
    async showDevelopers() {
        this.hideAllSections();
        document.getElementById('developersSection').style.display = 'block';

        try {
            const result = await this.apiCall('developers');
            this.allDevelopers = result.developers;
            this.displayDevelopers(this.allDevelopers);
        } catch (error) {
            console.error('Error fetching developers:', error);
        }
    }

    displayDevelopers(developers) {
        const container = document.getElementById('developersList');
        
        if (!developers || developers.length === 0) {
            container.innerHTML = '<p>No developers found.</p>';
            return;
        }

        container.innerHTML = developers.map(developer => `
            <div class="developer-item">
                <div class="developer-info">
                    <h4>${developer.name}</h4>
                    <p>Age: ${developer.age || 'Not specified'}</p>
                </div>
                <div class="developer-skills">
                    <strong>Skills:</strong> ${developer.skills || 'No skills listed'}
                </div>
            </div>
        `).join('');
    }

    filterDevelopersBySkill() {
        const skill = document.getElementById('skillFilter').value.trim().toLowerCase();
        
        if (!skill) {
            this.showMessage('Please enter a skill to filter by', 'warning');
            return;
        }

        const filteredDevelopers = this.allDevelopers.filter(developer => {
            const skills = (developer.skills || '').toLowerCase();
            return skills.includes(skill);
        });

        if (filteredDevelopers.length === 0) {
            this.showMessage(`No developers found with skill: ${skill}`, 'warning');
        } else {
            this.showMessage(`Found ${filteredDevelopers.length} developer(s) with skill: ${skill}`);
        }

        this.displayDevelopers(filteredDevelopers);
    }

    showAllDevelopers() {
        document.getElementById('skillFilter').value = '';
        this.displayDevelopers(this.allDevelopers);
    }

    // Assignment Management
    showAssignSection() {
        this.hideAllSections();
        document.getElementById('assignSection').style.display = 'block';
        
        // Clear previous results
        document.getElementById('assignResults').innerHTML = '';
    }

    async assignDeveloper() {
        const developerName = document.getElementById('developerName').value.trim();
        const projectNamesInput = document.getElementById('projectNames').value.trim();

        if (!developerName || !projectNamesInput) {
            this.showMessage('Please fill in all fields', 'warning');
            return;
        }

        // Parse project names (split by comma and trim)
        const projectNames = projectNamesInput.split(',').map(name => name.trim()).filter(name => name);

        if (projectNames.length === 0) {
            this.showMessage('Please enter at least one project name', 'warning');
            return;
        }

        try {
            const result = await this.apiCall('assign-developer', 'POST', {
                developer: developerName,
                projects: projectNames
            });

            this.displayAssignResults(result.results);
            this.showMessage('Assignment completed successfully!');
            
            // Clear form
            document.getElementById('assignForm').reset();
            
        } catch (error) {
            console.error('Error assigning developer:', error);
        }
    }

    displayAssignResults(results) {
        const container = document.getElementById('assignResults');
        
        if (!results || results.length === 0) {
            container.innerHTML = '<p>No results to display.</p>';
            return;
        }

        container.innerHTML = `
            <h3>Assignment Results:</h3>
            ${results.map(result => `
                <div class="result-item">
                    ${result}
                </div>
            `).join('')}
        `;
    }
}

// Global functions for button onclick events
let app;

window.addEventListener('DOMContentLoaded', () => {
    app = new ProjectManagementApp();
});

function setUser() {
    app.setUser();
}

function showAllProjects() {
    app.showAllProjects();
}

function showUserProjects() {
    app.showUserProjects();
}

function showDevelopers() {
    app.showDevelopers();
}

function showAssignSection() {
    app.showAssignSection();
}

function filterDevelopersBySkill() {
    app.filterDevelopersBySkill();
}

function showAllDevelopers() {
    app.showAllDevelopers();
}
