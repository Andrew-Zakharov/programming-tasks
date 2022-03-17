// string-to-integer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using std::string;


int myAtoi(string s)
{
	int number = 0;
	int sign = 1;
	int i = 0;
	int length = s.length();

	while (i < length && s[i] == ' ') i++;

	if (i < length && s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else
	{
		if (i < length && s[i] == '+')
		{
			sign = 1;
			i++;
		}
	}

	while (i < length && s[i] >= '0' && s[i] <= '9')
	{
		int digit = s[i] - '0';

		if ((number > INT_MAX / 10) || (number == INT_MAX / 10 && digit > INT_MAX % 10))
		{
			return sign == 1 ? INT_MAX : INT_MIN;
		}

		number = number * 10 + digit;
		i++;
	}

	number = number * sign;

	return number;
}

int main()
{
	std::vector<std::string> strings =
	{
		"42",
		"-42",
		"+-12",
		"2147483646"
	};

	for (std::string& str : strings)
	{
		std::cout << myAtoi(str) << std::endl;
	}

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
