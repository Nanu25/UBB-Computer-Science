// /**
//  * Frontend JavaScript for Software Developer Project Management System
//  * Handles all API communication and UI interactions
//  */

// class ProjectManagementApp {
//     constructor() {
//         this.baseURL = 'http://localhost/UserPropertyPHP/api';
//         this.currentUser = '';
//         this.allProperties = [];
        
//         //this.init();
//     }

//     init() {
//         this.setupEventListeners();
//     //    / this.showAllProperties(); // Show all projects by default
//     }

//     setupEventListeners() {
//         // Assign form submission
//         document.getElementById('assignForm').addEventListener('submit', (e) => {
//             e.preventDefault();
//             this.addProperty();
//         });

//         // Enter key for user input
//         document.getElementById('userName').addEventListener('keypress', (e) => {
//             if (e.key === 'Enter') {
//                 this.setUser();
//             }
//         });

//         // Enter key for skill filter
//         document.getElementById('skillFilter').addEventListener('keypress', (e) => {
//             if (e.key === 'Enter') {
//                 this.searchProperty();
//             }
//         });
//     }

//     // Utility Methods
//     showLoading(show = true) {
//         document.getElementById('loading').style.display = show ? 'flex' : 'none';
//     }

//     showMessage(message, type = 'success') {
//         const messagesContainer = document.getElementById('messages');
//         const messageDiv = document.createElement('div');
//         messageDiv.className = `message ${type}`;
//         messageDiv.textContent = message;
        
//         messagesContainer.appendChild(messageDiv);
        
//         // Auto remove after 3 seconds
//         setTimeout(() => {
//             if (messageDiv.parentNode) {
//                 messageDiv.parentNode.removeChild(messageDiv);
//             }
//         }, 3000);
//     }

//     hideAllSections() {
//         const sections = document.querySelectorAll('.content-section');
//         sections.forEach(section => section.style.display = 'none');
//     }

//     async apiCall(endpoint, method = 'GET', data = null) {
//         this.showLoading(true);
        
//         try {
//             const config = {
//                 method,
//                 headers: {
//                     'Content-Type': 'application/json',
//                 }
//             };

//             if (data) {
//                 config.body = JSON.stringify(data);
//             }

//             const response = await fetch(`${this.baseURL}/${endpoint}`, config);
//             const result = await response.json();

//             if (!response.ok) {
//                 throw new Error(result.error || 'API request failed');
//             }

//             return result;
//         } catch (error) {
//             this.showMessage(error.message, 'error');
//             throw error;
//         } finally {
//             this.showLoading(false);
//         }
//     }

//     // User Management
//     setUser() {
//         const userName = document.getElementById('userName').value.trim();
        
//         if (!userName) {
//             this.showMessage('Please enter your name', 'warning');
//             return;
//         }

//         this.currentUser = userName;
//         document.getElementById('currentUser').innerHTML = `
//             <strong>Current User:</strong> ${userName}
//         `;
        
//         // Enable user projects button
//         document.getElementById('userProjectsBtn').disabled = false;
        
//         this.showMessage(`Welcome, ${userName}!`);
//     }

//     // Project Management
//     async showAllProperties() {
//         this.hideAllSections();
//         document.getElementById('allProjectsSection').style.display = 'block';


//         try {
//             const result = await this.apiCall('properties');
//             this.allProperties = result.properties;
//             this.displayAllProperties(result.properties);

//             document.getElementById('totalProjectsCount').innerText = result.properties.length;
//         } catch (error) {
//             console.error('Error fetching projects:', error);
//         }
//     }

//     displayAllProperties(properties) {
//         const container = document.getElementById('allProjectsList');
        
//         if (!properties || properties.length === 0) {
//             container.innerHTML = '<p>No projects found.</p>';
//             return;
//         }

//         container.innerHTML = properties.map(property => `
//             <div class="project-item">
//                 <h3>${property.description}</h3>
//                 <p><strong>ID:</strong> ${property.id}</p>
//                 <p><strong>Address:</strong> ${property.address || 'No description'}</p>
//                 <td><button onclick="deleteProperty(${property.id})">Delete</button></td>

//             </div>
//         `).join('');
//     }

//     async deleteProperty(id) {
//         if (!confirm('Are you sure you want to delete this property?')) {
//             return;
//         }

//         try {
//             const result = await this.apiCall('delete-property', 'POST', {
//                 propertyId: id
//             });

//             this.showMessage('Property deleted successfully!');
            
//             // Refresh the properties list
//             this.showAllProperties();
            
//         } catch (error) {
//             console.error('Error deleting property:', error);
//             this.showMessage('Error deleting property: ' + error.message, 'error');
//         }
//     }

//     async showUserProjects() {
//         if (!this.currentUser) {
//             this.showMessage('Please set your name first', 'warning');
//             return;
//         }

//         this.hideAllSections();
//         document.getElementById('userProjectsSection').style.display = 'block';

//         try {
//             const result = await this.apiCall(`user-projects?user=${encodeURIComponent(this.currentUser)}`);
//             this.displayUserProjects(result.projects);
//         } catch (error) {
//             console.error('Error fetching user projects:', error);
//         }
//     }

//     displayUserProjects(projects) {
//         const container = document.getElementById('userProjectsList');
        
//         if (!projects || projects.length === 0) {
//             container.innerHTML = `<p>You are not a member of any projects.</p>`;
//             return;
//         }

//         container.innerHTML = projects.map(projectName => `
//             <div class="simple-project-item">
//                 ${projectName}
//             </div>
//         `).join('');
//     }

//     // Developer Management
//     async showDevelopers() {
//         this.hideAllSections();
//         document.getElementById('developersSection').style.display = 'block';

//         try {
//             const result = await this.apiCall('properties');
//             this.allProperties = result.properties;
//             this.displayDevelopers(this.allProperties);
//         } catch (error) {
//             console.error('Error fetching developers:', error);
//         }
//     }

//     displayDevelopers(developers) {
//         const container = document.getElementById('developersList');
        
//         if (!developers || developers.length === 0) {
//             container.innerHTML = '<p>No developers found.</p>';
//             return;
//         }

//         container.innerHTML = developers.map(developer => `
//             <div class="developer-item">
//                 <div class="developer-info">
//                     <h4>${developer.name}</h4>
//                     <p>Age: ${developer.age || 'Not specified'}</p>
//                 </div>
//                 <div class="developer-skills">
//                     <strong>Skills:</strong> ${developer.skills || 'No skills listed'}
//                 </div>
//             </div>
//         `).join('');
//     }

//     searchProperty() {
        
//         const searchDesc = document.getElementById('skillFilter').value.trim().toLowerCase();
        
//         if (!searchDesc) {
//             this.showMessage('Please enter a skill to filter by', 'warning');
//             return;
//         }
//         console.log(this.allProperties);
//         const filteredProp = this.allProperties.filter(property => {
//             const desc = (property.description || '').toLowerCase();
//             return desc.includes(searchDesc);
//         });

//         if (filteredProp.length === 0) {
//             this.showMessage(`No developers found with skill: ${searchDesc}`, 'warning');
//         } else {
//             this.showMessage(`Found ${filteredProp.length} developer(s) with skill: ${searchDesc}`);
//         }

//         this.displayAllProperties(filteredProp);
//     }

//     showAllDevelopers() {
//         document.getElementById('skillFilter').value = '';
//         this.displayDevelopers(this.allProperties);
//     }

//     // Assignment Management
//     showAssignSection() {
//         this.hideAllSections();
//         document.getElementById('assignSection').style.display = 'block';
        
//         // Clear previous results
//         document.getElementById('assignResults').innerHTML = '';
//     }

   
//     async addProperty() {
//         const propertyAddress = document.getElementById('propertyAddress').value.trim();
//         const propertyDescription = document.getElementById('propertyDescription').value.trim();
        
//         // Get user ID from session storage (logged-in user)
//         const storedUser = sessionStorage.getItem('currentUser');
        
//         if (!storedUser) {
//             this.showMessage('Please log in first', 'warning');
//             return;
//         }
//         console.log("am ajuns");
//         const user = JSON.parse(storedUser);
//         const userId = user.id;
        
//         if (!propertyAddress || !propertyDescription) {
//             this.showMessage('Please fill in all fields', 'warning');
//             return;
//         }

//         try {
//             const result = await this.apiCall('add-property', 'POST', {
//                 propertyAddr: propertyAddress,
//                 propertyDesc: propertyDescription, // Don't split into array, just send as string
//                 userId: userId
//             });

//             // Show success message
//             this.showMessage('Property added successfully!');
            
//             // Clear form
//             document.getElementById('assignForm').reset();
            
//             // Refresh the properties list
//             this.showAllProperties();
            
//         } catch (error) {
//             console.error('Error adding property:', error);
//             this.showMessage('Error adding property: ' + error.message, 'error');
//         }
//     }


//     displayAssignResults(results) {
//         const container = document.getElementById('assignResults');
        
//         if (!results || results.length === 0) {
//             container.innerHTML = '<p>No results to display.</p>';
//             return;
//         }

//         container.innerHTML = `
//             <h3>Assignment Results:</h3>
//             ${results.map(result => `
//                 <div class="result-item">
//                     ${result}
//                 </div>
//             `).join('')}
//         `;
//     }
// }

// // Global functions for button onclick events
// let app;

// window.addEventListener('DOMContentLoaded', () => {
//     app = new ProjectManagementApp();
//     app.setupEventListeners();
// });

// function setUser() {
//     app.setUser();
// }

// function showAllProperties() {
//     app.showAllProperties();
// }

// function showUserProjects() {
//     app.showUserProjects();
// }

// function showDevelopers() {
//     app.showDevelopers();
// }

// function showAssignSection() {
//     app.showAssignSection();
// }

// function searchProperty() {
//     app.searchProperty();
// }

// function showAllDevelopers() {
//     app.showAllDevelopers();
// }

// function deleteProperty(id) {
//     app.deleteProperty(id);
// }
