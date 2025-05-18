#include <iostream>
#include <vector>
#include<climits>
using namespace std;

struct Edge {
    int u, v, weight;
};

class Graph {
    int V, E;
    vector<Edge> edges;

public:
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

   void addEdge(int u, int v, int w) {
    if (u < 0 || u >= V || v < 0 || v >= V) {
        cout << "Invalid edge! Vertices should be between 0 and " << V - 1 << ".\n";
        return;
    }
    edges.push_back({u, v, w});
}


    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Relax all edges (V-1) times
        for (int i = 1; i <= V - 1; ++i) {
            for (auto e : edges) {
                if (dist[e.u] != INT_MAX && dist[e.u] + e.weight < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.weight;
                }
            }
        }

        // Check for negative-weight cycles
        for (auto e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.weight < dist[e.v]) {
                cout << "Graph contains a negative weight cycle.\n";
                return;
            }
        }

        // Print distances
        cout << "\nVertex Distance from Source " << src << ":\n";
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INT_MAX)
                cout << i << " : INF\n";
            else
                cout << i << " : " << dist[i] << "\n";
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V, E);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    g.bellmanFord(src);

    return 0;
}
