#include <iostream>
#include <vector>
#include <tree.h>

void test_bst() {
    tree::BST b;

    std::vector<int> data = { 30, 40, 20, 37, 38, 25 };

    for (int n : data) {
        b.insert(n);
    }

    /*tree::Node* founded = b.breadthFirstSearch_recursive(38);

    if(founded){
        std::cout << "Found: " << founded << std::endl;
    }*/

    b.depthFirstSearch(tree::TraversalType::inorder, 0);
}

int main() {
    test_bst();

    return 0;
}
