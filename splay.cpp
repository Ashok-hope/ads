#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};
// Rotations
Node* rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation
Node* splay(Node* root, int key) {
    if (!root || root->key == key)
        return root;

    // Key in left subtree
    if (key < root->key) {
        if (!root->left) return root;

        // Zig-Zig (left-left)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        }
        // Zig-Zag (left-right)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right)
                root->left = rotateLeft(root->left);
        }

        return root->left ? rotateRight(root) : root;
    }
    // Key in right subtree
    else {
        if (!root->right) return root;

        // Zag-Zig (right-left)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left)
                root->right = rotateRight(root->right);
        }
        // Zag-Zag (right-right)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        }

        return root->right ? rotateLeft(root) : root;
    }
}


// Insert
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    root = splay(root, key);
    if (root->key == key) return root;

    Node* newNode = new Node(key);

    if (key < root->key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    return newNode;
}

// Inorder traversal
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
int main() {
    Node* root = nullptr;
    
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    
    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    root = splay(root, 10);
    cout << "After splaying 10 to root: " << root->key << endl;

    return 0;
}
