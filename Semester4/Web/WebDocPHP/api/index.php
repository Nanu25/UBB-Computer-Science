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
                case 'documents':
                    if ($method === 'GET') {
                        $this->getAllDocuments();
                    }
                    break;
                
                case 'user-projects':
                    if ($method === 'GET') {
                        $this->getUserProjects();
                    }
                    break;
                
                case 'websites':
                    if ($method === 'GET') {
                        $this->getAllWebsites();
                    }
                    break;
                
                case 'search-websites':
                    if ($method === 'POST') {
                        $this->getWebSites3Words();
                    }
                    break;
                case 'update-keywords':
                    if ($method === 'PUT') {
                        $this->updateKeywords();
                    }
                    break;
                
                default:
                    $this->sendResponse(['error' => 'Endpoint not found'], 404);
            }
        } catch (Exception $e) {
            $this->sendResponse(['error' => $e->getMessage()], 500);
        }
    }

    private function getAllDocuments() {
        $sql = "SELECT * 
                FROM Documents d";
                //LEFT JOIN Websites w ON d.idWebSite = w.id";
        
        $documents = $this->db->fetchAll($sql);
        $this->sendResponse(['documents' => $documents]);
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

    private function getAllWebsites() {
        $sql = "SELECT * FROM Websites";
        $websites = $this->db->fetchAll($sql);
        $this->sendResponse(['websites' => $websites]);
    }

    private function getWebSites3Words() {
        $input = json_decode(file_get_contents('php://input'), true);
        $words = $input['keywords'] ?? '';

        if (empty($words)) {
            $this->sendResponse(['error' => 'Keywords are required'], 400);
            return;
        }

        $wordsArray = explode(' ', trim($words));
        if (count($wordsArray) != 3) {
            $this->sendResponse(['error' => 'You need to write exactly three words'], 400);
            return;
        }

        // Get all websites
        $sql = "SELECT * FROM Websites";
        $websites = $this->db->fetchAll($sql);
        
        $filteredWebsites = [];
        
        foreach($websites as $website) {
            // Get documents for this website
            $sql = "SELECT * FROM Documents WHERE idWebSite = ?";
            $documents = $this->db->fetchAll($sql, [$website['id']]);
            
            $websiteHasAllWords = true;
            
            // Check if this website has all 3 words
            foreach($wordsArray as $word) {
                $wordFound = false;
                
                // Check if this word exists in any document of this website
                foreach($documents as $document) {
                    // Check all keyword fields and words field
                    if (stripos($document['keyword1'], $word) !== false ||
                        stripos($document['keyword2'], $word) !== false ||
                        stripos($document['keyword3'], $word) !== false ||
                        stripos($document['keyword4'], $word) !== false ||
                        stripos($document['keyword5'], $word) !== false ){
                        $wordFound = true;
                        break;
                    }
                }
                
                if (!$wordFound) {
                    $websiteHasAllWords = false;
                    break;
                }
            }
            
            if ($websiteHasAllWords) {
                $filteredWebsites[] = $website;
            }
        }
        
        $this->sendResponse(['websites' => $filteredWebsites]);
    }

        
    // Add this method to your ProjectAPI class
    private function updateKeywords() {
        $input = json_decode(file_get_contents('php://input'), true);
        $websiteId = $input['websiteId'] ?? '';
        $keywords = $input['keywords'] ?? '';

        if (empty($websiteId)) {
            $this->sendResponse(['error' => 'Website ID is required'], 400);
            return;
        }

        // Parse keywords - assume they are comma-separated
        $keywordArray = array_map('trim', explode(',', $keywords));
        
        // Pad array to have 5 elements
        while (count($keywordArray) < 5) {
            $keywordArray[] = '';
        }
        
        // Take only first 5 keywords
        $keywordArray = array_slice($keywordArray, 0, 5);

        try {
            // Get all documents for this website
            $documents = $this->db->fetchAll("SELECT * FROM Documents WHERE idWebSite = ?", [$websiteId]);
            
            if (empty($documents)) {
                $this->sendResponse(['error' => 'No documents found for this website'], 404);
                return;
            }

            // Update keywords for all documents of this website
            $sql = "UPDATE Documents SET keyword1 = ?, keyword2 = ?, keyword3 = ?, keyword4 = ?, keyword5 = ? WHERE idWebSite = ?";
            $this->db->query($sql, [
                $keywordArray[0],
                $keywordArray[1], 
                $keywordArray[2],
                $keywordArray[3],
                $keywordArray[4],
                $websiteId
            ]);

            $this->sendResponse(['message' => 'Keywords updated successfully']);
            
        } catch (Exception $e) {
            $this->sendResponse(['error' => 'Failed to update keywords: ' . $e->getMessage()], 500);
        }
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
