#include <iostream>
using namespace std;

// Structure to represent a node in AVL Tree
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        height = 1;
        left = right = nullptr;
    }
};

// Function to get height of a node
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Function to get balance factor
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Function to update height of a node
void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Insert a key into AVL tree
Node* insert(Node* root, int key) {
    // Step 1: Normal BST insertion
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // duplicate keys not allowed

    // Step 2: Update height
    updateHeight(root);

    // Step 3: Balance the tree
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Inorder traversal (sorted order)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int n, key;

    cout << "How many numbers do you want to insert? ";
    cin >> n;

    cout << "Enter the numbers: ";
    for (int i = 0; i < n; i++) {
        cin >> key;
        root = insert(root, key);
    }

    cout << "Inorder (sorted) traversal: ";
    inorder(root);
    cout << endl;

    return 0;
}
