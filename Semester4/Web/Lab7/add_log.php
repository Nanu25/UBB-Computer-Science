<?php
// Enable error reporting for debugging
ini_set('display_errors', 1);
error_reporting(E_ALL);

// Start output buffering to prevent unexpected output
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

// Check for POST request
if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode(['success' => false, 'message' => 'Invalid request method']);
    exit;
}

// Get data from the request
$rawInput = file_get_contents('php://input');
$contentType = isset($_SERVER['CONTENT_TYPE']) ? $_SERVER['CONTENT_TYPE'] : '';

try {
    if (strpos($contentType, 'application/json') !== false) {
        $data = json_decode($rawInput, true);
        if (json_last_error() !== JSON_ERROR_NONE) {
            throw new Exception('Invalid JSON: ' . json_last_error_msg());
        }
        $type = $data['type'] ?? '';
        $severity = $data['severity'] ?? '';
        $message = $data['message'] ?? '';
    } else {
        $type = $_POST['type'] ?? '';
        $severity = $_POST['severity'] ?? '';
        $message = $_POST['message'] ?? '';
    }

    // Validate data
    if (empty($type) || empty($message)) {
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode(['success' => false, 'message' => 'Type and message are required']);
        exit;
    }

    // Validate severity
    $validSeverities = ['debug', 'notice', 'warning', 'error', 'critical'];
    if (!in_array($severity, $validSeverities)) {
        $severity = 'notice'; // Default to notice if invalid
    }

    // Include database connection
    include 'db.php';

    // Debug info
    $debug_info = [
        'user_id' => $_SESSION['user_id'],
        'type' => $type,
        'severity' => $severity,
        'message' => $message
    ];

    // Insert log - FIXED TABLE NAME FROM 'logs' to 'log_reports'
    $stmt = $pdo->prepare("INSERT INTO log_reports (user_id, type, severity, message, date) VALUES (?, ?, ?, ?, NOW())");
    if ($stmt->execute([$_SESSION['user_id'], $type, $severity, $message])) {
        $logId = $pdo->lastInsertId();
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode([
            'success' => true,
            'message' => 'Log added successfully',
            'log_id' => $logId
        ]);
    } else {
        ob_end_clean();
        header("Content-Type: application/json");
        echo json_encode([
            'success' => false,
            'message' => 'Failed to add log: Database error',
            'debug_info' => $debug_info
        ]);
    }
} catch (Exception $e) {
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode([
        'success' => false,
        'message' => 'Error: ' . $e->getMessage(),
        'raw_input' => $rawInput
    ]);
}
?>