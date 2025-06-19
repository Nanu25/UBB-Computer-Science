/**
 * Frontend JavaScript for Software Developer Project Management System
 * Handles all API communication and UI interactions
 */

class ProjectManagementApp {
    constructor() {
        this.baseURL = 'http://localhost/WebDocPHP/api';
        this.currentUser = '';
        this.allDevelopers = [];
        this.init();
    }

    init() {
        this.setupEventListeners();
        this.showAllWebSites(); // Show all projects by default
    }

    setupEventListeners() {

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
    async showAllWebSites() {
        this.hideAllSections();
        document.getElementById('allWebSitesSection').style.display = 'block';

        try {
            const result = await this.apiCall('websites');
            const documents = await this.apiCall('documents');
            this.displayAllWebSites(result.websites, documents.documents);
        } catch (error) {
            console.error('Error fetching projects:', error);
        }
    }

displayAllWebSites(websites, documents) {
    const container = document.getElementById('allWebSitesList');

    if (!websites || websites.length === 0) {
        container.innerHTML = '<p>No projects found.</p>';
        return;
    }

    // Group documents by websiteId
    const websitesGroup = {};
    documents.forEach(doc => {
        if (!websitesGroup[doc.idWebSite]) {
            websitesGroup[doc.idWebSite] = [];
        }
        websitesGroup[doc.idWebSite].push(doc);
    });

    // Build the table
    let tableHTML = `
        <table border="1" cellspacing="0" cellpadding="8">
            <thead>
                <tr>
                    <th>Website ID</th>
                    <th>URL</th>
                    <th>Keywords</th>
                    <th>Actions</th>
                </tr>
            </thead>
            <tbody>
    `;

    websites.forEach(website => {
        const docs = websitesGroup[website.id] || [];
        // Flatten all keywords into one array
        const keywords = docs.flatMap(doc => [
            doc.keyword1, doc.keyword2, doc.keyword3, doc.keyword4, doc.keyword5
        ]).filter(Boolean); // Remove any undefined/null

        tableHTML += `
            <tr>
                <td>${website.id}</td>
                <td>${website.URL || 'No URL'}</td>
                <td>${keywords.join(', ') || 'No keywords'}</td>
                <td><button onclick="editKeyWords(${website.id})">Edit Keywords</button></td>
            </tr>
            `;
        });

        tableHTML += `</tbody></table>`;
        container.innerHTML = tableHTML;
    }

    async searchWebSites(event) {
        if (event) {
            event.preventDefault(); // Prevent form submission
        }
        
        const keywords = document.getElementById('KeyWords').value.trim();
        if (!keywords) {
            this.showMessage('Please enter keywords to search', 'warning');
            return;
        }

        // Check if exactly 3 words
        const wordsArray = keywords.split(' ').filter(word => word.trim() !== '');
        if (wordsArray.length !== 3) {
            this.showMessage('Please enter exactly 3 keywords separated by spaces', 'warning');
            return;
        }

        try {
            const result = await this.apiCall('search-websites', 'POST', {
                keywords: keywords
            });
            
            this.displaySearchResults(result.websites);
            
        } catch (error) {
            console.error("Error searching websites:", error);
        }
    }

    // Add this new method to display search results
    displaySearchResults(websites) {
        const container = document.getElementById('SearchResults');
        
        if (!websites || websites.length === 0) {
            container.innerHTML = '<p>No websites found with those 3 keywords.</p>';
            return;
        }

        container.innerHTML = `
            <h3>Search Results (${websites.length} websites found):</h3>
            <div class="search-results">
                ${websites.map(website => `
                    <div class="website-result">
                        <h4>Website ID: ${website.id}</h4>
                        <p><strong>URL:</strong> ${website.URL || 'No URL'}</p>
                    </div>
                `).join('')}
            </div>
        `;
    }

    // Replace the editKeyWords method with this corrected version:
    editKeyWords(websiteId) {
        // Find the keywords cell using a simple approach
        const rows = document.querySelectorAll('table tbody tr');
        let keywordsCell = null;
        
        rows.forEach(row => {
            const firstCell = row.querySelector('td:first-child');
            if (firstCell && firstCell.textContent.trim() === websiteId.toString()) {
                keywordsCell = row.querySelector('td:nth-child(3)');
            }
        });
        
        if (!keywordsCell) {
            this.showMessage('Could not find keywords cell', 'error');
            return;
        }
        
        const currentKeywords = keywordsCell.textContent.trim();
        
        // Replace cell content with input field
        keywordsCell.innerHTML = `
            <input type="text" 
                   id="edit-keywords-${websiteId}" 
                   value="${currentKeywords === 'No keywords' ? '' : currentKeywords}"
                   style="width: 100%; padding: 4px;">
            <br>
            <button onclick="saveKeywords(${websiteId}, '${currentKeywords}')" style="margin-top: 4px;">Save</button>
            <button onclick="cancelEdit(${websiteId}, '${currentKeywords}')" style="margin-top: 4px;">Cancel</button>
        `;
        
        // Focus on input
        const input = document.getElementById(`edit-keywords-${websiteId}`);
        if (input) {
            input.focus();
            
            // Add event listeners for Enter key and blur
            input.addEventListener('keypress', (event) => {
                if (event.key === 'Enter') {
                    this.saveKeywords(websiteId, currentKeywords);
                }
            });
            
            input.addEventListener('blur', () => {
                // Small delay to allow Save button click to register
                setTimeout(() => {
                    const stillExists = document.getElementById(`edit-keywords-${websiteId}`);
                    if (stillExists) {
                        this.saveKeywords(websiteId, currentKeywords);
                    }
                }, 100);
            });
        }
    }

// Add these new methods:
    async saveKeywords(websiteId, originalKeywords) {
        const input = document.getElementById(`edit-keywords-${websiteId}`);
        if (!input) return;
        
        const newKeywords = input.value.trim() || 'No keywords';
        
        try {
            // Save to database
            await this.apiCall('update-keywords', 'PUT', {
                websiteId: websiteId,
                keywords: newKeywords
            });
            
            // Update the display
            const rows = document.querySelectorAll('table tbody tr');
            rows.forEach(row => {
                const firstCell = row.querySelector('td:first-child');
                if (firstCell && firstCell.textContent.trim() === websiteId.toString()) {
                    const keywordsCell = row.querySelector('td:nth-child(3)');
                    keywordsCell.textContent = newKeywords;
                }
            });
            
            this.showMessage(`Keywords saved to database for website ${websiteId}`, 'success');
            
        } catch (error) {
            console.error('Error saving keywords:', error);
            this.showMessage('Failed to save keywords to database', 'error');
            
            // Restore original keywords on error
            const rows = document.querySelectorAll('table tbody tr');
            rows.forEach(row => {
                const firstCell = row.querySelector('td:first-child');
                if (firstCell && firstCell.textContent.trim() === websiteId.toString()) {
                    const keywordsCell = row.querySelector('td:nth-child(3)');
                    keywordsCell.textContent = originalKeywords;
                }
            });
        }
    }

    cancelEdit(websiteId, originalKeywords) {
        // Find the keywords cell and restore original content
        const rows = document.querySelectorAll('table tbody tr');
        rows.forEach(row => {
            const firstCell = row.querySelector('td:first-child');
            if (firstCell && firstCell.textContent.trim() === websiteId.toString()) {
                const keywordsCell = row.querySelector('td:nth-child(3)');
                keywordsCell.textContent = originalKeywords;
            }
        });
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

function showAllWebSites() {
    app.showAllWebSites();
}

function searchWebsites(event) {
    app.searchWebSites(event);
}

function editKeyWords(websiteId) {
    app.editKeyWords(websiteId);
}

function saveKeywords(websiteId, originalKeywords) {
    app.saveKeywords(websiteId, originalKeywords);
}

function cancelEdit(websiteId, originalKeywords) {
    app.cancelEdit(websiteId, originalKeywords);
}