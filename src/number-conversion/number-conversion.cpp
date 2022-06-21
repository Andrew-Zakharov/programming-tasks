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

std::vector<char> binaryToHex(const std::vector<int>& binary)
{
    std::vector<char> hex{ 0 };
    std::vector<std::vector<int>> groups{ 0 };
    constexpr int GROUP_LENGTH = 4;
    std::vector<int> group;
    size_t count = 0;

    for (auto it = binary.crbegin(); it != binary.crend(); it++)
    {
        group.push_back(*it);
        count++;

        if (count == GROUP_LENGTH)
        {
            groups.push_back(std::vector<int>(group.crbegin(), group.crend()));
            group.clear();
            count = 0;
        }
    }


    for (int i = group.size(); i < GROUP_LENGTH; i++)
    {
        group.push_back(0);
    }

    groups.push_back(std::vector<int>(group.crbegin(), group.crend()));

    for (auto group : groups)
    {
        int digit = binaryToDecimal(group);

        switch (digit)
        {
            case 10:
            {
                hex.push_back('A');
            }break;

            case 11:
            {
                hex.push_back('B');
            }break;

            case 12:
            {
                hex.push_back('C');
            }break;


            case 13:
            {
                hex.push_back('D');
            }break;

            case 14:
            {
                hex.push_back('E');
            }break;

            case 15:
            {
                hex.push_back('F');
            }break;

            default:
            {
                hex.push_back((char)(digit + '0'));
            }
        }
    }

    return hex;
}

void testDecimalToBinary()
{
    std::vector<int> binary = decimalToBinary(110);

    for (auto bit : binary)
    {
        std::cout << bit;
    }

    std::cout << std::endl;
}

void testBinaryToDecimal()
{
    std::vector<int> binary = { 0, 1, 1, 1, 1, 1, 1, 0 };

    std::cout << binaryToDecimal(binary) << std::endl;
}

void testBinaryToHex()
{
    std::vector<int> binary = { 1, 0, 1, 0, 1 };

    binaryToHex(binary);
}

int main()
{
    testBinaryToHex();

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
