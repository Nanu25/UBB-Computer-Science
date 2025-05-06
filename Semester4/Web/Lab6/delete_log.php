<?php
session_start();
if (!isset($_SESSION['user_id'])) {
    echo json_encode(['success' => false, 'message' => 'Not logged in']);
    exit;
}
include 'db.php';
// Look for ID in either GET or POST
$log_id = $_REQUEST['id'] ?? 0;
if ($log_id > 0) {
    $stmt = $pdo->prepare("DELETE FROM log_reports WHERE log_id = ? AND user_id = ?");
    $stmt->execute([$log_id, $_SESSION['user_id']]);
    echo json_encode(['success' => $stmt->rowCount() > 0]);
} else {
    echo json_encode(['success' => false, 'message' => 'Invalid log ID']);
}
?>