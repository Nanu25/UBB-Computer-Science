import graph
import wolf_goat_cabbage

import heapq
import math

def bfs(g, s):
    '''Performs a Breadth-First Search in the graph g starting from vertex s.
    Returns a tuple of 3 dictionaries: the first maps accessible vertices to their parents (None for
      the root - s), the second maps accessible vertices to their distances from s, and the 
      third one maps accessible vertices to the lists of their children
    '''
    prev = {s: None}
    dist = {s: 0}
    children = {s: []}
    queue = [s]
    
    while(len(queue)):
        x = queue.pop(0)
        for y in g.parse_nout(x):
            if not y in prev:
                queue.append(y)
                prev[y] = x
                children[x].append(y)
                dist[y] = dist[x] + 1
                children[y] = []
    
    return prev, dist, children
    
def shortest_path(g, s, t):
    prev, dist, children = bfs(g, s)
    if t not in prev.keys():
        return None
    path = []
    current_vertex = t
    while current_vertex != s:
        path.append(current_vertex)
        current_vertex = prev[current_vertex]
    
    path.append(current_vertex)
    path.reverse()
    
    return path

def dijkstra(g, s):
    '''Executes Dijkstra's algorithm in the graph g (with costs) starting from vertex s.
    Precondition: all costs are non-negative
    Returns a tuple of 2 dictionaries: the first maps accessible vertices to their parents (None for
      the root - s), the second maps accessible vertices to their distances from s
    '''
    prev = {s: None}
    dist = {s: 0}
    queue = [(0,s)]
    
    print(f"queue={queue}, dist={dist}")
    while(len(queue)):
        dx,x = heapq.heappop(queue)
        if dx > dist[x]:
            print(f"Skipping vertex {x}")
            continue
        for y in g.parse_nout(x):
            if not y in dist or dist[x] + g.cost(x,y) < dist[y]:
                dist[y] = dist[x] + g.cost(x,y)
                prev[y] = x
                heapq.heappush(queue, (dist[y], y))
        print(f"x={x}, queue={queue}, dist={dist}")
    
    return prev, dist
    
def min_cost_dijkstra(g, s, t):
    prev, dist = dijkstra(g, s)
    if t not in prev.keys():
        return None
    path = []
    current_vertex = t
    while current_vertex != s:
        path.append(current_vertex)
        current_vertex = prev[current_vertex]
    
    path.append(current_vertex)
    path.reverse()
    
    return path

def compute_min_cost_dp(g, s):
    '''Returns a list of dictionaries w such that w[k][x] = cost of min cost walk from s to x of length k,
    or math.inf if no such walk exists. w[k][x] must be given for all vertices x and for al integers k from 0
    to n (inclusive), where n is the number of vertices
    '''
    all_vertices = list(g.parse_vertices())
    w = [{x : math.inf for x in all_vertices}]
    w[0][s] = 0
    for k in range(len(all_vertices)):
        w.append({})
        for x in all_vertices:
            w[k+1][x] = math.inf
            for y in g.parse_nin(x):
                if w[k+1][x] > w[k][y] + g.cost(y, x):
                    w[k+1][x] = w[k][y] + g.cost(y, x)
    return w

def min_cost_path_dp(g, s, t):
    w = compute_min_cost_dp(g, s)
    print(w)
    min_cost = math.inf
    for k in range(len(w)):
        if min_cost > w[k][t]:
            min_cost = w[k][t]
            len_min_cost = k
    print(f"min_cost={min_cost}")
    if min_cost == math.inf:
        return None
    print(f"len_min_cost={len_min_cost}")
    current_vertex = t
    current_len = len_min_cost
    path = []
    while current_len > 0:
        path.append(current_vertex)
        for previous_vertex in g.parse_nin(current_vertex):
            if (w[current_len-1][previous_vertex] + g.cost(previous_vertex, current_vertex)
                    == w[current_len][current_vertex]):
                current_vertex = previous_vertex
                current_len -= 1
                break
    assert(current_vertex == s)
    path.append(s)
    path.reverse()
    return path

def toposort(g):
    '''Returns a topologically sorted list of all vertices of g, or None if g contains a cycle.
    '''
    sorted = []
    indegree = {}
    for x in g.parse_vertices():
        indegree[x] = len(list(g.parse_nin(x)))
        if indegree[x] == 0:
            sorted.append(x)
    head = 0
    while head < len(sorted):
        x = sorted[head]
        head += 1
        for y in g.parse_nout(x):
            indegree[y] -= 1
            if indegree[y] == 0:
                sorted.append(y)
    if len(sorted) < len(indegree):
        print("Cycle found")
        not_in_sorted=set(g.parse_vertices())-set(sorted)
        visited=set()
        for s in not_in_sorted:
            current=s
            break
            
        while current not in visited:
            visited.add(current)
            for pre in g.parse_nin(current):
                if pre in not_in_sorted :
                    current=pre
                    print(current," ") 
                    break
        return None
    return sorted

def dag_compute_costs(g, s):
    '''Computes the costs of the walks from a vertex s in a DAG
    Returns a tuple of 2 dictionaries: the first maps accessible vertices to their parents (None for
      the root - s), the second maps accessible vertices to their distances from s
    '''
    
    sorted = toposort(g)
    
    prev = {s: None}
    dist = {s: 0}
    for vertex in sorted:
        if vertex == s:
            continue
        dist[vertex] = math.inf
        for neighbor in g.parse_nin(vertex):
            if ((dist[neighbor] + g.cost(neighbor, vertex)) < dist[vertex]):
                dist[vertex] = dist[neighbor] + g.cost(neighbor, vertex)
                prev[vertex] = neighbor
 
    return prev, dist
     #   print(f"x={x}, dist={dist}")
    
    
def min_cost_path_dag(g, s, t):
    prev, dist = dag_compute_costs(g, s)
    print(f"prev={prev}")
    print(f"dist={dist}")
    if t not in prev.keys():
        return None
    path = []
    current_vertex = t
    while current_vertex != s:
        path.append(current_vertex)
        current_vertex = prev[current_vertex]
    
    path.append(current_vertex)
    path.reverse()
    
    return path

def dag_cost_internal(g, s, cache, active, x):
    if x in cache:
        return cache[x]
    if x == s:
        print(f"dag_cost({x}) -> 0")
        cache[x] = 0
        return 0
    if x in active:
        raise Exception("Cycle detected")
    active.add(x)
    dist = math.inf
    for y in g.parse_nin(x):
        dy = dag_cost_internal(g, s, cache, active, y)
        if dist > dy + g.cost(y, x):
            dist = dy + g.cost(y, x)
    print(f"dag_cost({x}) -> {dist}")
    cache[x] = dist
    active.remove(x)
    return dist

def dag_cost(g, s, x):
    '''Computes and returns the cost of min cost walk from s to x
    '''
    cache = {}
    active = set()
    return dag_cost_internal(g, s, cache, active, x)

def test_shortest_path():
    g = graph.create_small_graph(graph.Graph)
    print(shortest_path(g, 0, 3))
    print(shortest_path(g, 0, 0))
    print(shortest_path(g, 3, 0))

def test_wolf_goat_cabbage():
    g = wolf_goat_cabbage.WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    print(shortest_path(g, s, t))

def test_dijkstra():
    g = graph.create_small_graph(graph.Graph)
    print(min_cost_dijkstra(g, 0, 3))
    print(min_cost_dijkstra(g, 0, 0))
    print(min_cost_dijkstra(g, 3, 0))

def test_min_cost_dp():
    g = graph.create_small_graph(graph.Graph)
    print(min_cost_path_dp(g, 0, 3))
    print(min_cost_path_dp(g, 0, 0))
    print(min_cost_path_dp(g, 3, 0))
    print(min_cost_path_dp(g, 2, 1))

def test_dag():
    g = graph.create_small_dag2(graph.Graph)
    print(toposort(g))
    #print(min_cost_path_dag(g, 0, 6))

def test_dag2():
    g = graph.create_small_dag2(graph.Graph)
    #cache = {}
    #active = set()
    #for x in g.parse_vertices():
    #    dag_cost_internal(g, 0, cache, active, x)
    print(dag_cost(g, 0, 6))

if __name__ == "__main__":
    test_dag()
