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
    strpos($_SERVER['HTTP_ACCEPT'], 'application/json') !== false;

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
    
    if (empty($username) || empty($password)) {
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
    } else {
        include 'db.php';
        
        // Check if username already exists
        $stmt = $pdo->prepare("SELECT * FROM users WHERE username = ?");
        $stmt->execute([$username]);
        if ($stmt->fetch()) {
            if ($is_api_request) {
                header('Content-Type: application/json');
                echo json_encode([
                    'success' => false,
                    'message' => 'Username already exists'
                ]);
                exit;
            } else {
                $error_message = "Username already exists.";
            }
        } else {
            // Insert new user
            $hashed_password = password_hash($password, PASSWORD_DEFAULT);
            $stmt = $pdo->prepare("INSERT INTO users (username, password) VALUES (?, ?)");
            if ($stmt->execute([$username, $hashed_password])) {
                $user_id = $pdo->lastInsertId();
                $_SESSION['user_id'] = $user_id;
                $_SESSION['username'] = $username;
                
                if ($is_api_request) {
                    header('Content-Type: application/json');
                    echo json_encode([
                        'success' => true,
                        'message' => 'Registration successful',
                        'user' => [
                            'user_id' => $user_id,
                            'username' => $username
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
                        'message' => 'Registration failed'
                    ]);
                    exit;
                } else {
                    $error_message = "Registration failed.";
                }
            }
        }
    }
}
?>