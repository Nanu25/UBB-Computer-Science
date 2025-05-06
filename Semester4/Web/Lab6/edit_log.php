<?php
session_start();    //pentru a folosi variabilele de sesiune
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}
include 'db.php';
$log_id = $_GET['id'] ?? 0;
if ($log_id <= 0) {
    header("Location: logs.php");
    exit;
}
$stmt = $pdo->prepare("SELECT * FROM log_reports WHERE log_id = ? AND user_id = ?");
$stmt->execute([$log_id, $_SESSION['user_id']]);
$log = $stmt->fetch();
if (!$log) {
    echo "Log not found or not authorized.";
    exit;
}
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $type = $_POST['type'];
    $severity = $_POST['severity'];
    $message = $_POST['message'];
    if (!empty($type) && !empty($severity) && !empty($message)) {
        $stmt = $pdo->prepare("UPDATE log_reports SET type = ?, severity = ?, message = ? WHERE log_id = ? AND user_id = ?");
        $stmt->execute([$type, $severity, $message, $log_id, $_SESSION['user_id']]);
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
    <title>Edit Log</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Edit Log Report</h1>
    <form method="post">
        <label for="type">Type:</label>
        <input type="text" id="type" name="type" value="<?php echo htmlspecialchars($log['type']); ?>" required>
        <label for="severity">Severity:</label>
        <select id="severity" name="severity" required>
            <?php
            $severities = ['debug', 'warning', 'notice', 'error', 'critical'];
            foreach ($severities as $sev) {
                $selected = $sev == $log['severity'] ? 'selected' : '';
                echo "<option value=\"$sev\" $selected>$sev</option>";
            }
            ?>
        </select>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required><?php echo htmlspecialchars($log['message']); ?></textarea>
        <input type="submit" value="Update Log">
    </form>
    <p><a href="logs.php">Back to Logs</a></p>
</body>
</html>