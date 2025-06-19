<?php
session_start();

// Redirect if already logged in
if (isset($_SESSION['user'])) {
    header('Location: index.php');
    exit;
}

require_once 'config/database.php';
$db = new Database();

$error = '';
$step = 1;
$user = null;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['step']) && $_POST['step'] == '1') {
        // Step 1: Check username
        $username = trim($_POST['username'] ?? '');
        
        if (empty($username)) {
            $error = 'Please enter username';
        } else {
            $user = $db->fetchOne(
                "SELECT id, name, secretQuestion FROM User WHERE name = ?", 
                [$username]
            );
            
            if ($user) {
                $step = 2;
            } else {
                $error = 'User not found';
            }
        }
    } elseif (isset($_POST['step']) && $_POST['step'] == '2') {
        // Step 2: Verify answer
        $userId = $_POST['userId'] ?? '';
        $answer = trim($_POST['answer'] ?? '');
        
        if (empty($answer) || empty($userId)) {
            $error = 'Please enter answer';
            $step = 2;
            // Get user data again for step 2
            $user = $db->fetchOne("SELECT id, name, secretQuestion FROM User WHERE id = ?", [$userId]);
        } else {
            $userCheck = $db->fetchOne("SELECT * FROM User WHERE id = ?", [$userId]);
            
            if ($userCheck && strtolower(trim($userCheck['secretAnswer'])) === strtolower(trim($answer))) {
                // Login successful
                $_SESSION['user'] = [
                    'id' => $userCheck['id'],
                    'name' => $userCheck['name']
                ];
                header('Location: index.php');
                exit;
            } else {
                $error = 'Incorrect answer';
                $step = 2;
                $user = $db->fetchOne("SELECT id, name, secretQuestion FROM User WHERE id = ?", [$userId]);
            }
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login - User Property Management</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="container">
        <div class="card" style="max-width: 400px; margin: 100px auto;">
            <h2>Login</h2>
            
            <?php if ($error): ?>
                <div class="message error"><?= htmlspecialchars($error) ?></div>
            <?php endif; ?>
            
            <?php if ($step === 1): ?>
                <!-- Step 1: Username -->
                <form method="POST">
                    <input type="hidden" name="step" value="1">
                    <div class="form-group">
                        <label>Username:</label>
                        <input type="text" name="username" value="<?= htmlspecialchars($_POST['username'] ?? '') ?>" 
                               placeholder="Enter your username" required>
                    </div>
                    <button type="submit">Next</button>
                </form>
            <?php else: ?>
                <!-- Step 2: Secret Question -->
                <form method="POST">
                    <input type="hidden" name="step" value="2">
                    <input type="hidden" name="userId" value="<?= $user['id'] ?>">
                    <div class="form-group">
                        <label>User:</label>
                        <p><strong><?= htmlspecialchars($user['name']) ?></strong></p>
                    </div>
                    <div class="form-group">
                        <label>Secret Question:</label>
                        <p><strong><?= htmlspecialchars($user['secretQuestion']) ?></strong></p>
                    </div>
                    <div class="form-group">
                        <label>Answer:</label>
                        <input type="text" name="answer" placeholder="Enter your answer" required>
                    </div>
                    <button type="submit">Login</button>
                    <a href="login.php" class="btn btn-secondary">Back</a>
                </form>
            <?php endif; ?>
        </div>
    </div>
</body>
</html>