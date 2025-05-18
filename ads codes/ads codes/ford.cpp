#include <iostream>
#include <vector>
#include <climits>
#include <stack>
using namespace std;
const int MAX_V = 100;
int graph[MAX_V][MAX_V];
bool dfs(int rGraph[MAX_V][MAX_V], int s, int t, int parent[], int V) {
    bool visited[MAX_V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    stack<int> st;
    st.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                st.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t)
                    return true;
            }
        }
    }
    return false;
}
int fordFulkerson(int source, int sink, int V) {
    int u, v;
    int rGraph[MAX_V][MAX_V];
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
    }
    int parent[MAX_V];
    int max_flow = 0;
    while (dfs(rGraph, source, sink, parent, V)) {
        int path_flow = INT_MAX;
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}
int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;
    }
    cout << "Enter edges in format (from to capacity):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        graph[u][v] = cap;
    }
    int source, sink;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter sink vertex: ";
    cin >> sink;
    int maxFlow = fordFulkerson(source, sink, V);
    cout << "Maximum Flow: " << maxFlow << endl;
    return 0;
}