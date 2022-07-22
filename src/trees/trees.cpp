#include <iostream>
#include <vector>
#include <tree.h>

void test_bst() {
    tree::BST b;

    std::vector<int> data = { 30, 40, 20, 37, 38, 25 };

    // Postorder:   25 20 38 37 40 30
    // Preorder:    30 20 25 40 37 38
    // Inorder:     20 25 30 37 38 40  

    for (int n : data) {
        b.insert(n);
    }

    /*tree::Node* founded = b.breadthFirstSearch_recursive(38);

    if(founded){
        std::cout << "Found: " << founded << std::endl;
    }*/

    tree::Node* founded = b.depthFirstSearch(tree::TraversalType::preorder, 37);

    if(founded){
        std::cout << founded << ", " << founded->getData() << std::endl; 
    }
}

int main() {
    test_bst();

    return 0;
}
