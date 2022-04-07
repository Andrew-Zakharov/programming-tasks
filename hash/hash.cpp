#include <iostream>
#include <string>
#include <algorithm>

constexpr int getPrimeNumber()
{
    return 31;
}

int hash(const std::string& str)
{
    int hash = 0;
    constexpr int PRIME = getPrimeNumber();

    for (int i = 0; i < str.length(); i++)
    {
        hash += str[i] * std::pow(PRIME, i);
    }

    return hash;
}

int main()
{
    std::cout << hash("abcde") << std::endl;

    return 0;
}
