<?php
    session_start();
    if (!isset($_SESSION['user_id'])) {
        echo json_encode(['error' => 'Not logged in']);
        exit;
    }
    include 'db.php';
    $type = $_GET['type'] ?? '';
    $severity = $_GET['severity'] ?? '';
    $view = $_GET['view'] ?? 'my';
    $page = intval($_GET['page'] ?? 1);
    if ($page < 1) $page = 1;
    
    $limit = 4;
    $offset = ($page - 1) * $limit;
    $where = [];
    $params = [];

    if ($view == 'my') {
        $where[] = 'user_id = ?';
        $params[] = $_SESSION['user_id'];
    }
    if (!empty($type)) {
        $where[] = 'type = ?';
        $params[] = $type;
    }
    if (!empty($severity)) {
        $where[] = 'severity = ?';
        $params[] = $severity;
    }
    $whereClause = empty($where) ? '' : 'WHERE ' . implode(' AND ', $where);
    $countSql = "SELECT COUNT(*) FROM log_reports $whereClause";
    $stmt = $pdo->prepare($countSql);
    $stmt->execute($params);
    $totalCount = $stmt->fetchColumn();
    $sql = "SELECT * FROM log_reports $whereClause ORDER BY date DESC LIMIT ? OFFSET ?";
    $params[] = $limit;
    $params[] = $offset;
    $stmt = $pdo->prepare($sql);
    $stmt->execute($params);
    $logs = $stmt->fetchAll(PDO::FETCH_ASSOC);
    echo json_encode(['logs' => $logs, 'total_count' => $totalCount]);
?>