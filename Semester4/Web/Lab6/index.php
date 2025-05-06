<?php
session_start();
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}
include 'db.php';
$stmt = $pdo->prepare("SELECT COUNT(*) FROM log_reports WHERE user_id = ?");
$stmt->execute([$_SESSION['user_id']]);
$count = $stmt->fetchColumn();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Welcome, <?php echo htmlspecialchars($_SESSION['username']); ?></h1>
    <p>You have created <?php echo $count; ?> logs.</p>
    <nav>
        <a href="logs.php">View Logs</a> |
        <a href="add_log.php">Add Log</a> |
        <a href="logout.php">Logout</a>
    </nav>
</body>
</html>