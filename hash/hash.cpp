#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <vector>
#include <cstddef>

namespace MD5
{
    constexpr int WORD_LENGTH = 32;
    constexpr size_t BYTE_LENGTH = 8;
    constexpr size_t MAX_MESSAGE_LENGTH = 64;

    typedef std::bitset<BYTE_LENGTH> BYTE;


    enum class MIXING_ROUND
    {
        F = 0,
        G,
        H,
        I,
        
        COUNT
    };

    class Message
    {
        public:
            Message(const std::string& source) : source(source)
            {
                length = source.length();
            }

            ~Message()
            {

            }
                
            std::vector<BYTE> convert()
            {
                std::vector<BYTE> bytes;

                for (auto c : source)
                {
                    bytes.push_back(BYTE(c));
                }

                return bytes;
            }

            bool isPadded(const size_t sizeInBytes)
            {
                return ((sizeInBytes * BYTE_LENGTH + MAX_MESSAGE_LENGTH) % 512 == 0);
            }

            std::vector<BYTE> pad()
            {
                std::vector<BYTE> paddedMessage;

                paddedMessage = convert();

                paddedMessage.push_back(0b1);

                while (!isPadded(paddedMessage.size()))
                {
                    paddedMessage.push_back(0b0);
                }

                BYTE temp;
                size_t j = 0;
                for (size_t i = 0; i < length.size(); i++)
                {
                    temp[j] = length[i];
                    j++;

                    if (j == BYTE_LENGTH)
                    {
                        paddedMessage.push_back(temp);

                        j = 0;
                        temp.reset();
                    }
                }

                return paddedMessage;
            }

        private:
            std::string source;
            std::bitset<MAX_MESSAGE_LENGTH> length;
    };

    class Algorithm
    {
        public:
            Algorithm() : A(0x67452301), B(0xefcdab89), C(0x98badcfe), D(0x10325476)
            {

            }

            std::bitset<WORD_LENGTH> mix(MIXING_ROUND round)
            {
                std::bitset<WORD_LENGTH> result;

                switch (round)
                {
                    case MIXING_ROUND::F:
                    {
                        result = (B & C) | ((~B) & D);
                    }break;

                    case MIXING_ROUND::G:
                    {
                        result = (B & D) | (C & (~D));
                    }break;

                    case MIXING_ROUND::H:
                    {
                        result = B ^ C ^ D;
                    }break;

                    case MIXING_ROUND::I:
                    {
                        result = B ^ (B | (~D));
                    }break;
                }

                return result;
            }

            

        private:
            std::bitset<WORD_LENGTH> A;
            std::bitset<WORD_LENGTH> B;
            std::bitset<WORD_LENGTH> C;
            std::bitset<WORD_LENGTH> D;
    };
}

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

void testMessageConversion()
{
    std::vector<std::bitset<8>> result;

    MD5::Message msg("abcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    result = msg.pad();

    for (auto b : result)
    {
        std::cout << b;
    }
}

int main()
{
    //std::cout << hash("abcde") << std::endl;

    testMessageConversion();

    return 0;
}
