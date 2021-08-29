// group-anagrams.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) 
{
    return std::vector<std::vector<std::string>>();
}

int hash(const std::string& str1, const std::string& str2)
{
    int hash = 0;

    if (str1.length() == str2.length())
    {
        for (size_t i = 0; i < str1.length(); i++)
        {
            hash ^= str1[i];
            hash ^= str2[i];
        }
    }

    return hash;
}

int main()
{
    std::vector<std::string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };

    std::vector<std::vector<std::string>> groups;

    for (size_t i = 0; i < strs.size(); i++)
    {
        std::vector<std::string> group;

        group.push_back(strs[i]);

        for (size_t j = i + 1; j < strs.size(); j++)
        {
            //std::cout << "hash(" << strs[i] << ", " << strs[j] << ") = " << hash(strs[i], strs[j]) << std::endl;

            if (!hash(strs[i], strs[j]))
            {
                group.push_back(strs[j]);
            }
        }

        groups.push_back(group);
    }

    for (auto group : groups)
    {
        std::cout << "[ ";
        for (auto string : group)
        {
            std::cout << string << ", ";
        }

        std::cout << "]" << std::endl;
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
