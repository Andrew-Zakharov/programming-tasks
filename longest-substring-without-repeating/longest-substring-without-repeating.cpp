// longest-substring-without-repeating.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::max;

bool allUnique(const string s, int start, int end)
{
	bool isUnique = true;

	vector<int> chars(128);

	for (int i = start; i < end; i++)
	{
		char c = s[i];
		chars[c]++;
		if (chars[c] > 1)
		{
			isUnique = false;
			break;
		}
	}

	return isUnique;
}

int lengthOfLongestSubstring(string s)
{
	const int stringLength = s.length();
	int subLength = 0;

	for (int i = 0; i < stringLength; i++)
	{
		for (int j = i; j < stringLength; j++)
		{
			if (allUnique(s, i, j))
			{
				subLength = max(subLength, j - i + 1);
			}
		}
	}

	return subLength;
}

int main()
{
	std::vector<std::string> list =
	{
		"abcabcbb",
		"abcdefgh",
		"bbbbbbbb",
		"pwwkew",
		"dvdf",
		"a"
	};

	for (std::string str : list)
	{
		std::cout << lengthOfLongestSubstring(str) << std::endl;
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
