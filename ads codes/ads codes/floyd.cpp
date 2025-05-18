#include <iostream>
#include <vector>
using namespace std;
#define INF 1e9
void floydWarshall(int V, vector<vector<int>>& graph) {
    vector<vector<int>> dist = graph;
    for (int k = 1; k <= V; ++k) {
        for (int i = 1; i <= V; ++i) {
            for (int j = 1; j <= V; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 1; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}
int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;
    vector<vector<int>> graph(V + 1, vector<int>(V + 1));
    cout << "Enter adjacency matrix (1-based index, use 1000000000 for INF):\n";
    for (int i = 1; i <= V; ++i)
        for (int j = 1; j <= V; ++j)
            cin >> graph[i][j];
    floydWarshall(V, graph);
    return 0;
}