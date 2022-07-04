#include <iostream>
#include <vector>
#include <tree.h>

void test_bst() {
    tree::BST b;

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
