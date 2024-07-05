class Vertex:
    def __init__(self, v):
        self.__v = v
    def __repr__(self):
        sides = ([], [])
        for i in range(4):
            sides[self.get_pos(i)].append(['wolf','goat','cabbage','boat'][i])
        return f"({','.join(sides[0])}|{','.join(sides[1])})"
    def __str__(self):
        return self.__repr__()
    def __eq__(self, other):
        if not isinstance(other, Vertex):
            return False
        return self.__v == other.__v
    def __hash__(self):
        return self.__v
    def get_pos(self, i):
        return 0 if (self.__v & (1 << i)) == 0 else 1
    def is_valid(self):
        if self.get_pos(3) == self.get_pos(1):
            return True
        if self.get_pos(0) == self.get_pos(1):
            return False
        if self.get_pos(2) == self.get_pos(1):
            return False
        return True
    def parse_neighbors(self):
        for i in range(4):
            if self.get_pos(i) == self.get_pos(3):
                v = self.__v
                v ^= (1 << 3)
                if i != 3:
                    v ^= (1 << i)
                if self.is_valid():
                    yield Vertex(v)

class WolfGoatCabbageGraph:
    def is_edge(self, x, y):
        '''Returns True if there is an edge from x to y in the graph, and False otherwise.
            Precondition: x and y are valid vertices of the graph.
        '''
        raise Exception("Not implemented")


    def parse_nout(self, x):
        '''Returns something iterable that contains all the outbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        return x.parse_neighbors()
        
    def parse_nin(self, x):
        '''Returns something iterable that contains all the inbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        return x.parse_neighbors()
    def parse_vertices(self):
        '''Return something iterable that contains all the vertices of the graph
        '''
        raise Exception("Not implemented")

    def initial_state(self):
        return Vertex(0)
    def final_state(self):
        return Vertex(15)
