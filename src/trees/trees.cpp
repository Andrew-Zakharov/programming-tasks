#include <iostream>
#include <vector>

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

    bool isLeaf() const {
        return (left == nullptr) && (right == nullptr);
    }

    bool isNext(const Node* node) const {
        return (node == right) || (node == left);
    }

    int getData() const {
        return data;
    }

    void setData(int data) {
        this->data = data;
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

    Node* getParent(Node* node) {
        Node* current = root;
        int targetData = node->getData();

        if (node == root) {
            return nullptr;
        }

        while (current && !current->isNext(node)) {
            if (targetData > current->getData()) {
                current = current->getRight();
            }
            else if (targetData < current->getData()) {
                current = current->getLeft();
            }
        }

        return current;
    }

    Node* getSuccessor(Node* node) { // one step right, then left till null
        node = node->getRight();

        if (node && node->getLeft()) {
            node = node->getLeft();
        }

        return node;
    }

    Node* getPredecessor(Node* node) {
        node = node->getLeft();

        if (node && node->getRight()) {
            node = node->getRight();
        }

        return node;
    }

    void print_horizontally_recursive(const std::string& prefix, Node* node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            if (node == root) {
                std::cout << "---";
            }
            else {
                std::cout << (isLeft ? "L--" : "R--");
            }

            std::cout << node->getData() << std::endl;

            print_horizontally_recursive(prefix + (isLeft ? "|   " : "    "), node->getLeft(), true);
            print_horizontally_recursive(prefix + (isLeft ? "|   " : "    "), node->getRight(), false);
        }
    }

    void print() {
        print_horizontally_recursive("", root, false);
    }

    Node* remove_recursive(Node* root, int data) {
        if (!root) {
            return nullptr;
        }

        if (data > root->getData()) {
            root->setRight(remove_recursive(root->getRight(), data));
        }
        else if (data < root->getData()) {
            root->setLeft(remove_recursive(root->getLeft(), data));
        }
        else {
            if (root->getLeft() == nullptr) {
                Node* holder = root->getRight();
                delete root;
                return holder;
            }
            else if (root->getRight() == nullptr) {
                Node* holder = root->getLeft();
                delete root;
                return holder;
            }
            else {
                Node* successor = getSuccessor(root);

                root->setData(successor->getData());
                root->setRight(remove_recursive(root->getRight(), successor->getData()));
            }
        }
    }

    void remove_iterative(int data) {
        Node* current = root;
        Node* parent = nullptr;
        bool found = false;

        while (current && !found) {
            if (data > current->getData()) {
                parent = current;
                current = current->getRight();
            } 
            else if (data < current->getData()) {
                parent = current;
                current = current->getLeft();
            }
            else if (data == current->getData()) {
                found = true;
            }
        }

        if (found) {
            if (current->getRight() == nullptr) {
                if (parent == nullptr) {
                    root = current->getLeft();
                }
                else {
                    if (current->getData() < parent->getData()) {
                        parent->setLeft(current->getLeft());
                    }
                    else if (current->getData() > parent->getData()) {
                        parent->setRight(current->getLeft());
                    }
                }
            }
            else if (current->getLeft() == nullptr) {
                current->getRight()->setLeft(current->getLeft());
                if (parent == nullptr) {
                    root = current->getRight();
                }
                else {
                    if (current->getData() < parent->getData()) {
                        parent->setLeft(current->getRight());
                    }
                    else if(current->getData() > parent->getData()) {
                        parent->setRight(current->getRight());
                    }
                }
            }
            else {
                Node* successor = current->getRight()->getLeft();
                Node* successorParent = current->getRight();

                while (successor->getLeft() != nullptr) {
                    successorParent = successor;
                    successor = successor->getLeft();
                }

                successorParent->setLeft(successor->getRight());
                successor->setLeft(current->getLeft());
                successor->setRight(current->getRight());

                if (parent == nullptr) {
                    this->root = successor;
                }
                else {
                    if (current->getData() < parent->getData()) {
                        parent->setLeft(successor);
                    }
                    else if(current->getData() > parent->getData()) {
                        parent->setRight(successor);
                    }
                }
            }
        }
    }

    void inorder(Node* node, std::vector<int>& v) {
        if (!node) {
            return;
        }

        inorder(node->getLeft(), v);

        //std::cout << node->getData() << ' ';
        v.push_back(node->getData());

        inorder(node->getRight(), v);
    }

    std::vector<int> inorder() {
        std::vector<int> temp;

        inorder(root, temp);

        return temp;
    }

    void remove(int data) {
        root = remove_recursive(root, data);
    }

    bool isRoot(const Node* node) const {
        return node == root;
    }

private:
    Node* root = nullptr;
};

void test_bst() {
    BST b;

    std::vector<int> data = { 30, 40, 20, 37, 38, 25 };

    for (int n : data) {
        b.insert(n);
    }

    //std::vector<int> temp = b.inorder();

    //b.inorder();

    b.print();
    b.remove(30);


    b.print();

    std::cout << std::endl;

    b.remove(37);

    b.print();

    std::cout << std::endl;

    b.remove(40);

    b.print();

    std::cout << std::endl;

    b.remove(38);

    b.print();
}

int main() {
    test_bst();

    return 0;
}
