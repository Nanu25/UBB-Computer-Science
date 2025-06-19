<?php
// Enable error reporting for debugging
ini_set('display_errors', 1);
error_reporting(E_ALL);

// Start output buffering
ob_start();

session_start();
// Allow CORS
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

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Get log ID from request
    $rawInput = file_get_contents('php://input');
    $contentType = isset($_SERVER['CONTENT_TYPE']) ? $_SERVER['CONTENT_TYPE'] : '';

    try {
        if (strpos($contentType, 'application/json') !== false) {
            $data = json_decode($rawInput, true);
            if (json_last_error() !== JSON_ERROR_NONE) {
                throw new Exception('Invalid JSON: ' . json_last_error_msg());
            }
            $id = $data['id'] ?? 0;
        } else {
            $id = $_POST['id'] ?? 0;
        }
        
        if ($id <= 0) {
            throw new Exception('Invalid log ID');
        }
        
        // Debug information
        $debug = [
            'id' => $id,
            'user_id' => $_SESSION['user_id'],
            'raw_input' => $rawInput,
            'content_type' => $contentType
        ];
        
        // Check if the log exists and user owns it
        $stmt = $pdo->prepare("SELECT user_id FROM log_reports WHERE log_id = ?");
        $stmt->execute([$id]);
        $log = $stmt->fetch();
        
        if (!$log) {
            throw new Exception('Log not found');
        }
        
        // Check ownership - user can only delete their own logs
        if ($log['user_id'] != $_SESSION['user_id']) {
            throw new Exception('You do not have permission to delete this log');
        }
        
        // Delete the log - using log_reports table, NOT logs
        $stmt = $pdo->prepare("DELETE FROM log_reports WHERE log_id = ?");
        if ($stmt->execute([$id])) {
            ob_end_clean();
            header("Content-Type: application/json");
            echo json_encode([
                'success' => true, 
                'message' => 'Log deleted successfully',
                'id' => $id
            ]);
        } else {
            throw new Exception('Database error while deleting log: ' . json_encode($stmt->errorInfo()));
        }
    } catch (Exception $e) {
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode([
            'success' => false, 
            'message' => $e->getMessage(),
            'debug' => $debug ?? null
        ]);
    }
} else {
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode(['success' => false, 'message' => 'Invalid request method']);
}
?>