#include <iostream>
#include <vector>
#include <tree.h>

void test_bst() {
    tree::BST b;

    std::vector<int> data = { 30, 40, 20, 37, 38, 25 };

    for (int n : data) {
        b.insert(n);
    }

    tree::Node* founded = b.breadthFirstSearch(90);
}

int main() {
    test_bst();

    return 0;
}
