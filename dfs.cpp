#include <iostream>
#define MAX 100 // Maximum number of vertices

using namespace std;

class Stack {
    int top;
    int capacity;
    int* array;
    
public:
    Stack(int capacity) : top(-1), capacity(capacity) {
        array = new int[capacity];
    }
    
    ~Stack() {
        delete[] array;
    }
    
    bool isFull() {
        return top == capacity - 1;
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    void push(int item) {
        if (isFull()) return;
        array[++top] = item;
    }
    
    int pop() {
        if (isEmpty()) return -1;
        return array[top--];
    }
};

class Graph {
    int adjMatrix[MAX][MAX];
    int vertexCount;
    
    void DFSUtil(int vertex, bool visited[]) {
        visited[vertex] = true;
        cout << vertex << " ";
        
        for (int i = 0; i < vertexCount; i++) {
            if (adjMatrix[vertex][i] == 1 && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }
    
public:
    Graph(int count) : vertexCount(count) {
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }
    
    void addEdge(int src, int dest) {
        if (src >= 0 && src < vertexCount && dest >= 0 && dest < vertexCount) {
            adjMatrix[src][dest] = 1;
            adjMatrix[dest][src] = 1; // For undirected graph
        }
    }
    
    void DFSRecursive(int startVertex) {
        bool visited[MAX] = {false};
        cout << "DFS Recursive Traversal: ";
        DFSUtil(startVertex, visited);
        cout << endl;
    }
    
    void DFSIterative(int startVertex) {
        bool visited[MAX] = {false};
        Stack stack(vertexCount);
        
        stack.push(startVertex);
        cout << "DFS Iterative Traversal: ";
        
        while (!stack.isEmpty()) {
            int currentVertex = stack.pop();
            
            if (!visited[currentVertex]) {
                visited[currentVertex] = true;
                cout << currentVertex << " ";
                
                for (int i = vertexCount - 1; i >= 0; i--) {
                    if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                        stack.push(i);
                    }
                }
            }
        }
        cout << endl;
    }
    
    void printAdjMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

void displayMenu() {
    cout << "\n===== DFS Traversal Menu =====\n";
    cout << "1. Add Edge\n";
    cout << "2. Perform DFS (Recursive)\n";
    cout << "3. Perform DFS (Iterative)\n";
    cout << "4. Print Adjacency Matrix\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int vertexCount;
    cout << "Enter number of vertices in graph: ";
    cin >> vertexCount;
    
    Graph g(vertexCount);
    int choice, src, dest, startVertex;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter source and destination vertices (0-" << vertexCount-1 << "): ";
                cin >> src >> dest;
                g.addEdge(src, dest);
                break;
            case 2:
                cout << "Enter starting vertex for DFS (0-" << vertexCount-1 << "): ";
                cin >> startVertex;
                g.DFSRecursive(startVertex);
                break;
            case 3:
                cout << "Enter starting vertex for DFS (0-" << vertexCount-1 << "): ";
                cin >> startVertex;
                g.DFSIterative(startVertex);
                break;
            case 4:
                g.printAdjMatrix();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}