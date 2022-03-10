// longest-substring-without-repeating.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using std::string;

int lengthOfLongestSubstring(string s)
{
	const int stringLength = s.length();
	int maxSubstringLength = 0;
	string sub;

	for (int k = 0; k < stringLength; k++)
	{
		for (int i = k; i < stringLength; i++)
		{
			char c = s[i];
			bool exist = false;

			for (int j = 0; j < sub.length(); j++)
			{
				if (c == sub[j])
				{
					exist = true;
					break;
				}
			}

			if (exist)
			{
				if (maxSubstringLength < sub.length())
				{
					maxSubstringLength = sub.length();
				}

				sub.clear();

				break;
			}

			sub.push_back(c);

			if (maxSubstringLength < sub.length())
			{
				maxSubstringLength = sub.length();
			}
		}
	}

	return maxSubstringLength;
}

int main()
{
	std::vector<std::string> list =
	{
		//"abcabcbb",
		//"abcdefgh",
		//"bbbbbbbb",
		//"pwwkew",
		//"dvdf",
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
