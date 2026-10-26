#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// ============================================================
// Part 1: Min-Heap using vector as raw storage
// ============================================================
class MinHeap {
private:
    vector<int> data_;

    static size_t parent(size_t index) { return (index - 1) / 2; }
    static size_t leftChild(size_t index) { return 2 * index + 1; }
    static size_t rightChild(size_t index) { return 2 * index + 2; }

    void heapifyUp(size_t index) {
        while (index > 0) {
            const size_t parentIndex = parent(index);
            if (data_[parentIndex] <= data_[index]) break;
            swap(data_[parentIndex], data_[index]);
            index = parentIndex;
        }
    }

    void heapifyDown(size_t index) {
        while (true) {
            const size_t left = leftChild(index);
            const size_t right = rightChild(index);
            size_t smallest = index;

            if (left < data_.size() && data_[left] < data_[smallest]) {
                smallest = left;
            }
            if (right < data_.size() && data_[right] < data_[smallest]) {
                smallest = right;
            }
            if (smallest == index) break;

            swap(data_[index], data_[smallest]);
            index = smallest;
        }
    }

public:
    void insert(int value) {
        data_.push_back(value);
        heapifyUp(data_.size() - 1);
    }

    int peekMin() const {
        if (data_.empty()) throw runtime_error("peekMin on empty heap");
        return data_.front();
    }

    int removeMin() {
        if (data_.empty()) throw runtime_error("removeMin on empty heap");

        const int minimum = data_.front();
        data_.front() = data_.back();
        data_.pop_back();
        if (!data_.empty()) heapifyDown(0);
        return minimum;
    }

    void printArray(const string& label) const {
        cout << label << " [";
        for (size_t i = 0; i < data_.size(); ++i) {
            if (i != 0) cout << ", ";
            cout << data_[i];
        }
        cout << "]\n";
    }
};

// ============================================================
// Part 2: Treap
// A treap is a BST by key and a max-heap by priority.
// ============================================================
struct TreapNode {
    int key;
    int priority;
    TreapNode* left = nullptr;
    TreapNode* right = nullptr;

    TreapNode(int keyValue, int priorityValue)
        : key(keyValue), priority(priorityValue) {}
};

class Treap {
private:
    TreapNode* root_ = nullptr;

    static TreapNode* rotateRight(TreapNode* root) {
        TreapNode* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        return newRoot;
    }

    static TreapNode* rotateLeft(TreapNode* root) {
        TreapNode* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        return newRoot;
    }

    static TreapNode* insert(TreapNode* root, int key, int priority) {
        if (root == nullptr) return new TreapNode(key, priority);

        if (key == root->key) {
            // Keep keys unique; update the priority for an existing key.
            root->priority = priority;
            return root;
        }

        if (key < root->key) {
            root->left = insert(root->left, key, priority);
            if (root->left->priority > root->priority) {
                root = rotateRight(root);
            }
        } else {
            root->right = insert(root->right, key, priority);
            if (root->right->priority > root->priority) {
                root = rotateLeft(root);
            }
        }
        return root;
    }

    static const TreapNode* search(const TreapNode* root, int key) {
        if (root == nullptr || root->key == key) return root;
        return key < root->key ? search(root->left, key)
                               : search(root->right, key);
    }

    static void print(const TreapNode* root, const string& branch,
                      int depth) {
        if (root == nullptr) return;
        cout << string(depth * 2, ' ') << branch
                  << " key=" << root->key
                  << ", priority=" << root->priority << "\n";
        print(root->left, "L:", depth + 1);
        print(root->right, "R:", depth + 1);
    }

    static void inorder(const TreapNode* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << "(" << root->key << ", " << root->priority << ") ";
        inorder(root->right);
    }

    static void destroy(TreapNode* root) {
        if (root == nullptr) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

public:
    ~Treap() { destroy(root_); }

    void insert(int key, int priority) {
        root_ = insert(root_, key, priority);
    }

    bool search(int key) const { return search(root_, key) != nullptr; }

    void printStructure() const {
        print(root_, "root:", 0);
    }

    void printInorder() const {
        inorder(root_);
        cout << "\n";
    }
};

int main() {
    cout << "PART 1: MIN-HEAP\n";
    MinHeap heap;
    const vector<int> values = {42, 17, 8, 99, 23, 4, 16, 55, 1, 31, 12};

    for (int value : values) heap.insert(value);
    heap.printArray("After inserting 11 integers:");
    cout << "peekMin(): " << heap.peekMin() << "\n";

    heap.insert(0);
    heap.printArray("After insert(0):");

    cout << "removeMin(): " << heap.removeMin() << "\n";
    heap.printArray("After first removeMin:");
    cout << "removeMin(): " << heap.removeMin() << "\n";
    heap.printArray("After second removeMin:");

    cout << "\nPART 2: TREAP\n";
    Treap treap;
    const vector<pair<int, int>> keyPriorityPairs = {
        {50, 40}, {30, 75}, {70, 60}, {20, 25}, {40, 90},
        {60, 35}, {80, 80}, {10, 15}, {35, 55}, {65, 70}, {90, 10}
    };

    for (const auto& pair : keyPriorityPairs) {
        treap.insert(pair.first, pair.second);
    }

    cout << "Final treap structure (BST by key, max-heap by priority):\n";
    treap.printStructure();
    cout << "In-order (key, priority), proving BST key order:\n";
    treap.printInorder();

    cout << "search(65): " << boolalpha << treap.search(65) << "\n";
    cout << "search(999): " << treap.search(999) << "\n";
}

