#include <iostream>
using namespace std;

template <typename T>
class LeftistHeap {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        int npl; // Null Path Length

        Node(const T& val) : key(val), left(nullptr), right(nullptr), npl(0) {}
    };

    Node* root;

    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        // Ensure h1 has smaller key
        if (h2->key < h1->key)
            swap(h1, h2);

        // Merge h1->right with h2
        h1->right = merge(h1->right, h2);

        // Ensure leftist property
        if (!h1->left || h1->left->npl < h1->right->npl)
            swap(h1->left, h1->right);

        // Update NPL
        h1->npl = h1->right ? h1->right->npl + 1 : 0;
        return h1;
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    LeftistHeap() : root(nullptr) {}

    ~LeftistHeap() {
        destroy(root);
    }

    void insert(const T& val) {
        Node* newNode = new Node(val);
        root = merge(root, newNode);
    }

    void mergeWith(LeftistHeap<T>& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    const T& findMin() const {
        if (isEmpty()) throw runtime_error("Heap is empty");
        return root->key;
    }

    void deleteMin() {
        if (isEmpty()) throw runtime_error("Heap is empty");
        Node* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }
};
int main() {
    LeftistHeap<int> heap;

    heap.insert(10);
    heap.insert(5);
    heap.insert(30);
    heap.insert(3);

    cout << "Minimum: " << heap.findMin() << endl; // 3
    heap.deleteMin();
    cout << "New Minimum: " << heap.findMin() << endl; // 5

    return 0;
}
