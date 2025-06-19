<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');

// Handle preflight requests
if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    exit(0);
}

require_once '../config/database.php';

class ProjectAPI {
    private $db;

    public function __construct() {
        $this->db = new Database();
    }

    public function handleRequest() {
        $method = $_SERVER['REQUEST_METHOD'];
        $path = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
        $segments = explode('/', trim($path, '/'));
        
        // Remove the base path segments to get the actual endpoint
        $endpoint = end($segments);

        try {
            switch ($endpoint) {
                case 'projects':
                    if ($method === 'GET') {
                        $this->getAllProjects();
                    }
                    break;
                
                case 'user-projects':
                    if ($method === 'GET') {
                        $this->getUserProjects();
                    }
                    break;
                
                case 'developers':
                    if ($method === 'GET') {
                        $this->getAllDevelopers();
                    }
                    break;
                
                case 'assign-developer':
                    if ($method === 'POST') {
                        $this->assignDeveloperToProjects();
                    }
                    break;
                
                default:
                    $this->sendResponse(['error' => 'Endpoint not found'], 404);
            }
        } catch (Exception $e) {
            $this->sendResponse(['error' => $e->getMessage()], 500);
        }
    }

    private function getAllProjects() {
        $sql = "SELECT p.*, sd.name as manager_name 
                FROM Project p 
                LEFT JOIN SoftwareDeveloper sd ON p.ProjectManagerID = sd.id 
                ORDER BY p.id";
        
        $projects = $this->db->fetchAll($sql);
        $this->sendResponse(['projects' => $projects]);
    }

    private function getUserProjects() {
        $userName = $_GET['user'] ?? '';
        
        if (empty($userName)) {
            $this->sendResponse(['error' => 'User name is required'], 400);
            return;
        }

        $sql = "SELECT name FROM Project WHERE members LIKE ? ORDER BY name";
        $projects = $this->db->fetchAll($sql, ["%{$userName}%"]);
        
        $projectNames = array_column($projects, 'name');
        $this->sendResponse(['projects' => $projectNames]);
    }

    private function getAllDevelopers() {
        $sql = "SELECT * FROM SoftwareDeveloper ORDER BY name";
        $developers = $this->db->fetchAll($sql);
        $this->sendResponse(['developers' => $developers]);
    }

    private function assignDeveloperToProjects() {
        $input = json_decode(file_get_contents('php://input'), true);
        
        $developerName = $input['developer'] ?? '';
        $projectNames = $input['projects'] ?? [];

        if (empty($developerName) || empty($projectNames)) {
            $this->sendResponse(['error' => 'Developer name and projects are required'], 400);
            return;
        }

        // Check if developer exists
        $developer = $this->db->fetchOne(
            "SELECT * FROM SoftwareDeveloper WHERE name = ?", 
            [$developerName]
        );

        if (!$developer) {
            $this->sendResponse(['error' => 'Developer not found'], 404);
            return;
        }

        $results = [];
        
        foreach ($projectNames as $projectName) {
            // Check if project exists
            $project = $this->db->fetchOne(
                "SELECT * FROM Project WHERE name = ?", 
                [$projectName]
            );

            if (!$project) {
                // Create new project
                $sql = "INSERT INTO Project (name, description, members) VALUES (?, '', ?)";
                $this->db->query($sql, [$projectName, $developerName]);
                $results[] = "Created new project '{$projectName}' and added {$developerName}";
            } else {
                // Check if developer is already a member
                $members = $project['members'] ?? '';
                if (strpos($members, $developerName) === false) {
                    // Add developer to existing project
                    $newMembers = empty($members) ? $developerName : $members . ',' . $developerName;
                    $sql = "UPDATE Project SET members = ? WHERE id = ?";
                    $this->db->query($sql, [$newMembers, $project['id']]);
                    $results[] = "Added {$developerName} to existing project '{$projectName}'";
                } else {
                    $results[] = "{$developerName} is already a member of '{$projectName}'";
                }
            }
        }

        $this->sendResponse(['results' => $results]);
    }

    private function sendResponse($data, $statusCode = 200) {
        http_response_code($statusCode);
        echo json_encode($data);
        exit;
    }
}

$api = new ProjectAPI();
$api->handleRequest();
?>
