#include <iostream>
using namespace std;

// ============ LINKED LIST ============
class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void pushBack(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
    }

    void pushFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    bool remove(int val) {
        if (!head) return false;
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        Node* curr = head;
        while (curr->next && curr->next->data != val) curr = curr->next;
        if (curr->next) {
            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;
            return true;
        }
        return false;
    }

    void display() {
        Node* curr = head;
        cout << "LinkedList: ";
        while (curr) {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "NULL\n";
    }
};

// ============ STACK ============
class Stack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* top;
    int count;

public:
    Stack() : top(nullptr), count(0) {}

    ~Stack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        count++;
    }

    bool pop() {
        if (!top) return false;
        Node* temp = top;
        top = top->next;
        delete temp;
        count--;
        return true;
    }

    int peek() {
        if (!top) throw runtime_error("Stack is empty");
        return top->data;
    }

    bool isEmpty() { return top == nullptr; }
    int size() { return count; }

    void display() {
        Node* curr = top;
        cout << "Stack (top -> bottom): ";
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

// ============ QUEUE ============
class Queue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    ~Queue() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    bool dequeue() {
        if (!front) return false;
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        count--;
        return true;
    }

    int peekFront() {
        if (!front) throw runtime_error("Queue is empty");
        return front->data;
    }

    bool isEmpty() { return front == nullptr; }
    int size() { return count; }

    void display() {
        Node* curr = front;
        cout << "Queue (front -> rear): ";
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

// ============ BINARY SEARCH TREE ============
class BinaryTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insertHelper(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insertHelper(node->left, val);
        else if (val > node->data) node->right = insertHelper(node->right, val);
        return node;
    }

    void inorderHelper(Node* node) {
        if (!node) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    bool searchHelper(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        if (val < node->data) return searchHelper(node->left, val);
        return searchHelper(node->right, val);
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* removeHelper(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->data) {
            node->left = removeHelper(node->left, val);
        } else if (val > node->data) {
            node->right = removeHelper(node->right, val);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = removeHelper(node->right, successor->data);
        }
        return node;
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroy(root); }

    void insert(int val) { root = insertHelper(root, val); }
    bool search(int val) { return searchHelper(root, val); }
    void remove(int val) { root = removeHelper(root, val); }

    void displayInorder() {
        cout << "BST (inorder): ";
        inorderHelper(root);
        cout << endl;
    }
};

int main() {
    cout << "===== Linked List Demo =====\n";
    LinkedList list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushFront(5);
    list.display();
    list.remove(20);
    list.display();

    cout << "\n===== Stack Demo =====\n";
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.display();
    cout << "Peek: " << stack.peek() << endl;
    stack.pop();
    stack.display();

    cout << "\n===== Queue Demo =====\n";
    Queue queue;
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    queue.display();
    cout << "Front: " << queue.peekFront() << endl;
    queue.dequeue();
    queue.display();

    cout << "\n===== Binary Search Tree Demo =====\n";
    BinaryTree tree;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) tree.insert(v);
    tree.displayInorder();
    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    tree.remove(30);
    cout << "After removing 30: ";
    tree.displayInorder();

    return 0;
}
