import random
import time

class Graph:
    def __init__(self, n=0):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges
        '''
        self.__n = n
        self.__inner_edges = {}
        self.__out_edges = {}
        for i in range(n):
            self.__inner_edges[i] = []
            self.__out_edges[i] = []

        self.__cost = {}
        
    def add_vertex(self, x):
        '''Inserts the vertex into the graph.
        Preconditions:
          - x is not already a vertex.
          - x is of a type that can be used as a key in a dictionary (immutable and hashable)
        '''
        self.__inner_edges[x] = []
        self.__out_edges[x] = []
        
        
    def add_edge(self, x, y, c=1):
        '''Adds an edge from vertex x to vertex y and returns True.
            If the edge already exists, nothing happens and the function returns False.
            Precondition: x and y are valid vertices of the graph.
        '''
        if self.is_edge(x,y):
            return False
        self.__inner_edges[y].append(x)
        self.__out_edges[x].append(y)
        self.__cost[(x,y)] = c
        return True
        
    def cost(self, x, y):
        '''Returns the cost of the edge (x,y). Precondition: (x,y) is an edge of the graph
        '''
        return self.__cost[(x,y)]
        
    def is_edge(self, x, y):
        '''Returns True if there is an edge from x to y in the graph, and False otherwise.
            Precondition: x and y are valid vertices of the graph.
        '''
        return  x in self.__inner_edges[y]


    def parse_nout(self, x):
        '''Returns something iterable that contains all the outbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        return list(self.__out_edges[x])
        
    def parse_nin(self, x):
        '''Returns something iterable that contains all the inbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        return list(self.__inner_edges[x])
    def parse_vertices(self):
        '''Return something iterable that contains all the vertices of the graph
        '''
        #return list(self.__inner_edges.keys())
        for x in self.__inner_edges.keys():
            yield x
        
class GraphOutboundOnly:
    def __init__(self, n=0):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges
        '''
        self.__out_edges = {}
        for i in range(n):
            self.__out_edges[i] = []

    def add_vertex(self, x):
        '''Inserts the vertex into the graph.
        Preconditions:
          - x is not already a vertex.
          - x is of a type that can be used as a key in a dictionary (immutable and hashable)
        '''
        self.__out_edges[x] = []
        
    def add_edge(self, x, y):
        '''Adds an edge from vertex x to vertex y and returns True.
            If the edge already exists, nothing happens and the function returns False.
            Precondition: x and y are valid vertices of the graph.
        '''
        if self.is_edge(x,y):
            return False
        self.__out_edges[x].append(y)
        return True
        
    def is_edge(self, x, y):
        '''Returns True if there is an edge from x to y in the graph, and False otherwise.
            Precondition: x and y are valid vertices of the graph.
        '''
        return y in self.__out_edges[x]

    def parse_nout(self, x):
        '''Returns something iterable that contains all the outbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        return list(self.__out_edges[x])
        
    def parse_nin(self, x):
        '''Returns something iterable that contains all the inbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        inbound_list = []
        
        for y in self.__out_edges.keys():
            if x in self.__out_edges[y]:
                inbound_list.append(y)
        
        return inbound_list
    def parse_vertices(self):
        '''Return something iterable that contains all the vertices of the graph
        '''
        #return list(self.__inner_edges.keys())
        for x in self.__out_edges.keys():
            yield x
        
class GraphAdjacencyMatrix:
    def __init__(self, n=0):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges
        '''
        self.__n = n
        self.__matrix = [None for i in range(n)]
        for i in range(n):
            self.__matrix[i] = [False for j in range(n)]
        
    def add_vertex(self, x):
        '''Inserts the vertex into the graph.
        Preconditions:
          - x is not already a vertex.
          - x is of a type that can be used as a key in a dictionary (immutable and hashable)
        '''
        raise Exception("Not supported")
        
    def add_edge(self, x, y):
        '''Adds an edge from vertex x to vertex y and returns True.
            If the edge already exists, nothing happens and the function returns False.
            Precondition: x and y are valid vertices of the graph.
        '''
        if self.is_edge(x,y):
            return False
        self.__matrix[x][y] = True
        return True
        
        
    def is_edge(self, x, y):
        '''Returns True if there is an edge from x to y in the graph, and False otherwise.
            Precondition: x and y are valid vertices of the graph.
        '''
        return self.__matrix[x][y]


    def parse_nout(self, x):
        '''Returns something iterable that contains all the outbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        for i in range(self.__n):
            if self.__matrix[x][i]:
                yield i
    
        
    def parse_nin(self, x):
        '''Returns something iterable that contains all the inbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        for i in range(self.__n):
            if self.__matrix[i][x]:
                yield i
    
    def parse_vertices(self):
        '''Return something iterable that contains all the vertices of the graph
        '''
        return range(self.__n)
        
        
def create_small_graph(ctor):
    g = ctor(5)
    g.add_edge(0, 1, 1)
    g.add_edge(0, 2, 4)
    g.add_edge(1, 2, 2)
    g.add_edge(4, 2, 5)
    g.add_edge(2, 3, 3)
    return g

def create_small_dag(ctor):
    g = ctor(5)
    g.add_edge(0, 1, 1)
    g.add_edge(0, 2, 4)
    g.add_edge(1, 2, 2)
    g.add_edge(4, 2, 5)
    g.add_edge(2, 3, 3)
    
    #g.add_edge(3, 4, 1)
    return g

def create_small_dag2(ctor):
    g = ctor(7)
    g.add_edge(0, 3, 1)
    g.add_edge(0, 4, 1)
    g.add_edge(3, 1, 1)
    g.add_edge(4, 1, -1)
    g.add_edge(1, 2, 1)
    g.add_edge(1, 5, 1)
    g.add_edge(2, 6, 1)
    g.add_edge(5, 6, 1)
    
    #g.add_edge(6, 1, 1)
    g.add_edge(1, 0, 1)
    return g

def create_random_graph(ctor, n, m):
    g = ctor(n)
    for i in range(m):
        origin = random.randrange(n)
        target = random.randrange(n)
        while not g.add_edge(origin, target):
            origin = random.randrange(n)
            target = random.randrange(n)
    return g

def print_graph(g):
    print("Outbound:")
    for x in g.parse_vertices():
        print(f"{x}:", end='')
        for y in g.parse_nout(x):
            print(f" {y}", end='')
        print()
    print("Inbound:")
    for x in g.parse_vertices():
        print(f"{x}:", end='')
        for y in g.parse_nin(x):
            print(f" {y}", end='')
        print()

def measure_time(g):
    print("Outbound:")
    t = time.time()
    for x in g.parse_vertices():
        for y in g.parse_nout(x):
            pass
    print(f"  time={time.time()-t} seconds")
    print("Inbound:")
    t = time.time()
    for x in g.parse_vertices():
        for y in g.parse_nin(x):
            pass
    print(f"  time={time.time()-t} seconds")

def test_basic_graph():
    #g = create_small_graph(GraphAdjacencyMatrix)
    g = create_random_graph(GraphOutboundOnly, 1000, 500000)
    #print_graph(g)
    measure_time(g)

if __name__ == "__main__":
    test_basic_graph()
