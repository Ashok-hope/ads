#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

void addEdge(int u, int v) {
    if (u < 0 || v < 0 || u >= V || v >= V) {
        cout << "Invalid edge! Vertices should be between 0 and " << V - 1 << ".\n";
        return;
    }
    adj[u].push_back(v);
    adj[v].push_back(u);
}

    void display() {
        cout << "\nGraph:\n";
        for (int i = 0; i < V; ++i) {
            cout << i << ": ";
            for (int v : adj[i])
                cout << v << " ";
            cout << endl;
        }
    }

    bool isBiconnected() {
        vector<bool> visited(V, false);
        vector<int> disc(V), low(V), parent(V, -1);
        int time = 0;
        bool foundArticulation = false;

        dfs(0, visited, disc, low, parent, time, foundArticulation);

        for (bool v : visited)
            if (!v) return false;

        return !foundArticulation;
    }

private:
    void dfs(int u, vector<bool>& visited, vector<int>& disc, vector<int>& low,
             vector<int>& parent, int& time, bool& foundArticulation) {
        visited[u] = true;
        disc[u] = low[u] = ++time;
        int children = 0;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                dfs(v, visited, disc, low, parent, time, foundArticulation);
                low[u] = min(low[u], low[v]);

                if ((parent[u] == -1 && children > 1) ||
                    (parent[u] != -1 && low[v] >= disc[u])) {
                    foundArticulation = true;
                }
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
};

int main() {
    int V, choice;
    cout << "Enter number of vertices: ";
    cin >> V;
    Graph g(V);

    while (true) {
        cout << "\n1. Add Edge\n2. Display Graph\n3. Check Biconnectivity\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int u, v;
            cout << "Enter edge (u v): ";
            cin >> u >> v;
            g.addEdge(u, v);
        } else if (choice == 2) {
            g.display();
        } else if (choice == 3) {
            if (g.isBiconnected())
                cout << "Graph is BICONNECTED.\n";
            else
                cout << "Graph is NOT BICONNECTED.\n";
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
