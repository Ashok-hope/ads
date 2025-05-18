#include <iostream>
#include <vector>
#include <climits>
using namespace std;
struct Edge {
    int u, v, weight;
};
void bellmanFord(int V, int E, vector<Edge>& edges, int source) {
    vector<int> dist(V + 1, INT_MAX);
    dist[source] = 0;
    for (int i = 1; i <= V - 1; ++i) {
        for (auto edge : edges) {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v])
                dist[edge.v] = dist[edge.u] + edge.weight;
        }
    }
    for (auto edge : edges) {
        if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
            cout << "Graph contains a negative weight cycle" << endl;
            return;
        }
    }
    cout << "Vertex Distance from Source " << source << ":\n";
    for (int i = 1; i <= V; ++i)
        cout << "To " << i << " \t\t" << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
}
int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    vector<Edge> edges(E);
    cout << "Enter each edge (u v weight):\n";
    for (int i = 0; i < E; ++i)
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    int source;
    cout << "Enter source vertex (starting from 1): ";
    cin >> source;
    bellmanFord(V, E, edges, source);
    return 0;
}