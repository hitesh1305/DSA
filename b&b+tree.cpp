#include <iostream>
using namespace std;

const int T = 2;

struct BTreeNode {
    int keys[2 * T - 1];
    BTreeNode* children[2 * T];
    int n;
    bool isLeaf;
};

BTreeNode* createNode(bool isLeaf) {
    BTreeNode* node = new BTreeNode;
    node->isLeaf = isLeaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; i++) node->children[i] = NULL;
    return node;
}

void traverse(BTreeNode* root) {
    for (int i = 0; i < root->n; i++) {
        if (!root->isLeaf) traverse(root->children[i]);
        cout << root->keys[i] << " ";
    }
    if (!root->isLeaf) traverse(root->children[root->n]);
}

void splitChild(BTreeNode* parent, int i, BTreeNode* fullChild) {
    BTreeNode* newNode = createNode(fullChild->isLeaf);
    newNode->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        newNode->keys[j] = fullChild->keys[j + T];

    if (!fullChild->isLeaf)
        for (int j = 0; j < T; j++)
            newNode->children[j] = fullChild->children[j + T];

    fullChild->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = newNode;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = fullChild->keys[T - 1];

    parent->n++;
}

void insertNonFull(BTreeNode* node, int k) {
    int i = node->n - 1;

    if (node->isLeaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && k < node->keys[i]) i--;
        i++;
        if (node->children[i]->n == 2 * T - 1) {
            splitChild(node, i, node->children[i]);
            if (k > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], k);
    }
}

void insert(BTreeNode*& root, int k) {
    if (root->n == 2 * T - 1) {
        BTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        int i = (k > newRoot->keys[0]) ? 1 : 0;
        insertNonFull(newRoot->children[i], k);
        root = newRoot;
    } else {
        insertNonFull(root, k);
    }
}

const int DEGREE = 2;

struct BPlusNode {
    int keys[2 * DEGREE];
    BPlusNode* children[2 * DEGREE + 1];
    int n;
    bool isLeaf;
    BPlusNode* next;
};

BPlusNode* createBPlusNode(bool isLeaf) {
    BPlusNode* node = new BPlusNode;
    node->isLeaf = isLeaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i < 2 * DEGREE + 1; i++) node->children[i] = NULL;
    return node;
}

void bplusTraverse(BPlusNode* root) {
    while (!root->isLeaf) root = root->children[0];
    while (root) {
        for (int i = 0; i < root->n; i++) cout << root->keys[i] << " ";
        root = root->next;
    }
}

void bplusInsertNonFull(BPlusNode* node, int k);

void bplusSplitChild(BPlusNode* parent, int i, BPlusNode* fullChild) {
    BPlusNode* newLeaf = createBPlusNode(fullChild->isLeaf);
    int mid = DEGREE;

    for (int j = 0; j < DEGREE; j++)
        newLeaf->keys[j] = fullChild->keys[j + mid];

    if (!fullChild->isLeaf) {
        for (int j = 0; j <= DEGREE; j++)
            newLeaf->children[j] = fullChild->children[j + mid];
    }

    newLeaf->n = DEGREE;
    fullChild->n = DEGREE;

    if (fullChild->isLeaf) {
        newLeaf->next = fullChild->next;
        fullChild->next = newLeaf;
    }

    for (int j = parent->n; j > i; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = newLeaf;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = newLeaf->keys[0];
    parent->n++;
}

void bplusInsertNonFull(BPlusNode* node, int k) {
    int i = node->n - 1;
    if (node->isLeaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && k < node->keys[i]) i--;
        i++;
        if (node->children[i]->n == 2 * DEGREE) {
            bplusSplitChild(node, i, node->children[i]);
            if (k > node->keys[i]) i++;
        }
        bplusInsertNonFull(node->children[i], k);
    }
}

void bplusInsert(BPlusNode*& root, int k) {
    if (root->n == 2 * DEGREE) {
        BPlusNode* newRoot = createBPlusNode(false);
        newRoot->children[0] = root;
        bplusSplitChild(newRoot, 0, root);
        int i = (k > newRoot->keys[0]) ? 1 : 0;
        bplusInsertNonFull(newRoot->children[i], k);
        root = newRoot;
    } else {
        bplusInsertNonFull(root, k);
    }
}

int main() {
    cout << "=== B Tree ===\n";
    BTreeNode* bRoot = createNode(true);
    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++) insert(bRoot, values[i]);
    traverse(bRoot);
    cout << "\n";

    cout << "=== B+ Tree ===\n";
    BPlusNode* bpRoot = createBPlusNode(true);
    for (int i = 0; i < 8; i++) bplusInsert(bpRoot, values[i]);
    bplusTraverse(bpRoot);
    cout << "\n";

    return 0;
}
