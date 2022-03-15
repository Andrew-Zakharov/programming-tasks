// longest-substring-without-repeating.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::max;

int lengthOfLongestSubstring(string s)
{
	int subLength = 0;
	vector<int> chars(128, -1);

	int right = 0, left = 0;

	while (right < s.length())
	{
		char r = s[right];

		int index = chars[r];

		if (index != -1 && index >= left && index < right)
		{
			left = index + 1;
		}

		subLength = max(subLength, right - left + 1);

		chars[r] = right;
		right++;
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
