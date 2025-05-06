<?php
session_start();
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $type = $_POST['type'];
    $severity = $_POST['severity'];
    $message = $_POST['message'];
    if (!empty($type) && !empty($severity) && !empty($message)) {
        include 'db.php';
        $stmt = $pdo->prepare("INSERT INTO log_reports (type, severity, date, user_id, message) VALUES (?, ?, NOW(), ?, ?)");
        $stmt->execute([$type, $severity, $_SESSION['user_id'], $message]);
        header("Location: logs.php");
        exit;
    } else {
        echo "Please fill in all fields.";
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Add Log</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Add Log Report</h1>
    <form method="post">
        <label for="type">Type:</label>
        <input type="text" id="type" name="type" required>
        <label for="severity">Severity:</label>
        <select id="severity" name="severity" required>
            <option value="debug">Debug</option>
            <option value="warning">Warning</option>
            <option value="notice">Notice</option>
            <option value="error">Error</option>
            <option value="critical">Critical</option>
        </select>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea>
        <input type="submit" value="Add Log">
    </form>
    <p><a href="index.php">Back to Home</a></p>
</body>
</html>