#include <iostream>
using namespace std;

const int CAPACITY = 10;

// 1. Array stack
class ArrayStack {
private:
    int data[CAPACITY];
    int topIndex;
public:
    ArrayStack() : topIndex(-1) {}
    bool isEmpty() const { return topIndex == -1; }
    bool isFull() const { return topIndex == CAPACITY - 1; }

    bool push(int value) {
        if (isFull()) return false;
        data[++topIndex] = value;
        return true;
    }
    bool pop(int& value) {
        if (isEmpty()) return false;
        value = data[topIndex--];
        return true;
    }
    bool peek(int& value) const {
        if (isEmpty()) return false;
        value = data[topIndex];
        return true;
    }
    void display() const {
        cout << "Top -> ";
        for (int i = topIndex; i >= 0; --i) cout << data[i] << ' ';
        cout << '\n';
    }
};

// 2. linked list stack
class LinkedStack {
private:
    struct Node {
        int value;
        Node* next;
        Node(int v, Node* n = nullptr) : value(v), next(n) {}
    };
    Node* topNode;
public:
    LinkedStack() : topNode(nullptr) {}
    ~LinkedStack() {
        while (topNode != nullptr) {
            Node* old = topNode;
            topNode = topNode->next;
            delete old;
        }
    }
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    bool isEmpty() const { return topNode == nullptr; }
    void push(int value) { topNode = new Node(value, topNode); }
    bool pop(int& value) {
        if (isEmpty()) return false;
        Node* old = topNode;
        value = old->value;
        topNode = old->next;
        delete old;
        return true;
    }
    bool peek(int& value) const {
        if (isEmpty()) return false;
        value = topNode->value;
        return true;
    }
    void display() const {
        cout << "Top -> ";
        for (Node* cur = topNode; cur != nullptr; cur = cur->next)
            cout << cur->value << ' ';
        cout << '\n';
    }
};

// 3. Array-based queue
class ArrayQueue {
private:
    int data[CAPACITY];
    int frontIndex;
    int rearIndex;
    int count;
public:
    ArrayQueue() : frontIndex(0), rearIndex(-1), count(0) {}
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == CAPACITY; }

    bool enqueue(int value) {
        if (isFull()) return false;
        rearIndex = (rearIndex + 1) % CAPACITY;
        data[rearIndex] = value;
        ++count;
        return true;
    }
    bool dequeue(int& value) {
        if (isEmpty()) return false;
        value = data[frontIndex];
        frontIndex = (frontIndex + 1) % CAPACITY;
        --count;
        return true;
    }
    bool peek(int& value) const {
        if (isEmpty()) return false;
        value = data[frontIndex];
        return true;
    }
    void display() const {
        cout << "Front -> ";
        for (int i = 0; i < count; ++i)
            cout << data[(frontIndex + i) % CAPACITY] << ' ';
        cout << "<- Rear\n";
    }
};

// 4. Linked list queue
class LinkedQueue {
private:
    struct Node {
        int value;
        Node* next;
        Node(int v) : value(v), next(nullptr) {}
    };
    Node* frontNode;
    Node* rearNode;
public:
    LinkedQueue() : frontNode(nullptr), rearNode(nullptr) {}
    ~LinkedQueue() {
        while (frontNode != nullptr) {
            Node* old = frontNode;
            frontNode = frontNode->next;
            delete old;
        }
    }
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    bool isEmpty() const { return frontNode == nullptr; }
    void enqueue(int value) {
        Node* node = new Node(value);
        if (isEmpty()) frontNode = rearNode = node;
        else {
            rearNode->next = node;
            rearNode = node;
        }
    }
    bool dequeue(int& value) {
        if (isEmpty()) return false;
        Node* old = frontNode;
        value = old->value;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete old;
        return true;
    }
    bool peek(int& value) const {
        if (isEmpty()) return false;
        value = frontNode->value;
        return true;
    }
    void display() const {
        cout << "Front -> ";
        for (Node* cur = frontNode; cur != nullptr; cur = cur->next)
            cout << cur->value << ' ';
        cout << "<- Rear\n";
    }
};

// 5. Array-based deque: insertion/removals at either end
class ArrayDeque {
private:
    int data[CAPACITY];
    int frontIndex;
    int count;
public:
    ArrayDeque() : frontIndex(0), count(0) {}
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == CAPACITY; }

    bool pushFront(int value) {
        if (isFull()) return false;
        frontIndex = (frontIndex - 1 + CAPACITY) % CAPACITY;
        data[frontIndex] = value;
        ++count;
        return true;
    }
    bool pushBack(int value) {
        if (isFull()) return false;
        int backIndex = (frontIndex + count) % CAPACITY;
        data[backIndex] = value;
        ++count;
        return true;
    }
    bool popFront(int& value) {
        if (isEmpty()) return false;
        value = data[frontIndex];
        frontIndex = (frontIndex + 1) % CAPACITY;
        --count;
        return true;
    }
    bool popBack(int& value) {
        if (isEmpty()) return false;
        int backIndex = (frontIndex + count - 1) % CAPACITY;
        value = data[backIndex];
        --count;
        return true;
    }
    void display() const {
        cout << "Front -> ";
        for (int i = 0; i < count; ++i)
            cout << data[(frontIndex + i) % CAPACITY] << ' ';
        cout << "<- Back\n";
    }
};

// 6. Linkedlist deque
class LinkedDeque {
private:
    struct Node {
        int value;
        Node* prev;
        Node* next;
        Node(int v) : value(v), prev(nullptr), next(nullptr) {}
    };
    Node* frontNode;
    Node* backNode;
public:
    LinkedDeque() : frontNode(nullptr), backNode(nullptr) {}
    ~LinkedDeque() {
        while (frontNode != nullptr) {
            Node* old = frontNode;
            frontNode = frontNode->next;
            delete old;
        }
    }
    LinkedDeque(const LinkedDeque&) = delete;
    LinkedDeque& operator=(const LinkedDeque&) = delete;

    bool isEmpty() const { return frontNode == nullptr; }
    void pushFront(int value) {
        Node* node = new Node(value);
        if (isEmpty()) frontNode = backNode = node;
        else {
            node->next = frontNode;
            frontNode->prev = node;
            frontNode = node;
        }
    }
    void pushBack(int value) {
        Node* node = new Node(value);
        if (isEmpty()) frontNode = backNode = node;
        else {
            node->prev = backNode;
            backNode->next = node;
            backNode = node;
        }
    }
    bool popFront(int& value) {
        if (isEmpty()) return false;
        Node* old = frontNode;
        value = old->value;
        frontNode = frontNode->next;
        if (frontNode == nullptr) backNode = nullptr;
        else frontNode->prev = nullptr;
        delete old;
        return true;
    }
    bool popBack(int& value) {
        if (isEmpty()) return false;
        Node* old = backNode;
        value = old->value;
        backNode = backNode->prev;
        if (backNode == nullptr) frontNode = nullptr;
        else backNode->next = nullptr;
        delete old;
        return true;
    }
    void display() const {
        cout << "Front -> ";
        for (Node* cur = frontNode; cur != nullptr; cur = cur->next)
            cout << cur->value << ' ';
        cout << "<- Back\n";
    }
};



int main() {
    int removed = 0;
    int peeked = 0;

    cout << "=== 1. ARRAY STACK ===\n";
    ArrayStack arrayStack;
    cout << "1. Pop empty: " << (arrayStack.pop(removed) ? "success" : "failed (empty)") << '\n';
    arrayStack.push(10); cout << "2. Push 10\n";
    arrayStack.push(20); cout << "3. Push 20\n";
    arrayStack.push(30); cout << "4. Push 30\n";
    cout << "5. Peek: ";
    if (arrayStack.peek(peeked)) cout << peeked << '\n';
    cout << "6. Pop: ";
    if (arrayStack.pop(removed)) cout << removed << '\n';
    arrayStack.push(40); cout << "7. Push 40\n";
    arrayStack.push(50); cout << "8. Push 50\n";
    cout << "9. Pop: ";
    if (arrayStack.pop(removed)) cout << removed << '\n';
    cout << "10. Pop: ";
    if (arrayStack.pop(removed)) cout << removed << '\n';
    cout << "11. Pop: ";
    if (arrayStack.pop(removed)) cout << removed << '\n';
    cout << "12. Pop: "; if (arrayStack.pop(removed)) cout << removed << '\n';
    cout << "13. Pop empty: " << (arrayStack.pop(removed) ? "success" : "failed (empty)") << '\n';
    arrayStack.display();

    cout << "\n=== 2. LINKED-LIST STACK ===\n";
    LinkedStack linkedStack;
    cout << "1. Pop empty: " << (linkedStack.pop(removed) ? "success" : "failed (empty)") << '\n';
    linkedStack.push(100); cout << "2. Push 100\n";
    linkedStack.push(200); cout << "3. Push 200\n";
    linkedStack.push(300); cout << "4. Push 300\n";
    cout << "5. Peek: ";
    if (linkedStack.peek(peeked)) cout << peeked << '\n';
    cout << "6. Pop: ";
    if (linkedStack.pop(removed)) cout << removed << '\n';
    linkedStack.push(400); cout << "7. Push 400\n";
    linkedStack.push(500); cout << "8. Push 500\n";
    cout << "9. Pop: ";
    if (linkedStack.pop(removed)) cout << removed << '\n';
    cout << "10. Pop: ";
    if (linkedStack.pop(removed)) cout << removed << '\n';
    cout << "11. Pop: ";
    if (linkedStack.pop(removed)) cout << removed << '\n';
    cout << "12. Pop: "; if (linkedStack.pop(removed)) cout << removed << '\n';
    cout << "13. Pop empty: " << (linkedStack.pop(removed) ? "success" : "failed (empty)") << '\n';
    linkedStack.display();

    cout << "\n=== 3. ARRAY QUEUE (CIRCULAR ARRAY) ===\n";
    ArrayQueue arrayQueue;
    cout << "1. Dequeue empty: " << (arrayQueue.dequeue(removed) ? "success" : "failed (empty)") << '\n';
    arrayQueue.enqueue(10); cout << "2. Enqueue 10\n";
    arrayQueue.enqueue(20); cout << "3. Enqueue 20\n";
    arrayQueue.enqueue(30); cout << "4. Enqueue 30\n";
    cout << "5. Peek front: ";
    if (arrayQueue.peek(peeked)) cout << peeked << '\n';
    cout << "6. Dequeue: ";
    if (arrayQueue.dequeue(removed)) cout << removed << '\n';
    arrayQueue.enqueue(40); cout << "7. Enqueue 40\n";
    arrayQueue.enqueue(50); cout << "8. Enqueue 50\n";
    cout << "9. Dequeue: ";
    if (arrayQueue.dequeue(removed)) cout << removed << '\n';
    cout << "10. Dequeue: ";
    if (arrayQueue.dequeue(removed)) cout << removed << '\n';
    cout << "11. Dequeue: ";
    if (arrayQueue.dequeue(removed)) cout << removed << '\n';
    cout << "12. Dequeue: "; if (arrayQueue.dequeue(removed)) cout << removed << '\n';
    cout << "13. Dequeue empty: " << (arrayQueue.dequeue(removed) ? "success" : "failed (empty)") << '\n';
    arrayQueue.display();

    cout << "\n=== 4. LINKED-LIST QUEUE ===\n";
    LinkedQueue linkedQueue;
    cout << "1. Dequeue empty: " << (linkedQueue.dequeue(removed) ? "success" : "failed (empty)") << '\n';
    linkedQueue.enqueue(100); cout << "2. Enqueue 100\n";
    linkedQueue.enqueue(200); cout << "3. Enqueue 200\n";
    linkedQueue.enqueue(300); cout << "4. Enqueue 300\n";
    cout << "5. Peek front: ";
    if (linkedQueue.peek(peeked)) cout << peeked << '\n';
    cout << "6. Dequeue: ";
    if (linkedQueue.dequeue(removed)) cout << removed << '\n';
    linkedQueue.enqueue(400); cout << "7. Enqueue 400\n";
    linkedQueue.enqueue(500); cout << "8. Enqueue 500\n";
    cout << "9. Dequeue: ";
    if (linkedQueue.dequeue(removed)) cout << removed << '\n';
    cout << "10. Dequeue: ";
    if (linkedQueue.dequeue(removed)) cout << removed << '\n';
    cout << "11. Dequeue: ";
    if (linkedQueue.dequeue(removed)) cout << removed << '\n';
    cout << "12. Dequeue: "; if (linkedQueue.dequeue(removed)) cout << removed << '\n';
    cout << "13. Dequeue empty: " << (linkedQueue.dequeue(removed) ? "success" : "failed (empty)") << '\n';
    linkedQueue.display();

    cout << "\n=== 5. ARRAY DEQUE (CIRCULAR ARRAY) ===\n";
    ArrayDeque arrayDeque;
    cout << "1. Pop front empty: " << (arrayDeque.popFront(removed) ? "success" : "failed (empty)") << '\n';
    arrayDeque.pushBack(20); cout << "2. Push back 20\n";
    arrayDeque.pushBack(30); cout << "3. Push back 30\n";
    arrayDeque.pushFront(10); cout << "4. Push front 10\n";
    arrayDeque.pushFront(5); cout << "5. Push front 5\n";
    cout << "6. Pop back: ";
    if (arrayDeque.popBack(removed)) cout << removed << '\n';
    arrayDeque.pushBack(40); cout << "7. Push back 40\n";
    cout << "8. Pop front: ";
    if (arrayDeque.popFront(removed)) cout << removed << '\n';
    arrayDeque.pushFront(1); cout << "9. Push front 1\n";
    cout << "10. Pop back: ";
    if (arrayDeque.popBack(removed)) cout << removed << '\n';
    cout << "11. Pop front: ";
    if (arrayDeque.popFront(removed)) cout << removed << '\n';
    cout << "12. Pop front: ";
    if (arrayDeque.popFront(removed)) cout << removed << '\n';
    cout << "13. Pop front: "; if (arrayDeque.popFront(removed)) cout << removed << '\n';
    cout << "14. Pop front empty: " << (arrayDeque.popFront(removed) ? "success" : "failed (empty)") << '\n';
    arrayDeque.display();

    cout << "\n=== 6. LINKED-LIST DEQUE (DOUBLY LINKED LIST) ===\n";
    LinkedDeque linkedDeque;
    cout << "1. Pop back empty: " << (linkedDeque.popBack(removed) ? "success" : "failed (empty)") << '\n';
    linkedDeque.pushBack(200); cout << "2. Push back 200\n";
    linkedDeque.pushBack(300); cout << "3. Push back 300\n";
    linkedDeque.pushFront(100); cout << "4. Push front 100\n";
    linkedDeque.pushFront(50); cout << "5. Push front 50\n";
    cout << "6. Pop back: ";
    if (linkedDeque.popBack(removed)) cout << removed << '\n';
    linkedDeque.pushBack(400); cout << "7. Push back 400\n";
    cout << "8. Pop front: ";
    if (linkedDeque.popFront(removed)) cout << removed << '\n';
    linkedDeque.pushFront(10); cout << "9. Push front 10\n";
    cout << "10. Pop back: ";
    if (linkedDeque.popBack(removed)) cout << removed << '\n';
    cout << "11. Pop front: ";
    if (linkedDeque.popFront(removed)) cout << removed << '\n';
    cout << "12. Pop front: ";
    if (linkedDeque.popFront(removed)) cout << removed << '\n';
    cout << "13. Pop front: "; if (linkedDeque.popFront(removed)) cout << removed << '\n';
    cout << "14. Pop front empty: " << (linkedDeque.popFront(removed) ? "success" : "failed (empty)") << '\n';
    linkedDeque.display();

    return 0;
}
