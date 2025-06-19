<?php
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

// Check if this is an API request
$is_api_request = isset($_SERVER['HTTP_ACCEPT']) && 
    (strpos($_SERVER['HTTP_ACCEPT'], 'application/json') !== false || 
     isset($_GET['check_status']));

// Check if this is a status check request
if (isset($_GET['check_status'])) {
    header('Content-Type: application/json');
    if (isset($_SESSION['user_id'])) {
        echo json_encode([
            'success' => true,
            'user' => [
                'user_id' => $_SESSION['user_id'],
                'username' => $_SESSION['username']
            ]
        ]);
    } else {
        echo json_encode(['success' => false]);
    }
    exit;
}

if (isset($_SESSION['user_id'])) {
    if ($is_api_request) {
        header('Content-Type: application/json');
        echo json_encode([
            'success' => true,
            'redirectTo' => 'index.php',
            'user' => [
                'user_id' => $_SESSION['user_id'],
                'username' => $_SESSION['username']
            ]
        ]);
        exit;
    } else {
        header("Location: index.php");
        exit;
    }
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Get JSON data if content type is application/json
    if (strpos($_SERVER['CONTENT_TYPE'] ?? '', 'application/json') !== false) {
        $data = json_decode(file_get_contents('php://input'), true);
        $username = $data['username'] ?? '';
        $password = $data['password'] ?? '';
    } else {
        $username = $_POST['username'] ?? '';
        $password = $_POST['password'] ?? '';
    }
    
    if (!empty($username) && !empty($password)) {
        include 'db.php';
        $stmt = $pdo->prepare("SELECT * FROM users WHERE username = ?");
        $stmt->execute([$username]);
        $user = $stmt->fetch();
        
        if ($user && password_verify($password, $user['password'])) {
            $_SESSION['user_id'] = $user['user_id'];
            $_SESSION['username'] = $user['username'];
            
            if ($is_api_request) {
                header('Content-Type: application/json');
                echo json_encode([
                    'success' => true,
                    'message' => 'Login successful',
                    'user' => [
                        'user_id' => $user['user_id'],
                        'username' => $user['username']
                    ]
                ]);
                exit;
            } else {
                header("Location: index.php");
                exit;
            }
        } else {
            if ($is_api_request) {
                header('Content-Type: application/json');
                echo json_encode([
                    'success' => false,
                    'message' => 'Invalid username or password'
                ]);
                exit;
            } else {
                $error_message = "Invalid username or password.";
            }
        }
    } else {
        if ($is_api_request) {
            header('Content-Type: application/json');
            echo json_encode([
                'success' => false,
                'message' => 'Please fill in all fields'
            ]);
            exit;
        } else {
            $error_message = "Please fill in all fields.";
        }
    }
}

// Only reach here for direct browser access, show HTML form
?>