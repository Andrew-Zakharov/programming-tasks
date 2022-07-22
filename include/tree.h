#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

namespace tree {
    enum TraversalType{
        inorder = 0,
        preorder,
        postorder
    };


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
                        else if (current->getData() > parent->getData()) {
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
                        else if (current->getData() > parent->getData()) {
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

        Node* breadthFirstSearch(int data) {
            std::queue<Node*> q;

            Node* current = root;

            while(current){
                if(current->getData() == data){
                    break;
                }

                std::cout << current->getData() << std::endl;

                if(current->getLeft()){
                    q.push(current->getLeft());
                }

                if(current->getRight()){
                    q.push(current->getRight());
                }

                //current = current->getLeft();
                current = q.empty() ? nullptr : q.front();
                q.pop();
            }

            return root;
        }

        Node* breadthFirstSearch_recursive(int data){
            std::queue<Node*> q;

            q.push(root);

            return breadthFirstSearch_recursive(q, data);
        }

        Node* breadthFirstSearch_recursive(std::queue<Node*>& q, const int& data){
            if(q.empty()){
                return nullptr;
            }

            Node* current = q.front();
            q.pop();

            if(current->getData() == data){
                return current;
            }

            if(current->getLeft()){
                q.push(current->getLeft());
            }

            if(current->getRight()){
                q.push(current->getRight());
            }

            return breadthFirstSearch_recursive(q, data);
        }

        Node* depthFirstSearch_iterative_inorder(const int& data){
            std::stack<Node*> s;
            Node* current = nullptr;
            std::unordered_set<int> visited;

            s.push(root);

            while(!s.empty()){
                current = s.top();

                if(current->getLeft() && visited.find(current->getLeft()->getData()) == visited.end()){
                    s.push(current->getLeft());
                }
                else{
                    s.pop();
                    std::cout << current->getData() << std::endl;
                    visited.insert(current->getData());

                    if(current->getRight()){
                        s.push(current->getRight());
                    }
                }
            }

            return current;
        }

        Node* depthFirstSearch_recursive_inorder(Node* root, const int& data){
            if(!root){
                return nullptr;
            }

            if(root && root->getData() != data) {
                depthFirstSearch_recursive_inorder(root->getLeft(), data);

                std::cout << root->getData() << std::endl;

                depthFirstSearch_recursive_inorder(root->getRight(), data);
            }

            return root;
        }

        Node* depthFirstSearch_recursive_preorder(Node* root, const int& data){
            if(!root){
                return nullptr;
            }

            if(root->getData() == data){
                return root;
            }

            Node* founded = nullptr;

            std::cout << root->getData() << std::endl;

            if(root->getLeft())
                founded = depthFirstSearch_recursive_preorder(root->getLeft(), data);

            if(root->getRight())
                founded = depthFirstSearch_recursive_preorder(root->getRight(), data);

            return founded;
        }

        Node* depthFirstSearch_iterative_preorder(const int& data){
            std::unordered_set<int> visited;
            std::stack<Node*> s;
            Node* current = nullptr;

            s.push(root);

            while(!s.empty()){
                current = s.top();
                s.pop();
                std::cout << current->getData() << std::endl;

                if(current->getRight()){
                    s.push(current->getRight());
                }

                if(current->getLeft()){
                    s.push(current->getLeft());
                }
            }

            return current;
        }

        Node* depthFirstSearch_iterative_postorder(const int& data){
            Node* current = nullptr;
            std::unordered_set<int> visited;
            std::stack<Node*> s;
            Node* right, *left;

            s.push(root);

            while(!s.empty()){
                current = s.top();
                right = current->getRight();
                left = current->getLeft();

                if(right){
                    if(visited.find(right->getData()) != visited.end()){
                        right = nullptr;
                    }
                    else{
                        s.push(right);
                    }
                }

                if(left){
                    if(visited.find(left->getData()) != visited.end()){
                        left = nullptr;
                    }
                    else{
                        s.push(left);
                    }
                    
                }

                if(!left && !right){
                    std::cout << current->getData() << std::endl;
                    s.pop();
                    visited.insert(current->getData());
                }
            }

            return current;
        }

        Node* depthFirstSearch(TraversalType type, const int& data){
            Node* founded = nullptr;

            switch(type){
                case TraversalType::inorder:{
                    founded = depthFirstSearch_recursive_inorder(root, data);
                }break;

                case TraversalType::preorder:{
                    founded = depthFirstSearch_recursive_preorder(root, data);
                }break;

                case TraversalType::postorder:{
                    founded = depthFirstSearch_iterative_postorder(data);
                }break;
            }

            return founded;
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
}