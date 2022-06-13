#include <iostream>

class Node {
public:
    Node(int data) : data(data) {

    }

    ~Node() {

    }

    Node* getLeft() {
        return left;
    }

    Node* getRight() {
        return right;
    }

    void setLeft(Node* left) {
        this->left = left;
    }

    void setRight(Node* right) {
        this->right = right;
    }

    void setChild(Node* child) {
        int childData = child->getData();

        if (childData > data) {
            this->setRight(child);
        }

        if (childData < data) {
            this->setLeft(child);
        }
    }

    int getData() {
        return data;
    }

private:
    int data = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

class BST {
public:
    BST() {

    }

    ~BST() {

    }

    void insert(int data) {
        Node* newNode = new Node(data);

        if (root) {
            traverse(root, data)->setChild(newNode);
        }
        else {
            root = newNode;
        }
    }

    Node* traverse(Node* node, int data) {
        int nodeData = node->getData();

        if (data < nodeData && node->getLeft()) {
            return traverse(node->getLeft(), data);
        }

        if (data > nodeData && node->getRight()) {
            return traverse(node->getRight(), data);
        }

        return node;
    }

    Node* lookup(int data) {
        Node* current = root;

        while (current && (current->getData() != data)) {
            if (data > current->getData()) {
                current = current->getRight();
            }

            if (data < current->getData()) {
                current = current->getLeft();
            }
        }

        return current;
    }

private:
    Node* root = nullptr;
};

void test_bst() {
    BST b;

    b.insert(9);
    b.insert(20);
    b.insert(170);
    b.insert(4);
    b.insert(1);
    b.insert(15);
    b.insert(6);

    Node* temp  = b.lookup(9);
}

int main() {
    test_bst();

    return 0;
}
