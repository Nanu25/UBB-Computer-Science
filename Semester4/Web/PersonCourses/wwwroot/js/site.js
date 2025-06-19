// Please see documentation at https://learn.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

document.addEventListener('DOMContentLoaded', function() {
    // Handle checkboxes for project selection
    const checkboxes = document.querySelectorAll('input[name="SelectedProjectIds"]');
    if (checkboxes.length) {
        const newProjectInput = document.getElementById('NewProjectName');
        
        checkboxes.forEach(checkbox => {
            checkbox.addEventListener('change', function() {
                // If at least one checkbox is checked, the new project name is optional
                // Otherwise, it should be required
                const anyChecked = Array.from(checkboxes).some(cb => cb.checked);
                if (newProjectInput) {
                    if (!anyChecked) {
                        newProjectInput.setAttribute('required', 'required');
                    } else {
                        newProjectInput.removeAttribute('required');
                    }
                }
            });
        });
    }
    
    // Skills filter highlight effect
    const filterBtn = document.getElementById('filterBtn');
    if (filterBtn) {
        filterBtn.addEventListener('click', function() {
            const skillFilter = document.getElementById('skillFilter');
            const skill = skillFilter.value.trim().toLowerCase();
            
            if (skill !== '') {
                document.querySelectorAll('.developer-row:not([style*="none"])').forEach(row => {
                    const skillsCell = row.querySelector('td:nth-child(4)');
                    if (skillsCell) {
                        const text = skillsCell.textContent;
                        const highlightedText = text.replace(
                            new RegExp(skill, 'gi'), 
                            match => `<span class="bg-warning">${match}</span>`
                        );
                        skillsCell.innerHTML = highlightedText;
                    }
                });
            }
        });
    }
});
