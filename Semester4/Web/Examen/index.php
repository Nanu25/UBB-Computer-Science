<?php
session_start();

// Check if user is logged in
if (!isset($_SESSION['user'])) {
    header('Location: login.php');
    exit;
}

require_once 'config/database.php';
$db = new Database();
$message = '';
// Initialize cart in session if not exists
if (!isset($_SESSION['cart'])) {
    $_SESSION['cart'] = [];
}

// Handle form submissions
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $userId = $_SESSION['user']['id'];
    
    if (isset($_POST['action'])) {
        switch ($_POST['action']) {
            case 'add_order':
                $productId = trim($_POST['productId'] ?? '');
                if ($productId) {
                    $productId = trim($_POST['productId'] ?? '');
                    $_SESSION['cart'][] = $productId;
                    $message = "Product added to cart successfully!";
                }
                break;
                
            case 'order_confirmation':
                if (!empty($_SESSION['cart'])) {
                    $db->query("INSERT INTO Order1 (userId, totalPrice) VALUES (?, ?)", [$userId, 0]);
                    $orderId = $db->lastInsertId();
                    
                    $total = 0;
                    $categories = [];
                    foreach ($_SESSION['cart'] as $productId) {
                        $db->query("INSERT INTO OrderItem (orderId, productId) VALUES (?, ?)", 
                                  [$orderId, $productId]);
                        
                        $product = $db->fetchOne("SELECT price, name FROM Product WHERE id = ?", [$productId]);
                        if ($product) {
                            $total += $product['price'];
                            
                            $nameParts = explode('-', $product['name'], 2);                            
                            $category = trim($nameParts[0]);
                            $categories[] = $category;
                            
                        }
                    }
                    
                    if (count($_SESSION['cart']) >= 3) {
                        $total = 0.9 * $total;
                    }

                    $nr = 0;
                    foreach($categories as $cat) {
                        $nr = 0;
                        for($i = 0; $i < count($categories); $i++) {
                            if($cat == $categories[$i])
                                $nr += 1;
                        }
                        if($nr >= 2) {
                            $total = 0.95 * $total;
                            break;
                        }
                    }
                    
                    $db->query("UPDATE Order1 SET totalPrice = ? WHERE id = ?", [$total, $orderId]);
                    
                    $_SESSION['cart'] = [];
                    $message = "Total Price=  " . $total;
                } else {
                    $message = "No items in cart to confirm.";
                }
                break;
                
            case 'clear_cart':
                $_SESSION['cart'] = [];
                $message = "Cart cleared successfully!";
                break;
        }
    }
}

$view = $_GET['view'] ?? 'all_products';

switch ($view) {
    case 'all_products':
        $products = $db->fetchAll("SELECT * FROM Product ORDER BY id DESC");
        break;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Channel Management </title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>Examen</h1>
            <div class="user-info">
                Welcome, <?= htmlspecialchars($_SESSION['user']['username']) ?>! 
                <a href="logout.php">Logout</a>
            </div>
        </header>

        <!-- Navigation -->
        <nav class="navigation">
            <a href="?view=all_products" class="nav-btn <?= $view === 'all_products' ? 'active' : '' ?>">
                All Products
            </a>
            
            <a href="?view=order_confirmation" class="nav-btn <?= $view === 'order_confirmation' ? 'active' : '' ?>">
                OrderConfirmation
            </a> 
        </nav>

        <?php if ($message): ?>
            <div class="message <?= strpos($message, 'Error') === 0 ? 'error' : 'success' ?>">
                <?= htmlspecialchars($message) ?>
            </div>
        <?php endif; ?>

        <!-- All Properties View -->
        <?php if ($view === 'all_products'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>All Products</h2>
                    
                    <div class="properties-list">
                        <?php if (empty($products)): ?>
                            <p>No properties found.</p>
                        <?php else: ?>
                            <?php foreach ($products as $product): ?>
                                <div class="project-item">
                                    <h3><strong>Name: </strong><?= htmlspecialchars($product['name']) ?></h3>
                                    <p><strong>ID:</strong> <?= $product['id'] ?></p>
                                    <p><strong>Price:</strong> <?= htmlspecialchars($product['price']) ?></p>

                                    <form method="POST" style="display: inline;" 
                                          onsubmit="return confirm('Are you sure you want to add this to the command?')">
                                        <input type="hidden" name="action" value="add_order">
                                        <input type="hidden" name="productId" value="<?= $product['id'] ?>">
                                        <input type="hidden" name="userId" value="<?= $_SESSION['user']['id'] ?>">
                                        <button type="submit" class="delete-btn">Add to Order</button>
                                    </form>
                                </div>
                            <?php endforeach; ?>
                        <?php endif; ?>
                    </div>
                </div>
            </section>
        <?php endif; ?>


        <!-- Add Property View -->
        <?php if ($view === 'order_confirmation'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>Are you sure? </h2>
                    <form method="POST">
                        <input type="hidden" name="action" value="order_confirmation">
                        <button type="submit">Confirm order</button>
                        <a href="?view=all_products" class="btn btn-secondary">Cancel</a>
                    </form>
                </div>
            </section>
        <?php endif; ?>
    </div>
</body>
</html>