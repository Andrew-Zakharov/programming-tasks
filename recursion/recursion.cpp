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

int fibonacci_recursive(int index) {
    if (index < 2) {
        return index;
    }

    return fibonacci_recursive(index - 1) + fibonacci_recursive(index - 2);
}

int fibonacci_iterative(int index) {
    int first = 0;
    int second = 1;
    int sum = 0;

    for (int i = 0; i < index; i++) {
        sum = first + second;

        first = second;
        second = sum;
    }

    return first;
}

void test_factorial() {
    std::cout << factorial_recursive(10) << std::endl;
    std::cout << factorial_iterative(10) << std::endl;
}

int main()
{
    //test_factorial();

    std::cout << fibonacci_recursive(15) << std::endl;
    std::cout << fibonacci_iterative(15) << std::endl;

    return 0;
}
