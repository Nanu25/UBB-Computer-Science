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
$user = null;
$password = null;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['step'])) {
        // Step 1: Check username
        $username = trim($_POST['username'] ?? '');
        $password = trim($_POST['password'] ?? '');
        if (empty($username)) {
            $error = 'Please enter username';
        } else {
            $user = $db->fetchOne(
                "SELECT id, name, password FROM Person WHERE name = ? and password = ?", 
                [$username, $password]
            );
            
            if ($user) {
                $_SESSION['user'] = [
                    'id' => $user['id'],
                    'name' => $user['name']
                ];
                header('Location: index.php');
                exit;
            } else {
                $error = 'User not found';
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
    <title>Login</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="container">
        <div class="card" style="max-width: 400px; margin: 100px auto;">
            <h2>Login</h2>
            
            <?php if ($error): ?>
                <div class="message error"><?= htmlspecialchars($error) ?></div>
            <?php endif; ?>
            
                <!-- Step 1: Username -->
                <form method="POST">
                    <input type="hidden" name="step" value="1">
                    <div class="form-group">
                        <label>Username:</label>
                        <input type="text" name="username" value="<?= htmlspecialchars($_POST['username'] ?? '') ?>" 
                               placeholder="Enter your username" required>
                        <label>Password:</label>
                        <input type="password" name="password" value="<?= htmlspecialchars($_POST['password'] ?? '') ?>" 
                               placeholder="Enter your password" required>
                            </div>
                    <button type="submit">Login</button>
                </form>
            
        </div>
    </div>
</body>
</html>