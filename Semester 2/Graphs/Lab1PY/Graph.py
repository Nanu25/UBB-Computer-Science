from collections import deque
from copy import deepcopy  # Importing deepcopy for creating deep copies of objects
from fileinput import close  # Importing close function from fileinput module (not used)
from random import randint  # Importing randint function for generating random integers

class Graph:
    def __init__(self, n=0, m=0):
        """
        Initialize a graph object.

        Parameters:
        - n: Number of vertices
        - m: Number of edges
        """
        self.__n = n  # Number of vertices
        self.__m = 0  # Number of edges (initialized to 0)
        self.__inner_edges = {}  # Dictionary to store inner edges of vertices
        self.__outer_edges = {}  # Dictionary to store outer edges of vertices
        self.__max_vertex = n  # Maximum vertex index
        for i in range(n):
            self.__inner_edges[i] = []  # Initialize inner edges as empty lists
            self.__outer_edges[i] = []  # Initialize outer edges as empty lists

        self.__edges = []  # List to store all edges in the graph

    @property
    def vertices(self):
        """Return the number of vertices in the graph."""
        return self.__n

    @property
    def edges(self):
        """Return the number of edges in the graph."""
        return self.__m

    def get_inner_degree(self, x):
        """Return the inner degree of vertex x."""
        if x > self.__n or x < 0:
            raise ValueError("Vertex does not exist")
        return len(self.__inner_edges[x])

    def get_outer_degree(self, x):
        """Return the outer degree of vertex x."""
        if x > self.__n or x < 0:
            raise ValueError("Vertex does not exist")
        return len(self.__outer_edges[x])

    def get_edge_cost(self, x, y):
        """
        Return the cost of the edge between vertices x and y.
        If the edge doesn't exist, return None.
        """
        for edge in self.__edges:
            if edge[0] == x and edge[1] == y:
                return edge[2]
        return None

    def add_edge(self, x, y, z):
        """
        Add an edge between vertices x and y with cost z.
        """
        if self.find_edge(x, y) is not None:
            raise ValueError("Edge already exists")

        if x > self.__n or y > self.__n:
            raise ValueError("Vertex does not exist")

        self.__inner_edges[y].append(x)  # Add y to the inner edges of x
        self.__outer_edges[x].append(y)  # Add x to the outer edges of y
        self.__edges.append((x, y, z))    # Add the edge to the list of edges
        self.__m += 1  # Increment the number of edges

    def get_inner_edges(self, x):
        """Return the inner edges of vertex x."""
        if x > self.__n:
            raise ValueError("Vertex does not exist")
        return self.__inner_edges[x]

    def get_outer_edges(self, x):
        """Return the outer edges of vertex x."""
        if x > self.__n:
            raise ValueError("Vertex does not exist")
        return self.__outer_edges[x]

    def find_edge(self, x, y):
        """
        Check if there's an edge between vertices x and y.
        If found, return the edge, otherwise return None.
        """
        for edge in self.__inner_edges[y]:
            if edge == x:
                return edge
        return None

    def vertex_iterator(self):
        """Iterate through all vertices in the graph."""
        for i in range(self.__n):
            yield i

    def edge_iterator(self):
        """Iterate through all edges in the graph."""
        for edge in self.__edges:
            yield edge

    def remove_edge(self, x, y):
        """
        Remove the edge between vertices x and y.
        """
        if self.find_edge(x, y) is None:
            raise ValueError("Edge does not exist")
        self.__inner_edges[y].remove(x)  # Remove y from the inner edges of x
        self.__outer_edges[x].remove(y)  # Remove x from the outer edges of y
        self.__edges.remove((x, y, self.get_edge_cost(x, y)))  # Remove the edge from the list of edges
        self.__m -= 1  # Decrement the number of edges

    def remove_vertex(self, x):
        """
        Remove vertex x from the graph.
        """
        if x > self.__n:
            raise ValueError("Vertex does not exist")

        # Remove all edges incident to vertex x
        while len(self.__inner_edges[x]) > 0:
            self.remove_edge(self.__inner_edges[x][0], x)

        while len(self.__outer_edges[x]) > 0:
            self.remove_edge(x, self.__outer_edges[x][0])

        self.__n -= 1  # Decrement the number of vertices

    def add_vertex(self):
        """Add a new vertex to the graph."""
        self.__inner_edges[self.__n] = []  # Initialize inner edges of the new vertex
        self.__outer_edges[self.__n] = []  # Initialize outer edges of the new vertex
        self.__n += 1  # Increment the number of vertices
        self.__max_vertex += 1  # Update the maximum vertex index

    def update_edge(self, x, y, z):
        """
        Update the cost of the edge between vertices x and y to z.
        """
        if self.find_edge(x, y) is None:
            raise ValueError("Edge does not exist")

        self.__edges.remove((x, y, self.get_edge_cost(x, y)))  # Remove the old edge
        self.__edges.append((x, y, z))  # Add the updated edge

    def copy_graph(self):
        """Create a deep copy of the graph."""
        return deepcopy(self)

    def print_graph(self):
        """Print the graph in a readable format."""
        for i in range(self.__max_vertex):
            if len(self.__outer_edges[i]) > 0:
                print(i, ":", self.__outer_edges[i])

    def bfs(self, start, end):
        """
        Perform Breadth First Search (BFS) to find the shortest path from end to start.

        Returns:
        - List of vertices representing the shortest path from start to end.
        """
        queue = deque()
        queue.append(end)
        parent = [None] * self.vertices  # Initialize parent list for backtracking the path
        visited = set()
        visited.add(end)

        while queue:
            node = queue.popleft()
            if node == start:
                break
            for neighbor in self.__inner_edges[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    parent[neighbor] = node
                    queue.append(neighbor)

        if start not in visited:
            return None

        # Reconstruct the path from start to end
        path = []
        node = start
        while node is not None:
            path.append(node)
            node = parent[node]

        return path

def generate_random_graph(n, m):
    """
    Generate a random graph with n vertices and m edges.

    Returns:
    - Randomly generated graph object.
    """
    graph = Graph(n, m)
    while m != 0:
        x = randint(0, n - 1)
        y = randint(0, n - 1)
        z = randint(0, 1000)
        try:
            graph.add_edge(x, y, z)
            m -= 1
        except ValueError:
            pass

    return graph

def read_graph(filename):
    """
    Read graph data from a file.

    Returns:
    - Graph object created from the data in the file.
    """
    with open(filename, "r") as file:
        n, m = map(int, file.readline().split())
        graph = Graph(n, m)

        for line in file:
            x, y, z = map(int, line.split())
            graph.add_edge(x, y, z)
    close()  # Closing the file (unused)
    return graph

def write_graph(graph, filename):
    """
    Write graph data to a file.

    Parameters:
    - graph: Graph object to be written to the file.
    - filename: Name of the file to write the graph data to.
    """
    with open(filename, "w") as file:
        file.write(str(graph.vertices) + " " + str(graph.edges) + "\n")
        for edge in graph.edge_iterator():
            file.write(str(edge[0]) + " " + str(edge[1]) + " " + str(edge[2]) + "\n")
    close()  # Closing the file (unused)

if __name__ == '__main__':
    # Example usage: Generate random graphs and write them to files
    graph = generate_random_graph(7, 20)
    write_graph(graph, "random_graph1.txt")

    graph = generate_random_graph(6, 10)
    write_graph(graph, "random_graph2.txt")
