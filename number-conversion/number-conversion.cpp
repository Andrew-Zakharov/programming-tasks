// number-conversion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>

std::vector<int> decimalToBinary(int decimal)
{
    std::vector<int> binary;

    int remainder = 0;
    int result = decimal;

    do
    {
        remainder = result % 2;
        result /= 2;

        binary.push_back(remainder);
    } while (result);

    return std::vector<int>(binary.crbegin(), binary.crend());
}

int binaryToDecimal(std::vector<int> binary)
{
    int decimal = 0;
    int rank = 0;

    for (auto it = binary.crbegin(); it != binary.crend(); it++)
    {
        decimal += *it * std::pow(2, rank);
        rank++;
    }

    return decimal;
}

int main()
{
    std::vector<int> binary = decimalToBinary(110);
    
    for (auto bit : binary)
    {
        std::cout << bit;
    }

    std::cout << std::endl;

    std::cout << binaryToDecimal(binary);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
