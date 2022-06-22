#include <iostream>

int factorial_recursive(int number) {
    if (number == 1) {
        return number;
    }

    return number * factorial_recursive(number - 1);
}

int factorial_iterative(int number) {
    int result = 1;

    for (int i = number; i > 1; i--) {
        result *= i;
    }

    return result;
}

void test_factorial() {
    std::cout << factorial_recursive(10) << std::endl;
    std::cout << factorial_iterative(10) << std::endl;
}

int main()
{
    test_factorial();

    return 0;
}
