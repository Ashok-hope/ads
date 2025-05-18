#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Find with Path Compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by Rank
    void unionSets(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);

        if (xroot == yroot)
            return;

        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    void printSets(int n) {
        cout << "Element:  ";
        for (int i = 0; i < n; ++i)
            cout << i << " ";
        cout << "\nSet Root: ";
        for (int i = 0; i < n; ++i)
            cout << find(i) << " ";
        cout << endl;
    }
};

// ---------------------------
// 🚀 Menu-Driven Main Program
// ---------------------------

int main() {
    int n, choice, x, y;
    cout << "Enter number of elements (0 to n-1): ";
    cin >> n;

    DisjointSet ds(n);

    while (true) {
        cout << "\n--- Disjoint Set Menu ---\n";
        cout << "1. Find Set of an Element\n";
        cout << "2. Union of Two Sets\n";
        cout << "3. Display Sets\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter element to find its set: ";
            cin >> x;
            if (x >= 0 && x < n)
                cout << "Set representative: " << ds.find(x) << endl;
            else
                cout << "Invalid element!\n";
            break;

        case 2:
            cout << "Enter two elements to union: ";
            cin >> x >> y;
            if (x >= 0 && x < n && y >= 0 && y < n)
                ds.unionSets(x, y);
            else
                cout << "Invalid elements!\n";
            break;

        case 3:
            ds.printSets(n);
            break;

        case 4:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
