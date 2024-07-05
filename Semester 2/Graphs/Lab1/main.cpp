#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

typedef pair<int, int> PII;
const int INF = 1e9;
const int DIM = 1e5;

stack <int> S;
vector<PII> G[DIM + 5], GT[DIM + 5];
vector <int> Strong_components[DIM + 5];
priority_queue <PII, vector<PII>, greater<PII>> PQ;
int dp[DIM + 5], cnt[DIM + 5];
int number_vertex, number_edges, nrcomp;
int in_degree[DIM + 5], out_degree[DIM + 5];
int in_degreeGT[DIM + 5], out_degreeGT[DIM + 5];
int dist[DIM + 5];
int nextt[DIM + 5];
bool visited[DIM + 5];

bool Find_edge(int x, int y, const vector<pair<int, int>> G[]) {
    for(auto e : G[x])
        if(e.first == y)
            return true;
    return false;
}

void Add_edge(int x, int y, int z, vector<pair<int, int>> G[], int in_degree[], int out_degree[]) {
    if(Find_edge(x, y, G))
        return;

    G[x].push_back({y, z});
    out_degree[x]++;
    in_degree[y]++;
}

int get_number_of_vertex(const vector<pair<int, int>> G[]) {
    return DIM; // Assuming DIM is the total number of vertices
}

void print_graph(const vector<pair<int, int>> G[]) {
    for(int i = 0; i < DIM; i++) {
        cout << "The vertex " << i << " has the list of adjacency list: ";
        for(auto e : G[i])
            cout << e.first << " ";
        cout << '\n';
    }
}

int get_in_degree(int x, const int in_degree[]) {
    return in_degree[x];
}

int get_out_degree(int x, const int out_degree[]) {
    return out_degree[x];
}

void outbound_edges(int x, const vector<pair<int, int>> G[]) {
    cout << "Outbound edges for vertex " << x << ": ";
    for(auto e : G[x])
        cout << e.first << " ";
    cout << '\n';
}

void update_edge(int x, int y, int new_cost, vector<pair<int, int>> G[]) {
    if(Find_edge(x, y, G)) {
        for(int i = 0; i < G[x].size(); i++)
            if(G[x][i].first == y)
                G[x][i].second = new_cost;
    }
}

void inbound_edges(int x, const vector<pair<int, int>> G[]) {
    cout << "Inbound edges for vertex " << x << ": ";
    for(int i = 0; i < DIM; i++)
        if(Find_edge(i, x, G))
            cout << i << " ";
    cout << '\n';
}

void delete_edge(int x, int y, int z, vector<pair<int, int>> G[], int in_degree[], int out_degree[]) {
    if(Find_edge(x, y, G)) {
        auto it = find(G[x].begin(), G[x].end(), make_pair(y, z));
        if (it != G[x].end()) {
            G[x].erase(it);
            out_degree[x]--;
            in_degree[y]--;
        }
    }
}

void copy_graph(vector<pair<int, int>> dest[DIM], const vector<pair<int, int>> source[DIM], int &nr_vert, int &nr_edges, int in_degree[], int out_degree[]) {
    for (int i = 0; i < DIM; ++i) {
        dest[i] = source[i]; // Using the assignment operator of std::vector
    }
    nr_vert = DIM;
    nr_edges = 0; // You need to compute the number of edges here
    // Copy in_degree and out_degree arrays
    for(int i = 0; i < DIM; ++i) {
        in_degree[i] = in_degree[i];
        out_degree[i] = out_degree[i];
    }
}

void delete_vertex(int x, vector<pair<int, int>> G[], int in_degree[], int out_degree[]) {
    G[x].clear();
    out_degree[x] = 0;
    in_degree[x] = 0;

    for (int i = 0; i < DIM; ++i) {
        auto& edges = G[i];
        auto it = remove_if(edges.begin(), edges.end(), [=](const pair<int, int>& edge) {
            if (edge.first == x) {
                // Decrease out_degree for the source vertex of the deleted edge
                --out_degree[i];
                return true;
            }
            return false;
        });
        edges.erase(it, edges.end());
    }
}

void write_graph_file(string& filename, const vector<pair<int, int>> G[], int number_vertex, int number_edges) {
    ofstream fout(filename);

    fout << number_vertex << " " << number_edges << '\n';

    for (int i = 0; i < number_vertex; ++i) {
        for (auto edge : G[i]) {
            fout << i << " " << edge.first << " " << edge.second << '\n';
        }
    }

    fout.close();
}


void generate_random_graph(int vertex, int edges, string& filename) {
    vector <PII> G[1005];
    int i_deg[1005], o_deg[1005];
    for(int i = 1; i <= edges; i++) {
        int x = rand() % vertex;
        int y = rand() % vertex;
        int z = rand() % (vertex + edges);
        Add_edge(x, y, z, G, i_deg, o_deg);
    }
    write_graph_file(filename, G, vertex, edges);
}

void graph_functions() {
    cout << "1 for 1k graph file\n";
    cout << "2 for 10k graph file\n";
    cout << "3 for 100k graph file\n";
    cout << "4 for 1M graph file\n";
    cout << "5 for generate a random graph";
    cout << "Tell the option do you want for the graph\n";
    int option;
    cin >> option;
    string filename;
    if(option == 1)
        filename = "graph1k.in";
    else if(option == 2)
        filename = "graph10k.in";
    else if(option == 3)
        filename = "graph100k.txt";
    else if(option == 4)
        filename = "graph1m.txt";
    else {
        filename = "my_file.out";
        generate_random_graph(100, 200, filename);
    }
    ifstream fin(filename);
    fin >> number_vertex >> number_edges;

    for(int i = 1, x, y, z; i <= number_edges; i++) {
        fin >> x >> y >> z;
        Add_edge(x, y, z, G, in_degree, out_degree);
    }

    //string filename="myfile.out";
    //generate_random_graph(10, 20,filename);

    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Remove Edge\n";
        cout << "3. Print Graph\n";
        cout << "4. Get Inbound Edges\n";
        cout << "5. Get Outbound Edges\n";
        cout << "6. Update Edge\n";
        cout << "7. Get in degree\n";
        cout << "8. Get out degree\n";
        cout << "9. Delete a vertex\n";
        cout << "0. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int x, y, z;
        switch (choice) {
            case 1:
                cout << "Enter source vertex, destination vertex, and edge weight: ";
                cin >> x >> y >> z;
                Add_edge(x, y, z, G, in_degree, out_degree);
                break;
            case 2:
                cout << "Enter source vertex, destination vertex, and edge weight: ";
                cin >> x >> y >> z;
                delete_edge(x, y, z, G, in_degree, out_degree);
                break;
            case 3:
                print_graph(G);
                break;
            case 4:
                cout << "Enter vertex: ";
                cin >> x;
                inbound_edges(x, G);
                break;
            case 5:
                cout << "Enter vertex: ";
                cin >> x;
                outbound_edges(x, G);
                break;
            case 6:
                cout << "Enter source vertex, destination vertex, and new edge weight: ";
                cin >> x >> y >> z;
                update_edge(x, y, z, G);
                break;
            case 7:
                cout << "Enter vertex: ";
                cin >> x;
                cout << "In degree for " << x << " is " << get_in_degree(x, in_degree) << '\n';
                break;
            case 8:
                cout << "Enter vertex: ";
                cin >> x;
                cout << "Out degree for " << x << " is " << get_out_degree(x, out_degree) << '\n';
                break;
            case 9:
                cout << "Enter vertex: ";
                cin >> x;
                delete_vertex(x, G, in_degree, out_degree);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    } while (choice != 0);
}

void dfs(int node) {
    visited[node] = 1;
    for(auto e : G[node])
        if(!visited[e.first])
            dfs(e.first);

    S.push(node);
}

void dfsGT(int node, int nrcomp) {
    visited[node] = 1;
    Strong_components[nrcomp].push_back(node);
    for(auto e : GT[node])
        if(visited[e.first] == 0)
            dfsGT(e.first, nrcomp);
}

///Complexity O(n + m);
void strong_components_algorithm() {
    cout << "1 for 1k graph file\n";
    cout << "2 for 10k graph file\n";
    cout << "3 for 100k graph file\n";
    cout << "4 for 1M graph file\n";
    cout << "5 for generate a random graph";
    cout << "Tell the option do you want for the graph\n";
    int option;
    cin >> option;
    string filename;
    if(option == 1)
        filename = "graph1k.in";
    else if(option == 2)
        filename = "graph10k.in";
    else if(option == 3)
        filename = "graph100k.txt";
    else if(option == 4)
        filename = "graph1m.txt";
    else {
        filename = "my_file.out";
        generate_random_graph(100, 200, filename);
    }
    ifstream fin(filename);
    fin >> number_vertex >> number_edges;

    for(int i = 1, x, y, z; i <= number_edges; i++) {
        fin >> x >> y >> z;
        Add_edge(x, y, z, G, in_degree, out_degree);
        Add_edge(y, x, z, GT, in_degreeGT, out_degreeGT);
    }

    for(int i = 0; i < number_vertex; i++)
        if(visited[i] == 0) {
            dfs(i);
        }

    for(int i = 0; i < number_vertex; i++)
        visited[i] = 0;

    while(S.empty() == 0) {
        if(visited[S.top()] == 0) {
            nrcomp++;
            dfsGT(S.top(), nrcomp);
        }
        S.pop();
    }

    for(int i = 1; i <= nrcomp; i++) {
        cout << "The " << i << " component is: ";
        for(auto e : Strong_components[i])
            cout << e << " ";
        cout << '\n';
    }

}

void Dijkstra_min_distance(int x, int y) {
    for(int i = 1; i <= number_vertex; i++) {
        dist[i] = INF;          ///all distances are very big at the begining
    }
    PQ.push({0, y});      ///distance and node
    dist[y] = 0;                   ///the distance from y to y is 0
    nextt[y] = 0;
    while(!PQ.empty()) {
        int node = PQ.top().second;
        int d = PQ.top().first;
        PQ.pop();

        if(d > dist[node])          ///Relaxation process
            continue;

        for(auto e : GT[node])
            if(d + e.second < dist[e.first]) {  ///if i have a better distance
                dist[e.first] = d + e.second;   ///save the best distance
                PQ.push({dist[e.first], e.first});      ///push in the pq
                nextt[e.first] = node;
            }
    }
    cout << "The cost is: " << dist[x] << '\n';
    cout << "The path is: ";
    ///path reconstitution
    int a = x;
    while(nextt[a] != 0) {
        cout << a << " ";
        a = nextt[a];
    }
    cout << a << '\n';
}

///dp[i] = The number of paths from the vertex x to to the vertex i
void Dijkstra_number_of_min_paths(int x, int y) {
    for(int i = 1; i <= number_vertex; i++)
        dist[i] = INF;

    dist[x] = 0;
    dp[x] = 1;
    PQ.push({0, x});
    while(!PQ.empty()) {
        int node = PQ.top().second;
        int d = PQ.top().first;
        PQ.pop();

        if(d > dist[node])
            continue;

        for(auto e : G[node])
            if(e.second + d < dist[e.first]) {
                dist[e.first] = e.second + d;
                PQ.push({dist[e.first], e.first});
                dp[e.first] = dp[node];
            }else if(e.second + d == dist[e.first])
                dp[e.first] += dp[node];
    }
    cout << "The number of min cost paths is: ";
    cout << dp[y];
}

void dfsPaths(int x, int y, int &number) {
    if(x == y)
        number++;
    else
        for(auto e : G[x]) {
            if(visited[e.first] == 0) {
                visited[e.first] = 1;
                dfsPaths(e.first, y, number);
                visited[e.first] = 0;
            }
        }
}

void Number_of_paths(int x, int y) {
    int nr=0;
    dfsPaths(x, y, nr);
    cout << endl;
    cout << "The number of paths between the nodes: ";
    cout << nr;
}

void dfsTopo(int node, vector<int> aux, int &ok) {
    visited[node] = 1;
    aux.push_back(node);
    for(auto e : G[node]) {
        if(std::find(aux.begin(), aux.end(), e.first) != aux.end()) {
            ok = 0;     //there is a cycle
        }
        if (!visited[e.first])
            dfsTopo(e.first, aux, ok);
    }

    S.push(node);
    aux.pop_back();
}

void topologicalSort(int s, int t) {
    vector <int> aux;
    int ok = 1;
    for(int i = 1; i <= number_vertex; i++) {
        if(visited[i] == 0)
            dfsTopo(i, aux, ok);
    }

    if(ok == 0) {
        cout << "This is not a DAG, because it has a cycle\n";
        return;
    }

    for(int i = 1; i <= number_vertex; i++)
        dist[i] = -INF;

    dist[s] = 0;

    cout << "Topological sort: ";

    int parent[100];
    parent[s] = 0;
    while(!S.empty()) {
        int node = S.top();
        cout << node << " ";
        S.pop();

        if(dist[node] != -INF)
            for(auto e : G[node])
                if(dist[e.first] < dist[node] + e.second) {
                    dist[e.first] = dist[node] + e.second;
                    parent[e.first] = node;
                }
    }

    vector <int> path;
    int node = t;
    while(node != s) {
        path.push_back(node);
        node = parent[node];
    }
    cout << "\nThe path is\n";
    path.push_back(node);
    reverse(path.begin(), path.end());
    for(auto e : path)
        cout << e << " ";
    cout << "\n";
    cout << "The longest distance between vertex " << s << " and  " << t << " is " << dist[t] << '\n';

}

void BellmanFord(int s, int t) {
    for(int i = 1; i <= number_vertex; i++)
        dist[i] = INF;

    dist[s] = 0;
    int fr[100] = {0};

    queue <int> Q;
    Q.push(s);
    while(Q.empty() == 0) {
        int node = Q.front();
        int d = dist[node];
        Q.pop();

        fr[node]++;
        if(fr[node] == number_vertex) {
            cout << "There is a negative cycle\n";
            return;
        }

        for(auto e : G[node]) {
            if(d + e.second < dist[e.first]) {
                dist[e.first] = d + e.second;
                Q.push(e.first);
                cout << e.first << ' ';
            }
        }
    }

   cout << "\n The minimum cost is: \n" << dist[t];
}

int main() {
    cout << "1 for graph functions\n";
    cout << "2 for find the strongly-connected components of a directed graph\n";
    cout << "3 for use a backwards Dijkstra algorithm\n";
    cout << "4 for topological sort\n";
    cout << "5 for Bellman Ford min path algorithm\n";

    int option;
    cin >> option;
    if(option == 1)
        graph_functions();
    else if(option == 2)
        strong_components_algorithm();
    else if(option == 3) {      ///6 4 (cost is 7) (min paths = 5) (number of paths = 8)
        int x, y;
        cout << "Tell the first vertex\n";
        cin >> x;
        cout << "Tell the second vertex\n";
        cin >> y;

        ifstream fin("myfile.out");
        //ifstream fin("graph100k.txt");
        fin >> number_vertex >> number_edges;

        for(int i = 1, x, y, z; i <= number_edges; i++) {
            fin >> x >> y >> z;
            Add_edge(x, y, z, G, in_degree, out_degree);
            Add_edge(y, x, z, GT, in_degreeGT, out_degreeGT);
        }

        Dijkstra_min_distance(x, y);
        Dijkstra_number_of_min_paths(x, y);     //Bonus 1
        Number_of_paths(x, y);                  //Bonus 2
    }else if(option == 4){
        int x, y;
        cout << "Tell the vertices for the high cost\n";
        cout << "Tell the first vertex\n";
        cin >> x;
        cout << "Tell the second vertex\n";
        cin >> y;

        ifstream fin("toposortfile");
        //ifstream fin("graph100k.txt");
        fin >> number_vertex >> number_edges;

        for(int i = 1, x, y, z; i <= number_edges; i++) {
            fin >> x >> y >> z;
            Add_edge(x, y, z, G, in_degree, out_degree);
        }
        topologicalSort(x, y);  ///Top sort: 1 3 5 9 4 8 7 6 2 and the distance from 1 to 7 is 8;

    }else {
        int x, y;
        cout << "Tell the vertices for the negative cost path\n";
        cout << "Tell the first vertex \n";
        cin >> x;
        cout << "Tell the second vertex \n";
        cin >> y;

        ifstream fin("BellmanFord");
        fin >> number_vertex >> number_edges;

        for(int i = 1, x, y, z; i <= number_edges; i++) {
            fin >> x >> y >> z;
            Add_edge(x, y, z, G, in_degree, out_degree);
        }
        BellmanFord(x, y);          ///S: 1 T: 2 min cost -5
    }

    return 0;
}
