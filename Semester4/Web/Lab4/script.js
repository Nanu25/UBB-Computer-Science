document.addEventListener('DOMContentLoaded', function() {
    let table = document.querySelector('table');
    let thead = table.querySelector('thead');

    let currentSortColumn = -1; 
    let currentSortDirection = 'asc'; 
    
    function sortColumn(columnIndex) {
        if (currentSortColumn === columnIndex) {
            currentSortDirection = currentSortDirection === 'asc' ? 'desc' : 'asc';
        } else {
            currentSortColumn = columnIndex;
            currentSortDirection = 'asc';
        }

        let tbody = table.querySelector('tbody');
        let columnValues = Array.from(tbody.querySelectorAll(`tr td:nth-child(${columnIndex + 1})`));
        
        // Extract and sort the values
        let sortedValues = columnValues.map(cell => cell.textContent)
            .sort((a, b) => {
                // Special handling for age column (numeric sort)
                if (columnIndex === 1) {
                    if (currentSortDirection === 'asc') {
                        return parseInt(a) - parseInt(b);
                    } else {
                        return parseInt(b) - parseInt(a);
                    }
                } else {
                    if (currentSortDirection === 'asc') {
                        return a.localeCompare(b);
                    } else {
                        return b.localeCompare(a);
                    }
                }
            });
        
        // Replace values in the column
        columnValues.forEach((cell, index) => {
            cell.textContent = sortedValues[index];
        });
    }
    
    thead.addEventListener('click', function(event) {
        let th = event.target;
        if (th.tagName === 'TH') {
            sortColumn(th.cellIndex);
        }
    });

    function deleteTable() {
        table.parentNode.removeChild(table);
        // table.deleteTHead();
    }
    
    document.addEventListener('keydown', function(event) {
        if (document.activeElement.tagName === 'INPUT') {
            return;
        }
        
        switch(event.key.toLowerCase()) {
            case 'n':
                sortColumn(0); 
                break;
            case 'a':
                sortColumn(1); 
                break;
            case 'c':
                sortColumn(2);
                break;
            case 'd':
                deleteTable();
                break;
        }
    });

    let addButton = document.getElementById('addRowButton');
    let nameInput = document.getElementById('nameInput');
    let ageInput = document.getElementById('ageInput');
    let cityInput = document.getElementById('cityInput');
    
    addButton.addEventListener('click', function() {
        let name = nameInput.value.trim();
        let age = ageInput.value.trim();
        let city = cityInput.value.trim();
        
        if (name === '' || age === '' || city === '') {
            alert('Please fill all fields');
            return;
        }
        
        let tbody = table.querySelector('tbody');
        let newRow = document.createElement('tr');
        
        let nameCell = document.createElement('td');
        nameCell.textContent = name;
        
        let ageCell = document.createElement('td');
        ageCell.textContent = age;
        
        let cityCell = document.createElement('td');
        cityCell.textContent = city;
        
        newRow.appendChild(nameCell);
        newRow.appendChild(ageCell);
        newRow.appendChild(cityCell);
        
        tbody.appendChild(newRow);
        
        nameInput.value = '';
        ageInput.value = '';
        cityInput.value = '';
        
        nameInput.focus();
    });
});