<?php
// Enable error reporting for debugging
ini_set('display_errors', 1);
error_reporting(E_ALL);

// Start output buffering
ob_start();

session_start();
// Allow CORS - this is critical
header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Credentials: true");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

// Handle preflight OPTIONS request
if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(200);
    exit();
}

// Check if user is logged in
if (!isset($_SESSION['user_id'])) {
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode(['success' => false, 'message' => 'Not logged in']);
    exit;
}

include 'db.php';

// GET request - fetch log details
if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $id = isset($_GET['id']) ? intval($_GET['id']) : 0;
    
    if ($id <= 0) {
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode(['success' => false, 'message' => 'Invalid log ID']);
        exit;
    }
    
    try {
        // Get log details
        $stmt = $pdo->prepare("SELECT * FROM log_reports WHERE log_id = ?");
        $stmt->execute([$id]);
        $log = $stmt->fetch();
        
        if (!$log) {
            ob_end_clean();
            header("Content-Type: application/json");
            echo json_encode(['success' => false, 'message' => 'Log not found']);
            exit;
        }
        
        // Only allow users to edit their own logs
        if ($log['user_id'] != $_SESSION['user_id']) {
            ob_end_clean();
            header("Content-Type: application/json");
            echo json_encode(['success' => false, 'message' => 'You do not have permission to edit this log']);
            exit;
        }
        
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode(['success' => true, 'log' => $log]);
    } catch (Exception $e) {
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode(['success' => false, 'message' => 'Database error: ' . $e->getMessage()]);
    }
}
// POST request - update log
else if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $id = isset($_GET['id']) ? intval($_GET['id']) : 0;
    $type = $_POST['type'] ?? '';
    $severity = $_POST['severity'] ?? '';
    $message = $_POST['message'] ?? '';
    
    if ($id <= 0 || empty($type) || empty($message)) {
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode(['success' => false, 'message' => 'Missing required fields']);
        exit;
    }
    
    try {
        // Check if log exists and user owns it
        $stmt = $pdo->prepare("SELECT user_id FROM log_reports WHERE log_id = ?");
        $stmt->execute([$id]);
        $log = $stmt->fetch();
        
        if (!$log) {
            ob_end_clean();
            header("Content-Type: application/json");
            echo json_encode(['success' => false, 'message' => 'Log not found']);
            exit;
        }
        
        // Check ownership
        if ($log['user_id'] != $_SESSION['user_id']) {
            ob_end_clean();
            header("Content-Type: application/json");
            echo json_encode(['success' => false, 'message' => 'You do not have permission to edit this log']);
            exit;
        }
        
        // Update log
        $stmt = $pdo->prepare("UPDATE log_reports SET type = ?, severity = ?, message = ? WHERE log_id = ?");
        if ($stmt->execute([$type, $severity, $message, $id])) {
            ob_end_clean();
            header("Content-Type: application/json");
            echo json_encode(['success' => true, 'message' => 'Log updated successfully']);
        } else {
            throw new Exception('Failed to update log: Database error');
        }
    } catch (Exception $e) {
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode(['success' => false, 'message' => $e->getMessage()]);
    }
} else {
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode(['success' => false, 'message' => 'Invalid request method']);
}
?>