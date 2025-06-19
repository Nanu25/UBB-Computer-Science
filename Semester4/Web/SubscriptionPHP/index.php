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
$channels = [];
$userSubs = [];
$searchResults = [];

// // Handle form submissions
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $userId = $_SESSION['user']['id'];
    
    if (isset($_POST['action'])) {
        switch ($_POST['action']) {
            case 'add_channel':
                $name = trim($_POST['channelName'] ?? '');
                $description = trim($_POST['description'] ?? '');
                
                if (!empty($name) && !empty($description)) {
                    try {
                        // Check if property exists
                        $existingProperty = $db->fetchOne(
                            "SELECT id FROM Channels WHERE name = ?", 
                            [$name]
                        );
                        
                        if (!$existingProperty) {
                            // Insert new property
                            $db->query("INSERT INTO Channels (name, description) VALUES (?, ?)", 
                                      [$name, $description]);
                            $channelId = $db->getConnection()->lastInsertId();
                        } else {
                            $channelId = $existingProperty['id'];
                        }
                        
                        // Check if relationship exists
                        $existingRelation = $db->fetchOne(
                            "SELECT id FROM PersonChannels WHERE idPerson = ? AND idChannel = ?",
                            [$userId, $channelId]
                        );
                        
                        if (!$existingRelation) {
                            $db->query("INSERT INTO PersonChannels (idPerson, idChannel) VALUES (?, ?)", 
                                      [$userId, $channelId]);
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
                
            case 'delete_channel':
                $channelId = $_POST['channelId'] ?? '';
                if (!empty($channelId)) {
                    try {
                        // Delete user-property relationships first
                        $db->query("DELETE FROM PersonChannels WHERE idChannel = ?", [$channelId]);
                        // Delete the property
                        $db->query("DELETE FROM Channels WHERE id = ?", [$channelId]);
                        $message = "Channel deleted successfully!";
                    } catch (Exception $e) {
                        $message = "Error deleting property: " . $e->getMessage();
                    }
                }
                break;
            case 'subscribe':
                $channelId = $_POST['channelId'] ?? '';
                $userId = $_POST['userId'] ?? '';
                $existingRelation = $db->fetchOne(
                            "SELECT id FROM PersonChannels WHERE idPerson = ? AND idChannel = ?",
                            [$userId, $channelId]
                        );                

                if($existingRelation){
                    $message="Already subscribed";
                }else {
                    $db->query("Insert into PersonChannels  (idPerson, idChannel) values (?,?)", [$userId, $channelId]);
                }

                break;
        }
    }
}

// Handle different views
$view = $_GET['view'] ?? 'all_channels';

switch ($view) {
    case 'all_channels':
        $channels = $db->fetchAll("SELECT * FROM Channels ORDER BY id DESC");
        break;
        
    case 'my_subs':
        $userSubs = $db->fetchAll(
            "SELECT c.* FROM Channels c 
             INNER JOIN PersonChannels pc ON c.id = pc.idChannel 
             INNER JOIN Person p on p.id = pc.idPerson
             WHERE pc.idPerson = ? 
             ORDER BY c.id DESC", 
            [$_SESSION['user']['id']]
        );
        break;
        
    case 'search':
        $searchTerm = $_GET['search'] ?? '';
        if (!empty($searchTerm)) {
            $searchResults = $db->fetchAll(
                "SELECT * FROM Channels WHERE description LIKE ? ORDER BY id DESC", 
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
    <title>Channel Management </title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>Channel Management</h1>
            <div class="user-info">
                Welcome, <?= htmlspecialchars($_SESSION['user']['name']) ?>! 
                <a href="logout.php">Logout</a>
            </div>
        </header>

        <!-- Navigation -->
        <nav class="navigation">
            <a href="?view=all_channels" class="nav-btn <?= $view === 'all_channels' ? 'active' : '' ?>">
                All Channels
            </a>
            <a href="?view=my_subs" class="nav-btn <?= $view === 'my_subs' ? 'active' : '' ?>">
                My Properties
            </a>
            
            <a href="?view=add_channel" class="nav-btn <?= $view === 'add_channel' ? 'active' : '' ?>">
                Add Channel
            </a>
        </nav>

        <?php if ($message): ?>
            <div class="message <?= strpos($message, 'Error') === 0 ? 'error' : 'success' ?>">
                <?= htmlspecialchars($message) ?>
            </div>
        <?php endif; ?>

        <!-- All Properties View -->
        <?php if ($view === 'all_channels'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>All Channels</h2>
                    
                    <!-- Search Form -->
                    <form method="GET" class="form-group">
                        <input type="hidden" name="view" value="search">
                        <input type="text" name="search" value="<?= htmlspecialchars($_GET['search'] ?? '') ?>" 
                               placeholder="Search by description">
                        <button type="submit">Search</button>
                        <a href="?view=all_channels" class="btn">Show All</a>
                    </form>
                    
                    <div class="properties-list">
                        <?php if (empty($channels)): ?>
                            <p>No properties found.</p>
                        <?php else: ?>
                            <?php foreach ($channels as $channel): ?>
                                <div class="project-item">
                                    <h3><?= htmlspecialchars($channel['description']) ?></h3>
                                    <p><strong>ID:</strong> <?= $channel['id'] ?></p>
                                    <p><strong>Name:</strong> <?= htmlspecialchars($channel['name']) ?></p>
                                    
                                    <form method="POST" style="display: inline;" 
                                          onsubmit="return confirm('Are you sure you want to delete this channel?')">
                                        <input type="hidden" name="action" value="delete_channel">
                                        <input type="hidden" name="channelId" value="<?= $channel['id'] ?>">
                                        <button type="submit" class="delete-btn">Delete</button>
                                    </form>

                                    <form method="POST" style="display: inline;" 
                                          onsubmit="return confirm('Are you sure you want to subscribe this channel?')">
                                        <input type="hidden" name="action" value="subscribe">
                                        <input type="hidden" name="channelId" value="<?= $channel['id'] ?>">
                                        <input type="hidden" name="userId" value="<?= $_SESSION['user']['id'] ?>">
                                        <button type="submit" class="delete-btn">Subscribe</button>
                                    </form>
                                </div>
                            <?php endforeach; ?>
                        <?php endif; ?>
                    </div>
                    <div class="count">
                        <p>Total Channels: <strong><?= count($channels) ?></strong></p>
                    </div>
                </div>
            </section>
        <?php endif; ?>

        <?php if ($view === 'search'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>Search Results</h2>
                    
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
                                <?php foreach ($searchResults as $channel): ?>
                                    <div class="project-item">
                                        <h3><?= htmlspecialchars($channel['description']) ?></h3>
                                        <p><strong>ID:</strong> <?= $channel['id'] ?></p>
                                        <p><strong>Description:</strong> <?= htmlspecialchars($channel['description']) ?></p>
                                        
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
        <?php if ($view === 'my_subs'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>My Subscriptions</h2>
                    <div class="properties-list">
                        <?php if (empty($userSubs)): ?>
                            <p>You don't have any properties yet. <a href="?view=add_channel">Add one now</a></p>
                        <?php else: ?>
                            <?php foreach ($userSubs as $sub): ?>
                                <div class="project-item">
                                    <h3><?= htmlspecialchars($sub['description']) ?></h3>
                                    <p><strong>Name:</strong> <?= htmlspecialchars($sub['name']) ?></p>
                                </div>
                            <?php endforeach; ?>
                        <?php endif; ?>
                    </div>
                    <div class="count">
                        <p>Total My Properties: <strong><?= count($userSubs) ?></strong></p>
                    </div>
                </div>
            </section>
        <?php endif; ?>

        <!-- Add Property View -->
        <?php if ($view === 'add_channel'): ?>
            <section class="content-section">
                <div class="card">
                    <h2>Add New Channel</h2>
                    <form method="POST">
                        <input type="hidden" name="action" value="add_channel">
                        <div class="form-group">
                            <label for="channelName">Channel Name:</label>
                            <input type="text" id="channelName" name="channelName" 
                                   placeholder="Enter channel name" required>
                        </div>
                        <div class="form-group">
                            <label for="description">Channel Description:</label>
                            <textarea id="description" name="description" 
                                     placeholder="Enter channel description" required></textarea>
                        </div>
                        <button type="submit">Add Channel</button>
                        <a href="?view=all_channels" class="btn btn-secondary">Cancel</a>
                    </form>
                </div>
            </section>
        <?php endif; ?>
    </div>
</body>
</html>