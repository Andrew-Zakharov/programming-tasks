// decode-message.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

enum class STATE_TYPE
{
    UPPER_CASE = 0,
    LOWER_CASE,
    PUNCTUATION
};

class DecodingMachine
{
    public:
        DecodingMachine() : state(STATE_TYPE::UPPER_CASE)
        {

        }

        ~DecodingMachine()
        {

        }

        void decodeNumber(int number)
        {
            switch (state)
            {
                case STATE_TYPE::UPPER_CASE:
                {
                    int mod = number % 27;

                    if (mod == 0)
                    {
                        state = STATE_TYPE::LOWER_CASE;
                        break;
                    }

                    decodedMessage.push_back(('A' - 1) + mod);
                }break;

                case STATE_TYPE::LOWER_CASE:
                {
                    int mod = number % 27;

                    if (mod == 0)
                    {
                        state = STATE_TYPE::PUNCTUATION;
                        break;
                    }

                    decodedMessage.push_back(('a' - 1) + mod);
                }break;

                case STATE_TYPE::PUNCTUATION:
                {
                    int mod = number % 9;

                    if (mod == 0)
                    {
                        state = STATE_TYPE::UPPER_CASE;
                        break;
                    }

                    decodedMessage.push_back(getPunctuationSymbol(mod - 1));
                }break;
            }
        }

        std::string getDecodedMessage() const
        {
            return decodedMessage;
        }

    private:
        char getPunctuationSymbol(int index)
        {
            std::vector<char> symbols =
            {
                '!', '?', ',', '.', ' ', ';', '\"', '\''
            };

            return symbols.at(index);
        }
    private:
        STATE_TYPE state;
        std::string decodedMessage;
};

void test()
{
    std::vector<int> encodedMessage =
    {
        18, 12312, 171, 763, 98423, 1208, 216, 11, 500, 18, 241, 0, 32, 20620, 27, 10
    };

    DecodingMachine machine;

    for (int i = 0; i < encodedMessage.size(); i++)
    {
        machine.decodeNumber(encodedMessage.at(i));
    }

    std::cout << machine.getDecodedMessage() << std::endl;
}

int strToInt(const std::string& str)
{
    int number = 0;
    int digit = 0;

    for (std::string::const_iterator it = str.cbegin(); it != str.cend(); it++)
    {
        digit = ((*it) - '0');
        number = number * 10 + digit;
    }

    return number;
}

void getNumbers(const std::string& str, std::vector<int>& numbers)
{
    int p1 = 0, p2 = 0;

    if (str.empty())
        return;

    while (str[p2] != ',' && p2 < str.size())
    {
        p2++;
    }
    
    numbers.push_back(strToInt(str.substr(0, p2)));

    p2++;

    if (p2 > str.size())
        return;

    getNumbers(str.substr(p2), numbers);
}

std::vector<int> getNumbers(const std::string& str)
{
    std::vector<int> numbers;
    int n = 0;

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ',')
        {
            numbers.push_back(n);
            n = 0;
            continue;
        }

        if (str[i] >= '0' && str[i] <= '9')
        {
            n = n * 10 + (str[i] - '0');
        }
    }

    numbers.push_back(n);

    return numbers;
}

std::string decodeMessage(const std::vector<int>& numbers)
{
    DecodingMachine machine;

    for (int n : numbers)
    {
        machine.decodeNumber(n);
    }

    return machine.getDecodedMessage();
}

int main()
{
    std::string str;
        
    std::getline(std::cin, str);

    std::vector<int> numbers;

    numbers = getNumbers(str);

    /*for (int n : numbers)
    {
        std::cout << n << std::endl;
    }*/

    std::cout << decodeMessage(numbers) << std::endl;

    //std::cout << str << std::endl;

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
