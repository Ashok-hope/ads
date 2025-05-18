#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;

template <typename T>
class FibonacciHeap {
private:
    struct Node {
        T key;
        Node* parent = nullptr;
        Node* child = nullptr;
        Node* left;
        Node* right;
        int degree = 0;
        bool mark = false;

        Node(T k) : key(k), left(this), right(this) {}
    };

    Node* minNode = nullptr;
    int n = 0;

    void insertNode(Node* node) {
        if (!minNode) {
            minNode = node;
        } else {
            // Insert node into root list
            node->left = minNode;
            node->right = minNode->right;
            minNode->right->left = node;
            minNode->right = node;
            if (node->key < minNode->key)
                minNode = node;
        }
    }

    void link(Node* y, Node* x) {
        // Remove y from root list
        y->left->right = y->right;
        y->right->left = y->left;

        // Make y a child of x
        y->parent = x;
        if (!x->child) {
            x->child = y;
            y->left = y->right = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }

        x->degree++;
        y->mark = false;
    }

    void consolidate() {
        int D = static_cast<int>(log2(n)) + 1;
        vector<Node*> A(D, nullptr);

        vector<Node*> rootList;
        Node* x = minNode;
        if (x) {
            do {
                rootList.push_back(x);
                x = x->right;
            } while (x != minNode);
        }

        for (Node* w : rootList) {
            x = w;
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (x->key > y->key) swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }

        minNode = nullptr;
        for (Node* y : A) {
            if (y) {
                y->left = y->right = y;
                insertNode(y);
            }
        }
    }

    void cut(Node* x, Node* y) {
        // Remove x from child list of y
        if (x->right == x)
            y->child = nullptr;
        else {
            x->right->left = x->left;
            x->left->right = x->right;
            if (y->child == x)
                y->child = x->right;
        }
        y->degree--;

        // Add x to root list
        x->left = x->right = x;
        insertNode(x);
        x->parent = nullptr;
        x->mark = false;
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z) {
            if (!y->mark)
                y->mark = true;
            else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

public:
    unordered_map<T, Node*> nodeMap;

    void insert(T key) {
        Node* node = new Node(key);
        insertNode(node);
        nodeMap[key] = node;
        n++;
    }

    T getMin() {
        if (!minNode) throw runtime_error("Heap is empty");
        return minNode->key;
    }

    void merge(FibonacciHeap<T>& other) {
        if (!other.minNode) return;
        if (!minNode) {
            minNode = other.minNode;
        } else {
            // Merge circular lists
            Node* tmp1 = minNode->right;
            Node* tmp2 = other.minNode->left;

            minNode->right = other.minNode;
            other.minNode->left = minNode;

            tmp1->left = tmp2;
            tmp2->right = tmp1;

            if (other.minNode->key < minNode->key)
                minNode = other.minNode;
        }
        n += other.n;
        other.minNode = nullptr;
    }

    void extractMin() {
        if (!minNode) return;

        Node* z = minNode;
        if (z->child) {
            Node* x = z->child;
            do {
                Node* next = x->right;
                insertNode(x);
                x->parent = nullptr;
                x = next;
            } while (x != z->child);
        }

        // Remove z from root list
        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            minNode = nullptr;
        } else {
            minNode = z->right;
            consolidate();
        }

        nodeMap.erase(z->key);
        delete z;
        n--;
    }

    void decreaseKey(T oldKey, T newKey) {
        if (newKey > oldKey)
            throw runtime_error("New key is greater than old key");

        Node* x = nodeMap[oldKey];
        x->key = newKey;
        nodeMap.erase(oldKey);
        nodeMap[newKey] = x;

        Node* y = x->parent;
        if (y && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }

        if (x->key < minNode->key)
            minNode = x;
    }

    void deleteKey(T key) {
        decreaseKey(key, INT_MIN);
        extractMin();
    }

    bool isEmpty() {
        return minNode == nullptr;
    }
};
int main() {
    FibonacciHeap<int> fib;

    fib.insert(10);
    fib.insert(3);
    fib.insert(15);
    fib.insert(6);

    cout << "Min: " << fib.getMin() << endl;  // 3

    fib.extractMin();
    cout << "Min after extractMin: " << fib.getMin() << endl;  // 6

    fib.decreaseKey(15, 2);
    cout << "Min after decreaseKey: " << fib.getMin() << endl;  // 2

    return 0;
}
