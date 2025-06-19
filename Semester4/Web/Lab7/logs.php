<!-- 
 <?php
session_start();
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Log Reports</title>
    <link rel="stylesheet" href="style.css">
    <script>
        let currentPage = 1;
        function loadLogs() {
            const type = document.getElementById('type').value;
            const severity = document.getElementById('severity').value;
            const view = document.querySelector('input[name="view"]:checked').value;
            fetch(`get_logs.php?type=${type}&severity=${severity}&view=${view}&page=${currentPage}`)
                .then(response => response.json())
                .then(data => {
                    const tbody = document.querySelector('#logs-table tbody');
                    tbody.innerHTML = '';
                    data.logs.forEach(log => {
                        const tr = document.createElement('tr');
                        tr.innerHTML = `
                            <td>${log.log_id}</td>
                            <td>${log.type}</td>
                            <td>${log.severity}</td>
                            <td>${log.date}</td>
                            <td>${log.message}</td>
                            <td>${
                                log.user_id == <?php echo $_SESSION['user_id']; ?> ?
                                `<a href="edit_log.php?id=${log.log_id}">Edit</a> <button class="delete" data-id="${log.log_id}">Delete</button>` :
                                ''
                            }</td>
                        `;
                        tbody.appendChild(tr);
                    });
                    const totalPages = Math.ceil(data.total_count / 4);
                    document.getElementById('page-info').textContent = `Page ${currentPage} of ${totalPages}`;
                    document.getElementById('prev').disabled = currentPage == 1;
                    document.getElementById('next').disabled = currentPage == totalPages;
                    addDeleteListeners();
                });
        }
        function addDeleteListeners() {
            document.querySelectorAll('.delete').forEach(button => {
                button.addEventListener('click', function() {
                    if (confirm('Are you sure you want to delete this log?')) {
                        const logId = this.dataset.id;
                        fetch(`delete_log.php?id=${logId}`, { method: 'POST' })
                            .then(response => response.json())
                            .then(data => {
                                if (data.success) {
                                    this.closest('tr').remove();
                                } else {
                                    alert('Error deleting log');
                                }
                            });
                    }
                });
            });
        }
        document.addEventListener('DOMContentLoaded', () => {
            loadLogs();
            document.getElementById('type').addEventListener('input', () => { currentPage = 1; loadLogs(); });
            document.getElementById('severity').addEventListener('change', () => { currentPage = 1; loadLogs(); });
            document.querySelectorAll('input[name="view"]').forEach(radio => {
                radio.addEventListener('change', () => { currentPage = 1; loadLogs(); });
            });
            document.getElementById('prev').addEventListener('click', () => {
                if (currentPage > 1) {
                    currentPage--;
                    loadLogs();
                }
            });
            document.getElementById('next').addEventListener('click', () => {
                currentPage++;
                loadLogs();
            });
        });
    </script>
</head>
<body>
    <h1>Log Reports</h1>
    <label for="type">Type:</label>
    <input type="text" id="type" name="type">
    <label for="severity">Severity:</label>
    <select id="severity" name="severity">
        <option value="">All</option>
        <option value="debug">Debug</option>
        <option value="warning">Warning</option>
        <option value="notice">Notice</option>
        <option value="error">Error</option>
        <option value="critical">Critical</option>
    </select>
    <input type="radio" id="my-logs" name="view" value="my" checked> My Logs
    <input type="radio" id="all-logs" name="view" value="all"> All Logs
    <table id="logs-table">
        <thead>
            <tr>
                <th>ID</th>
                <th>Type</th>
                <th>Severity</th>
                <th>Date</th>
                <th>Message</th>
                <th>Actions</th>
            </tr>
        </thead>
        <tbody></tbody>
    </table>
    <div id="pagination">
        <button id="prev">Previous</button>
        <span id="page-info">Page 1</span>
        <button id="next">Next</button>
    </div>
    <p><a href="index.php">Back to Home</a></p>
</body>
</html> -->