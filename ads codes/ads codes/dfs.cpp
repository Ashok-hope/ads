#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
class Graph {
    int V;
    list<int> *adj;
    int time;
    void DFSUtil(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low,
        vector<int> &parent, vector<bool> &articulation) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;
        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                DFSUtil(v, visited, disc, low, parent, articulation);
                low[u] = min(low[u], low[v]);
                if (parent[u] == -1 && children > 1)
                    articulation[u] = true;
                if (parent[u] != -1 && low[v] >= disc[u])
                    articulation[u] = true;
            }
            else if (v != parent[u])
                low[u] = min(low[u], disc[v]);
        }
    }
public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
        time = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void findArticulationPoints() {
        vector<bool> visited(V, false);
        vector<int> disc(V), low(V), parent(V, -1);
        vector<bool> articulation(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                DFSUtil(i, visited, disc, low, parent, articulation);
        }
        cout << "\nArticulation points (cut vertices) are:\n";
        bool found = false;
        for (int i = 0; i < V; i++) {
            if (articulation[i]) {
                cout << i+1 << " ";
                found = true;
            }
        }
        if (!found)
            cout << "None (Graph is Biconnected)";
        cout << endl;
    }
};
int main() {            
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V>>E;
    Graph g(V);
    cout << "Enter " << E << " edges (as pairs u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u-1, v-1);
    }
    g.findArticulationPoints();
    return 0;
}