<?php
session_start();
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];
    if (!empty($username) && !empty($password)) {
        include 'db.php';
        $hashed_password = password_hash($password, PASSWORD_DEFAULT);
        $stmt = $pdo->prepare("INSERT INTO users (username, password) VALUES (?, ?)");
        try {
            $stmt->execute([$username, $hashed_password]);
            
            // Get the newly created user's ID
            $user_id = $pdo->lastInsertId();
            
            // Log the user in automatically
            $_SESSION['user_id'] = $user_id;
            $_SESSION['username'] = $username;
            
            // Redirect to index instead of login
            header("Location: index.php");
            exit;
        } catch (PDOException $e) {
            error_log("Registration PDO Error: Code=" . $e->getCode() . " Message=" . $e->getMessage());
            if ($e->getCode() == '23000') {
                 if (strpos($e->getMessage(), '1062') !== false) {
                     echo "<br><b>Username already exists.</b>";
                 } else {
                     echo "<br><b>User Friendly Message: Database integrity error (not duplicate username).</b>";
                 }
            } else {
                 echo "<br><b>User Friendly Message: An unexpected database error occurred.</b>";
            }
        }
    } else {
        echo "Please fill in all fields.";
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Register</h1>
    <form method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required>
        <input type="submit" value="Register">
    </form>
    <p>Already have an account? <a href="login.php">Login here</a></p>
</body>
</html>