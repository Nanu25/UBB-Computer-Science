<?php
// Display all errors for debugging
ini_set('display_errors', 1);
error_reporting(E_ALL);

// Start output buffering to capture any unexpected output
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
    // Clean any output so far
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode(['success' => false, 'message' => 'Not logged in']);
    exit;
}

// Include database connection
try {
    include 'db.php';
} catch (Exception $e) {
    // Clean any output so far
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode(['success' => false, 'message' => 'Database connection error: ' . $e->getMessage()]);
    exit;
}

// Get filter parameters
$type = isset($_GET['type']) ? $_GET['type'] : '';
$severity = isset($_GET['severity']) ? $_GET['severity'] : '';
$view = isset($_GET['view']) ? $_GET['view'] : 'my';
$page = isset($_GET['page']) ? intval($_GET['page']) : 1;
$perPage = 5;
$offset = ($page - 1) * $perPage;

// Initialize where conditions array
$whereConditions = [];
$params = [];

// Add view filter (my/all)
if ($view === 'my' && isset($_SESSION['user_id'])) {
    $whereConditions[] = "log_reports.user_id = :user_id";  // Add table name prefix
    $params[':user_id'] = $_SESSION['user_id'];
}

// Add type filter if provided
if (!empty($type)) {
    $whereConditions[] = "type LIKE :type";
    $params[':type'] = "%$type%";
}

// Add severity filter if provided
if (!empty($severity)) {
    $whereConditions[] = "severity = :severity";
    $params[':severity'] = $severity;
}

// Build WHERE clause
$whereClause = '';
if (!empty($whereConditions)) {
    $whereClause = "WHERE " . implode(" AND ", $whereConditions);
}

try {
    // Count total matching logs - CHANGED TO log_reports
    $countSql = "SELECT COUNT(*) FROM log_reports $whereClause";
    $countStmt = $pdo->prepare($countSql);
    $countStmt->execute($params);
    $totalCount = $countStmt->fetchColumn();

    // Get logs for current page - CHANGED TO log_reports
    $sql = "SELECT log_reports.*, users.username FROM log_reports 
            LEFT JOIN users ON log_reports.user_id = users.user_id 
            $whereClause 
            ORDER BY date DESC 
            LIMIT $perPage OFFSET $offset";
    $stmt = $pdo->prepare($sql);
    $stmt->execute($params);
    $logs = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
    // Debug info - add this for troubleshooting
    $debug = [
        'session_user_id' => $_SESSION['user_id'] ?? 'not set',
        'view' => $view,
        'where_clause' => $whereClause,
        'params' => $params,
        'sql' => $sql,
        'count_sql' => $countSql,
        'total_count' => $totalCount
    ];
    
    // Discard any buffered output
    ob_end_clean();
    
    // Set JSON header
    header("Content-Type: application/json");
    
    // Return JSON response
    echo json_encode([
        'success' => true,
        'logs' => $logs,
        'total_count' => $totalCount,
        'debug' => $debug // Include debug info for troubleshooting
    ]);
    
} catch (Exception $e) {
    // Clean any output so far
    ob_end_clean();
    header("Content-Type: application/json");
    echo json_encode(['success' => false, 'message' => 'Database error: ' . $e->getMessage()]);
}
?>