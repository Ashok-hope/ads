#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF 1e9  // Use a large value to represent infinity

void floydWarshall(vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist = graph;

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // Print the result
    cout << "\nShortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> graph(V, vector<int>(V, INF));

    // Distance to self is 0
    for (int i = 0; i < V; ++i)
        graph[i][i] = 0;

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertex!\n";
            --i; // Retry this edge
        } else {
            graph[u][v] = w;
        }
    }

    floydWarshall(graph, V);
    return 0;
}
