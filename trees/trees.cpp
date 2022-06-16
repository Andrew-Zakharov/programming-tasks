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

    void printBT(const std::string& prefix, Node* node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "L--" : "R--");

            // print the value of the node
            std::cout << node->getData() << std::endl;

            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "|   " : "    "), node->getLeft(), true);
            printBT(prefix + (isLeft ? "|   " : "    "), node->getRight(), false);
        }
    }

    void print(Node* node, int height) {

        for (int i = 0; i < height; i++) {
            std::cout << '\t';
        }

        std::cout << node->getData() << std::endl;

        if (node && node->getLeft()) {
            height++;
            print(node->getLeft(), height);
        }

        if (node && node->getRight()) {
            print(node->getRight(), height);
        }

        
    }

    void print() {
        int height = 0;
        Node* node = root;

        //print(node, height);
        printBT("", root, false);
    }

    Node* remove_recursive(Node* root, int data) {
        if (!root) {
            return nullptr;
        }

        if (data > root->getData()) {
            root = remove_recursive(root->getRight(), data);
        }
        else if (data < root->getData()) {
            root = remove_recursive(root->getLeft(), data);
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

    void remove(int data) {
        Node* exile = lookup(data);

        if (exile) {
            Node* successor = getSuccessor(exile);
            Node* predecessor = getPredecessor(exile);
            Node* parent = getParent(exile);
            
            if (isRoot(exile)) {
                if (successor) {
                    Node* successorParent = getParent(successor);

                    if (successorParent == exile) {
                        //successor->setRight(exile->getRight());
                        successor->setLeft(exile->getLeft());
                    }
                    else {
                        successorParent->setLeft(successor->getRight());
                        successor->setRight(exile->getRight());
                        successor->setLeft(exile->getLeft());
                    }
                    //successorParent->setLeft(successor->getRight());

                    root = successor;
                }
                else if (predecessor) {
                    Node* predecessorParent = getParent(predecessor);

                    if (predecessorParent == exile) {

                    }
                    else {
                        predecessorParent->setRight(predecessor->getLeft());

                        predecessor->setRight(exile->getRight());
                        predecessor->setLeft(exile->getLeft());
                    }

                    root = predecessor;
                }
                else {

                }
            }

            /*if (exile->isLeaf()) {
                if (parent->getRight() == exile) {
                    parent->setRight(nullptr);
                }

                if (parent->getLeft() == exile) {
                    parent->setLeft(nullptr);
                }
            }
            else if (exile->getRight() && !exile->getLeft()) {
                Node* successorParent = getParent(successor);

                successorParent->setLeft(successor->getLeft());

                if (parent->getRight() == exile) {
                    parent->setRight(successor);
                }

                if (parent->getLeft() == exile) {
                    parent->setLeft(successor);
                }

                successor->setLeft(exile->getLeft());
                successor->setRight(exile->getRight());
            }
            else if (!exile->getRight() && exile->getLeft()) {
                Node* predecessorParent = getParent(predecessor);

                predecessorParent->setLeft(predecessor->getLeft());

                if (parent->getRight() == exile) {
                    parent->setRight(predecessor);
                }

                if (parent->getLeft() == exile) {
                    parent->setLeft(predecessor);
                }

                predecessor->setLeft(exile->getLeft());
                predecessor->setRight(exile->getRight());
            }
            else {

            }*/

            delete exile;
        }
    }

    bool isRoot(const Node* node) const {
        return node == root;
    }

private:
    Node* root = nullptr;
};

void test_bst() {
    BST b;

    //std::vector<int> data = { 10, 20, 50, 60, 15, 17, 30, 40, 9, 6 };
    std::vector<int> data = { 30, 40, 20, 37, 38, 25 };

    /*b.insert(9);
    b.insert(20);
    b.insert(100);
    b.insert(4);
    b.insert(1);
    b.insert(15);
    b.insert(6);*/

    for (int n : data) {
        b.insert(n);
    }

    //b.insert()
    b.print();
   // b.remove(30);
   // b.remove(37);
   // b.remove(38);
   // b.remove(40);
    //b.remove(100);
    //Node* temp  = b.lookup(9);
}

int main() {
    test_bst();

    return 0;
}
