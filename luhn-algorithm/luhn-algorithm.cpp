// luhn-algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

int doubleDigitSum(int digit)
{
    int sum = 0;
    int doubleDigit = digit * 2;

    if (doubleDigit > 9)
    {
        sum = 1 + (doubleDigit % 10);
    }
    else
    {
        sum = doubleDigit;
    }

    return sum;
}

int luhnCheck()
{
    int position = 0;
    int checksum = 0;
    int evenSum = 0;
    int oddSum = 0;
    char digit = 0;
    int controlDigit = 0;

    digit = std::cin.get();

    while (digit != 10)
    {
        int number = digit - '0';

        if (position % 2 == 0)
        {
            oddSum += number;
            evenSum += doubleDigitSum(number);
        }
        else
        {
            oddSum += doubleDigitSum(number);
            evenSum += number;
        }

        position++;
        digit = std::cin.get();
    }

    checksum = (position % 2 == 0) ? evenSum : oddSum;

    std::cout << "Position = " << position << std::endl;
    std::cout << "OddSum = " << oddSum << std::endl;
    std::cout << "EvenSum = " << evenSum << std::endl;

    std::cout << "Checksum = " << checksum << std::endl;

    if (checksum % 10 == 0)
    {
        std::cout << "Valid";
    }
    else
    {
        std::cout << "Invalid";
    }

    controlDigit = 10 - (checksum % 10);

    return controlDigit;
}

int main()
{
    std::cout << "Control digit = " << luhnCheck() << std::endl;

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
