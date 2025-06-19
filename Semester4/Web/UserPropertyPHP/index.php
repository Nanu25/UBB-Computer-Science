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
$properties = [];
$userProperties = [];
$searchResults = [];

// Handle form submissions
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $userId = $_SESSION['user']['id'];
    
    if (isset($_POST['action'])) {
        switch ($_POST['action']) {
            case 'add_property':
                $address = trim($_POST['propertyAddress'] ?? '');
                $description = trim($_POST['propertyDescription'] ?? '');
                
                if (!empty($address) && !empty($description)) {
                    try {
                        // Check if property exists
                        $existingProperty = $db->fetchOne(
                            "SELECT id FROM Property WHERE address = ?", 
                            [$address]
                        );
                        
                        if (!$existingProperty) {
                            // Insert new property
                            $db->query("INSERT INTO Property (description, address) VALUES (?, ?)", 
                                      [$description, $address]);
                            $propertyId = $db->getConnection()->lastInsertId();
                        } else {
                            $propertyId = $existingProperty['id'];
                        }
                        
                        // Check if relationship exists
                        $existingRelation = $db->fetchOne(
                            "SELECT id FROM UserToProperty WHERE idUser = ? AND idProprty = ?",
                            [$userId, $propertyId]
                        );
                        
                        if (!$existingRelation) {
                            $db->query("INSERT INTO UserToProperty (idUser, idProprty) VALUES (?, ?)", 
                                      [$userId, $propertyId]);
                            $message = "Property added successfully!";
                        } else {
                            $message = "You already have this property!";
                        }
                    } catch (Exception $e) {
                        $message = "Error: " . $e->getMessage();
                    }
                } else {
                    $message = "Please fill all fields!";
                }
                break;
                
            case 'delete_property':
                $propertyId = $_POST['propertyId'] ?? '';
                if (!empty($propertyId)) {
                    try {
                        // Delete user-property relationships first
                        $db->query("DELETE FROM UserToProperty WHERE idProprty = ?", [$propertyId]);
                        // Delete the property
                        $db->query("DELETE FROM Property WHERE id = ?", [$propertyId]);
                        $message = "Property deleted successfully!";
                    } catch (Exception $e) {
                        $message = "Error deleting property: " . $e->getMessage();
                    }
                }
                break;
        }
    }
}

// Handle different views
$view = $_GET['view'] ?? 'all_properties';

switch ($view) {
    case 'all_properties':
        $properties = $db->fetchAll("SELECT * FROM Property ORDER BY id DESC");
        break;
        
    case 'my_properties':
        $userProperties = $db->fetchAll(
            "SELECT p.* FROM Property p 
             INNER JOIN UserToProperty utp ON p.id = utp.idProperty 
             WHERE utp.idUser = ? 
             ORDER BY p.id DESC", 
            [$_SESSION['user']['id']]
        );
        break;
        
    case 'search':
        $searchTerm = $_GET['search'] ?? '';
        if (!empty($searchTerm)) {
            $searchResults = $db->fetchAll(
                "SELECT * FROM Property WHERE description LIKE ? ORDER BY id DESC", 
                ["%{$searchTerm}%"]
            );
        }
        break;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>User Property Management</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>User Property Management System</h1>
            <div class="user-info">
                Welcome, <?= htmlspecialchars($_SESSION['user']['name']) ?>! 
                <a href="logout.php">Logout</a>
            </div>
        </header>

        <!-- Navigation -->
        <nav class="navigation">
            <a href="?view=all_properties" class="nav-btn <?= $view === 'all_properties' ? 'active' : '' ?>">
                All Properties
            </a>
            <a href="?view=my_properties" class="nav-btn <?= $view === 'my_properties' ? 'active' : '' ?>">
                My Properties
            </a>
            <a href="?view=add_property" class="nav-btn <?= $view === 'add_property' ? 'active' : '' ?>">
                Add Property
            </a>
        </nav>

        <?php if ($message): ?>
            <div class="message <?= strpos($message, 'Error') === 0 ? 'error' : 'success' ?>">
                <?= htmlspecialchars($message) ?>
            </div>
        <?php endif; ?>

        <!-- All Properties View -->
        <?php if ($view === 'all_properties'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>All Properties</h2>
                    
                    <!-- Search Form -->
                    <form method="GET" class="form-group">
                        <input type="hidden" name="view" value="search">
                        <input type="text" name="search" value="<?= htmlspecialchars($_GET['search'] ?? '') ?>" 
                               placeholder="Search by description">
                        <button type="submit">Search</button>
                        <a href="?view=all_properties" class="btn">Show All</a>
                    </form>
                    
                    <div class="properties-list">
                        <?php if (empty($properties)): ?>
                            <p>No properties found.</p>
                        <?php else: ?>
                            <?php foreach ($properties as $property): ?>
                                <div class="project-item">
                                    <h3><?= htmlspecialchars($property['description']) ?></h3>
                                    <p><strong>ID:</strong> <?= $property['id'] ?></p>
                                    <p><strong>Address:</strong> <?= htmlspecialchars($property['address']) ?></p>
                                    
                                    <form method="POST" style="display: inline;" 
                                          onsubmit="return confirm('Are you sure you want to delete this property?')">
                                        <input type="hidden" name="action" value="delete_property">
                                        <input type="hidden" name="propertyId" value="<?= $property['id'] ?>">
                                        <button type="submit" class="delete-btn">Delete</button>
                                    </form>
                                </div>
                            <?php endforeach; ?>
                        <?php endif; ?>
                    </div>
                    <div class="count">
                        <p>Total Properties: <strong><?= count($properties) ?></strong></p>
                    </div>
                </div>
            </section>
        <?php endif; ?>

        <!-- Search Results View -->
        <?php if ($view === 'search'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>Search Results</h2>
                    
                    <!-- Search Form -->
                    <form method="GET" class="form-group">
                        <input type="hidden" name="view" value="search">
                        <input type="text" name="search" value="<?= htmlspecialchars($_GET['search'] ?? '') ?>" 
                               placeholder="Search by description">
                        <button type="submit">Search</button>
                        <a href="?view=all_properties" class="btn">Show All</a>
                    </form>
                    
                    <?php if (!empty($_GET['search'])): ?>
                        <p>Search results for: <strong><?= htmlspecialchars($_GET['search']) ?></strong></p>
                        
                        <div class="properties-list">
                            <?php if (empty($searchResults)): ?>
                                <p>No properties found matching your search.</p>
                            <?php else: ?>
                                <?php foreach ($searchResults as $property): ?>
                                    <div class="project-item">
                                        <h3><?= htmlspecialchars($property['description']) ?></h3>
                                        <p><strong>ID:</strong> <?= $property['id'] ?></p>
                                        <p><strong>Address:</strong> <?= htmlspecialchars($property['address']) ?></p>
                                        
                                        <form method="POST" style="display: inline;" 
                                              onsubmit="return confirm('Are you sure you want to delete this property?')">
                                            <input type="hidden" name="action" value="delete_property">
                                            <input type="hidden" name="propertyId" value="<?= $property['id'] ?>">
                                            <button type="submit" class="delete-btn">Delete</button>
                                        </form>
                                    </div>
                                <?php endforeach; ?>
                            <?php endif; ?>
                        </div>
                        <div class="count">
                            <p>Found: <strong><?= count($searchResults) ?></strong> properties</p>
                        </div>
                    <?php endif; ?>
                </div>
            </section>
        <?php endif; ?>

        <!-- My Properties View -->
        <?php if ($view === 'my_properties'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>My Properties</h2>
                    <div class="properties-list">
                        <?php if (empty($userProperties)): ?>
                            <p>You don't have any properties yet. <a href="?view=add_property">Add one now</a></p>
                        <?php else: ?>
                            <?php foreach ($userProperties as $property): ?>
                                <div class="project-item">
                                    <h3><?= htmlspecialchars($property['description']) ?></h3>
                                    <p><strong>Address:</strong> <?= htmlspecialchars($property['address']) ?></p>
                                </div>
                            <?php endforeach; ?>
                        <?php endif; ?>
                    </div>
                    <div class="count">
                        <p>Total My Properties: <strong><?= count($userProperties) ?></strong></p>
                    </div>
                </div>
            </section>
        <?php endif; ?>

        <!-- Add Property View -->
        <?php if ($view === 'add_property'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>Add New Property</h2>
                    <form method="POST">
                        <input type="hidden" name="action" value="add_property">
                        <div class="form-group">
                            <label for="propertyAddress">Property Address:</label>
                            <input type="text" id="propertyAddress" name="propertyAddress" 
                                   placeholder="Enter property address" required>
                        </div>
                        <div class="form-group">
                            <label for="propertyDescription">Property Description:</label>
                            <textarea id="propertyDescription" name="propertyDescription" 
                                     placeholder="Enter property description" required></textarea>
                        </div>
                        <button type="submit">Add Property</button>
                        <a href="?view=all_properties" class="btn btn-secondary">Cancel</a>
                    </form>
                </div>
            </section>
        <?php endif; ?>
    </div>
</body>
</html>