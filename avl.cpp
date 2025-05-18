#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Utility: Get height of node
int height(Node* n) {
    return n ? n->height : 0;
}

// Utility: Get balance factor
int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Utility: Update height of node
void updateHeight(Node* n) {
    if (n)
        n->height = 1 + max(height(n->left), height(n->right));
}

// Right Rotate
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

// Left Rotate
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

// Rebalance node if needed
Node* rebalance(Node* node) {
    updateHeight(node);
    int balance = getBalance(node);

    // Left Heavy
    if (balance > 1) {
        if (getBalance(node->left) < 0)
            node->left = rotateLeft(node->left); // LR case
        return rotateRight(node);               // LL case
    }

    // Right Heavy
    if (balance < -1) {
        if (getBalance(node->right) > 0)
            node->right = rotateRight(node->right); // RL case
        return rotateLeft(node);                    // RR case
    }

    return node;
}

// Insertion
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // No duplicates

    return rebalance(root);
}

// Minimum node (for deletion)
Node* minValueNode(Node* node) {
    Node* curr = node;
    while (curr->left)
        curr = curr->left;
    return curr;
}

// Deletion
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with 1 or 0 children
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        // Node with 2 children
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return rebalance(root);
}

// Search
bool search(Node* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

// In-order Traversal
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
int main() {
    Node* root = nullptr;

    // Insert values
    int keys[] = {20, 4, 15, 70, 50, 100, 80};
    for (int key : keys)
        root = insert(root, key);

    cout << "Inorder after insertion: ";
    inorder(root);
    cout << endl;

    // Search
    int searchKey = 15;
    cout << "Searching " << searchKey << ": " << (search(root, searchKey) ? "Found" : "Not Found") << endl;

    // Delete
    root = deleteNode(root, 70);
    cout << "Inorder after deleting 70: ";
    inorder(root);
    cout << endl;

    return 0;
}
