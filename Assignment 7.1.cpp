#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node { //used ai to make the node
    int key;
    Node* left;
    Node* right;

    explicit Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root_ = nullptr;

    static Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    static bool search(const Node* node, int key) {
        if (node == nullptr) return false;
        if (key == node->key) return true;
        return key < node->key ? search(node->left, key)
                               : search(node->right, key);
    }

    static Node* smallestNode(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    static Node* remove(Node* node, int key) {
        if (node == nullptr) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            // Case 1: leaf.
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: exactly one child.
            if (node->left == nullptr) {
                Node* replacement = node->right;
                delete node;
                return replacement;
            }
            if (node->right == nullptr) {
                Node* replacement = node->left;
                delete node;
                return replacement;
            }

            // Case 3: two children. Replace with the inorder successor.
            Node* successor = smallestNode(node->right);
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        }
        return node;
    }

    static void inorder(const Node* node, vector<int>& result) {
        if (node == nullptr) return;
        inorder(node->left, result);
        result.push_back(node->key);
        inorder(node->right, result);
    }

    static void preorder(const Node* node, vector<int>& result) {
        if (node == nullptr) return;
        result.push_back(node->key);
        preorder(node->left, result);
        preorder(node->right, result);
    }

    static void postorder(const Node* node, vector<int>& result) {
        if (node == nullptr) return;
        postorder(node->left, result);
        postorder(node->right, result);
        result.push_back(node->key);
    }

    static int height(const Node* node) {
        if (node == nullptr) return -1; // Height measured in edges.
        return 1 + max(height(node->left), height(node->right));
    }

    static void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    vector<int> traversal(void (*traversalFunction)(const Node*, vector<int>&)) const {
        vector<int> result;
        traversalFunction(root_, result);
        return result;
    }

public:
    ~BinarySearchTree() { destroy(root_); }

    void insert(int key) { root_ = insert(root_, key); }

    bool search(int key) const { return search(root_, key); }

    void remove(int key) { root_ = remove(root_, key); }

    vector<int> inorder() const { return traversal(inorder); }
    vector<int> preorder() const { return traversal(preorder); }
    vector<int> postorder() const { return traversal(postorder); }
    int height() const { return height(root_); }

    void printInorder(const string& label) const {
        cout << label;
        for (int value : inorder()) cout << value << ' ';
        cout << '\n';
    }
};

void printVector(const string& label, const vector<int>& values) {
    cout << label;
    for (int value : values) cout << value << ' ';
    cout << '\n';
}

bool isSorted(const vector<int>& values) {
    for (size_t i = 1; i < values.size(); ++i) {
        if (values[i - 1] >= values[i]) return false;
    }
    return true;
}

int main() {
    BinarySearchTree tree;

    // Twelve distinct keys give enough nodes to demonstrate every removal case.
    const vector<int> values = {
        50, 30, 70, 20, 40, 60, 80, 10, 35, 65, 75, 85
    };
    for (int value : values) tree.insert(value);

    cout << "Initial traversals:\n";
    tree.printInorder("inorder:   ");
    printVector("preorder:  ", tree.preorder());
    printVector("postorder: ", tree.postorder());
    cout << "height (edges): " << tree.height() << "\n\n";

    cout << boolalpha;
    cout << "search(65):  " << tree.search(65) << "\n";
    cout << "search(999): " << tree.search(999) << "\n\n";

    // Leaf case: 10 has no children.
    tree.remove(10);
    vector<int> afterLeaf = tree.inorder();
    printVector("after removing leaf 10: ", afterLeaf);
    cout << "sorted: " << isSorted(afterLeaf) << "\n\n";

    // One-child case: 60 has one child, 65.
    tree.remove(60);
    vector<int> afterOneChild = tree.inorder();
    printVector("after removing one-child node 60: ", afterOneChild);
    cout << "sorted: " << isSorted(afterOneChild) << "\n\n";

    // Two-child case: 70 has left child 65 and right child 80.
    tree.remove(70);
    vector<int> afterTwoChildren = tree.inorder();
    printVector("after removing two-child node 70: ", afterTwoChildren);
    cout << "sorted: " << isSorted(afterTwoChildren) << "\n\n";
}
