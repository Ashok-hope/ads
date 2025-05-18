#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// BFS to find an augmenting path and store it in 'parent'
bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    int V = rGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && rGraph[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                if (v == t) return true;
                q.push(v);
            }
        }
    }

    return false;
}

int fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    int V = graph.size();
    vector<vector<int>> rGraph = graph;
    vector<int> parent(V);
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        // Find minimum residual capacity in the path found
        for (int v = t; v != s; v = parent[v])
            path_flow = min(path_flow, rGraph[parent[v]][v]);

        // Update residual capacities
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    cout << "Enter edges (from to capacity):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        graph[u][v] = cap;
    }

    int source, sink;
    cout << "Enter source and sink: ";
    cin >> source >> sink;

    int maxFlow = fordFulkerson(graph, source, sink);
    cout << "Maximum Flow: " << maxFlow << endl;

    return 0;
}
