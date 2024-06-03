#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

std::string generateRandomString() {
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    int length = rand() % 5 + 1;
    for (int i = 0; i < length; i++) {
        result += chars[rand() % chars.length()];
    }
    return result;
}


struct Node {
    std::string data;
    Node* next;
    Node(std::string value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
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

    void add(std::string value) {
        Node* newNode = new Node(value);
        if (!head || head->data > value) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && current->next->data <= value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void remove(std::string value) {
        if (!head) return;
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    bool search(std::string value) {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    void print() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void fillRandom(int n) {
        for (int i = 0; i < n; i++) {
            add(generateRandomString());
        }
    }
};


class ArrayList {
private:
    std::vector<std::string> list;
public:
    void add(std::string value) {
        list.push_back(value);
        std::sort(list.begin(), list.end());
    }

    void remove(std::string value) {
        auto it = std::find(list.begin(), list.end(), value);
        if (it != list.end()) {
            list.erase(it);
        }
    }

    bool search(std::string value) {
        return std::binary_search(list.begin(), list.end(), value);
    }

    void print() {
        for (const auto& val : list) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    void fillRandom(int n) {
        for (int i = 0; i < n; i++) {
            add(generateRandomString());
        }
    }
};


struct BSTNode {
    std::string data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(std::string value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    BSTNode* root;

    BSTNode* add(BSTNode* node, std::string value) {
        if (!node) return new BSTNode(value);
        if (value < node->data) {
            node->left = add(node->left, value);
        }
        else {
            node->right = add(node->right, value);
        }
        return node;
    }

    BSTNode* remove(BSTNode* node, std::string value) {
        if (!node) return nullptr;
        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            if (!node->left) {
                BSTNode* rightNode = node->right;
                delete node;
                return rightNode;
            }
            if (!node->right) {
                BSTNode* leftNode = node->left;
                delete node;
                return leftNode;
            }
            BSTNode* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = remove(node->right, minNode->data);
        }
        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    bool search(BSTNode* node, std::string value) {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    void inorder(BSTNode* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        deleteTree(root);
    }

    void deleteTree(BSTNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void add(std::string value) {
        root = add(root, value);
    }

    void remove(std::string value) {
        root = remove(root, value);
    }

    bool search(std::string value) {
        return search(root, value);
    }

    void print() {
        inorder(root);
        std::cout << std::endl;
    }

    void fillRandom(int n) {
        for (int i = 0; i < n; i++) {
            add(generateRandomString());
        }
    }
};

struct AVLNode {
    std::string data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(std::string value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* balance(AVLNode* node) {
        updateHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode* add(AVLNode* node, std::string value) {
        if (!node) return new AVLNode(value);
        if (value < node->data) {
            node->left = add(node->left, value);
        }
        else {
            node->right = add(node->right, value);
        }
        return balance(node);
    }

    AVLNode* remove(AVLNode* node, std::string value) {
        if (!node) return nullptr;
        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            if (!node->left) {
                AVLNode* rightNode = node->right;
                delete node;
                return rightNode;
            }
            if (!node->right) {
                AVLNode* leftNode = node->left;
                delete node;
                return leftNode;
            }
            AVLNode* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = remove(node->right, minNode->data);
        }
        return balance(node);
    }

    AVLNode* findMin(AVLNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    bool search(AVLNode* node, std::string value) {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    void inorder(AVLNode* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }

    void deleteTree(AVLNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void add(std::string value) {
        root = add(root, value);
    }

    void remove(std::string value) {
        root = remove(root, value);
    }

    bool search(std::string value) {
        return search(root, value);
    }

    void print() {
        inorder(root);
        std::cout << std::endl;
    }

    void fillRandom(int n) {
        for (int i = 0; i < n; i++) {
            add(generateRandomString());
        }
    }
};


struct TTNode {
    std::string data1, data2;
    TTNode* left;
    TTNode* middle;
    TTNode* right;
    TTNode* parent;

    TTNode(std::string value) : data1(value), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}

    bool isLeaf() {
        return left == nullptr && middle == nullptr && right == nullptr;
    }

    bool hasTwoKeys() {
        return !data2.empty();
    }

    bool hasOneKey() {
        return !data1.empty() && data2.empty();
    }
};

class TwoThreeTree {
private:
    TTNode* root;

    void insertIntoNode(TTNode* node, const std::string& value, TTNode* left, TTNode* right) {
        if (node->data1.empty()) {
            node->data1 = value;
            node->left = left;
            node->middle = right;
        }
        else if (value < node->data1) {
            node->data2 = node->data1;
            node->data1 = value;
            node->right = node->middle;
            node->left = left;
            node->middle = right;
        }
        else {
            node->data2 = value;
            node->middle = left;
            node->right = right;
        }

        if (left) left->parent = node;
        if (right) right->parent = node;
    }

    void split(TTNode* node) {
        TTNode* parent = node->parent;
        TTNode* left = new TTNode(node->data1);
        TTNode* right = new TTNode(node->data2);

        left->left = node->left;
        left->middle = node->middle;
        right->left = node->middle;
        right->middle = node->right;

        if (left->left) left->left->parent = left;
        if (left->middle) left->middle->parent = left;
        if (right->left) right->left->parent = right;
        if (right->middle) right->middle->parent = right;

        if (parent) {
            insertIntoNode(parent, node->data1, left, right);
            if (parent->hasTwoKeys()) split(parent);
        }
        else {
            root = new TTNode(node->data1);
            root->left = left;
            root->middle = right;
            left->parent = root;
            right->parent = root;
        }

        delete node;
    }

    void insert(TTNode* node, const std::string& value) {
        if (node->isLeaf()) {
            insertIntoNode(node, value, nullptr, nullptr);
            if (node->hasTwoKeys()) split(node);
        }
        else {
            if (value < node->data1) {
                insert(node->left, value);
            }
            else if (!node->data2.empty() && value < node->data2) {
                insert(node->middle, value);
            }
            else {
                insert(node->right, value);
            }
        }
    }

    TTNode* findMin(TTNode* node) {
        while (!node->isLeaf()) {
            node = node->left;
        }
        return node;
    }

    void merge(TTNode* parent, TTNode* left, TTNode* right) {
        if (parent->data1 == left->data1) {
            parent->data1 = parent->data2;
            parent->data2.clear();
            parent->left = right;
            parent->middle = nullptr;
        }
        else {
            parent->data2.clear();
            parent->middle = nullptr;
            parent->right = right;
        }

        delete left;
    }

    void fix(TTNode* node) {
        if (node->parent == nullptr) {
            if (node->left && node->left->hasOneKey()) {
                TTNode* left = node->left;
                TTNode* right = node->middle;

                node->data1 = right->data1;
                node->left = left->left;
                node->middle = left->middle;
                node->right = right->middle;

                delete left;
                delete right;
            }
            return;
        }

        TTNode* parent = node->parent;

        if (parent->left == node) {
            TTNode* sibling = parent->middle;

            if (sibling->hasTwoKeys()) {
                node->data1 = parent->data1;
                parent->data1 = sibling->data1;
                sibling->data1 = sibling->data2;
                sibling->data2.clear();

                node->middle = sibling->left;
                sibling->left = sibling->middle;
                sibling->middle = sibling->right;
                sibling->right = nullptr;
            }
            else {
                merge(parent, node, sibling);
                fix(parent);
            }
        }
        else if (parent->middle == node) {
            TTNode* sibling = parent->left;

            if (sibling->hasTwoKeys()) {
                node->data1 = parent->data1;
                parent->data1 = sibling->data2;
                sibling->data2.clear();

                node->middle = node->left;
                node->left = sibling->right;
                sibling->right = nullptr;
            }
            else {
                merge(parent, sibling, node);
                fix(parent);
            }
        }
        else {
            TTNode* sibling = parent->middle;

            if (sibling->hasTwoKeys()) {
                node->data1 = parent->data2;
                parent->data2 = sibling->data2;
                sibling->data2.clear();

                node->middle = node->left;
                node->left = sibling->right;
                sibling->right = nullptr;
            }
            else {
                merge(parent, sibling, node);
                fix(parent);
            }
        }
    }

    void remove(TTNode* node, const std::string& value) {
        if (node->isLeaf()) {
            if (node->data1 == value) {
                node->data1.clear();
            }
            else if (node->data2 == value) {
                node->data2.clear();
            }
            fix(node);
        }
        else {
            if (value < node->data1) {
                remove(node->left, value);
            }
            else if (node->data2.empty() || value < node->data2) {
                remove(node->middle, value);
            }
            else {
                remove(node->right, value);
            }
        }
    }

    bool search(TTNode* node, const std::string& value) {
        if (!node) return false;
        if (node->data1 == value || node->data2 == value) return true;
        if (value < node->data1) {
            return search(node->left, value);
        }
        else if (node->data2.empty() || value < node->data2) {
            return search(node->middle, value);
        }
        else {
            return search(node->right, value);
        }
    }

    void inorder(TTNode* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->data1 << " ";
            inorder(node->middle);
            if (!node->data2.empty()) {
                std::cout << node->data2 << " ";
                inorder(node->right);
            }
        }
    }

public:
    TwoThreeTree() : root(nullptr) {}

    ~TwoThreeTree() {
        deleteTree(root);
    }

    void deleteTree(TTNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->middle);
            deleteTree(node->right);
            delete node;
        }
    }

    void add(std::string value) {
        if (root == nullptr) {
            root = new TTNode(value);
        }
        else {
            insert(root, value);
        }
    }

    void remove(std::string value) {
        if (root == nullptr) return;
        remove(root, value);
        if (root && root->data1.empty() && root->data2.empty()) {
            TTNode* oldRoot = root;
            if (root->left) {
                root = root->left;
                root->parent = nullptr;
            }
            else if (root->middle) {
                root = root->middle;
                root->parent = nullptr;
            }
            else if (root->right) {
                root = root->right;
                root->parent = nullptr;
            }
            else {
                root = nullptr;
            }
            delete oldRoot;
        }
    }

    bool search(std::string value) {
        return search(root, value);
    }

    void print() {
        inorder(root);
        std::cout << std::endl;
    }

    void fillRandom(int n) {
        for (int i = 0; i < n; i++) {
            add(generateRandomString());
        }
    }
};


void benchmark() {
    LinkedList linkedList;
    ArrayList arrayList;
    BinarySearchTree bst;
    AVLTree avl;
    TwoThreeTree tt;

    int n = 10000;
    std::cout << "Benchmarking with " << n << " elements...\n";

    auto start = std::chrono::high_resolution_clock::now();
    linkedList.fillRandom(n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "LinkedList fillRandom: " << duration.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    arrayList.fillRandom(n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "ArrayList fillRandom: " << duration.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    bst.fillRandom(n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "BinarySearchTree fillRandom: " << duration.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    avl.fillRandom(n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "AVLTree fillRandom: " << duration.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    tt.fillRandom(n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "TwoThreeTree fillRandom: " << duration.count() << " seconds\n";
}

void demo() {
    LinkedList linkedList;
    ArrayList arrayList;
    BinarySearchTree bst;
    AVLTree avl;
    TwoThreeTree tt;

    linkedList.add("B");
    linkedList.add("A");
    linkedList.add("C");
    linkedList.print(); 
    linkedList.remove("B");
    linkedList.print();

    arrayList.add("B");
    arrayList.add("A");
    arrayList.add("C");
    arrayList.print(); 
    arrayList.remove("B");
    arrayList.print(); 

    bst.add("B");
    bst.add("A");
    bst.add("C");
    bst.print();
    bst.remove("B");
    bst.print(); 

    avl.add("B");
    avl.add("A");
    avl.add("C");
    avl.print();
    avl.remove("B");
    avl.print();

    tt.add("B");
    tt.add("A");
    tt.add("C");
    tt.print(); 
    tt.remove("B");
    tt.print();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    LinkedList linkedList;
    ArrayList arrayList;
    BinarySearchTree bst;
    AVLTree avl;
    TwoThreeTree tt;

    int choice;
    std::string value;
    while (true) {
        std::cout << "1. Add\n2. Remove\n3. Search\n4. Print\n5. Fill random\n6. Demo\n7. Benchmark\n8. Exit\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "Enter value to add: ";
            std::cin >> value;
            linkedList.add(value);
            arrayList.add(value);
            bst.add(value);
            avl.add(value);
            tt.add(value);
            break;
        case 2:
            std::cout << "Enter value to remove: ";
            std::cin >> value;
            linkedList.remove(value);
            arrayList.remove(value);
            bst.remove(value);
            avl.remove(value);
            tt.remove(value);
            break;
        case 3:
            std::cout << "Enter value to search: ";
            std::cin >> value;
            std::cout << "LinkedList: " << (linkedList.search(value) ? "Found" : "Not found") << "\n";
            std::cout << "ArrayList: " << (arrayList.search(value) ? "Found" : "Not found") << "\n";
            std::cout << "BST: " << (bst.search(value) ? "Found" : "Not found") << "\n";
            std::cout << "AVL: " << (avl.search(value) ? "Found" : "Not found") << "\n";
            std::cout << "2-3 Tree: " << (tt.search(value) ? "Found" : "Not found") << "\n";
            break;
        case 4:
            std::cout << "LinkedList: "; linkedList.print();
            std::cout << "ArrayList: "; arrayList.print();
            std::cout << "BST: "; bst.print();
            std::cout << "AVL: "; avl.print();
            std::cout << "2-3 Tree: "; tt.print();
            break;
        case 5:
            int n;
            std::cout << "Enter number of random values: ";
            std::cin >> n;
            linkedList.fillRandom(n);
            arrayList.fillRandom(n);
            bst.fillRandom(n);
            avl.fillRandom(n);
            tt.fillRandom(n);
            break;
        case 6:
            demo();
            break;
        case 7:
            benchmark();
            break;
        case 8:
            return 0;
        }
    }

    return 0;
}
