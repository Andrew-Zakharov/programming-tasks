#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <vector>
#include <cstddef>
#include <limits>

void printBinary(const std::vector<char>& bytes)
{
    for (char byte : bytes)
    {
        std::cout << std::bitset<8>(byte).to_string() << std::endl;
    }
}

std::vector<bool> toByteArray(size_t number)
{
    std::vector<bool> bitArray;

    std::bitset<64> bits(number);

    for (int i = 0; i < 64; i++)
    {
        bitArray.push_back(bits[i]);
    }

    return bitArray;
}

namespace MD5
{
    constexpr int WORD_LENGTH = 32;
    constexpr size_t BYTE_LENGTH = 8;
    constexpr size_t MAX_MESSAGE_LENGTH = 64;
    constexpr size_t CHUNK_SIZE = 64;

    typedef std::bitset<BYTE_LENGTH> BYTE;
    typedef std::bitset<1> BIT;


    enum class MIXING_ROUND : size_t
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
            Message(const std::string& source)
            {
                bytes.insert(bytes.begin(), source.cbegin(), source.cend());
                convert();
            }

            ~Message()
            {

            }

            void convert()
            {
                //std::vector<bool> bits;

                for (char c : bytes)
                {
                    std::bitset<8> b(c);

                    for (size_t i = 0; i < 8; i++)
                    //for (int i = 7; i >= 0; i--)
                    {
                        bits.push_back(b[i]);
                    }
                }

                //return bits;
            }

            bool isPadded(const size_t sizeInBytes)
            {
                return ((sizeInBytes + MAX_MESSAGE_LENGTH) % 512 == 0);
            }

            std::vector<bool> pad()
            {
                std::vector<bool> paddedMessage = bits;
                std::vector<bool> length = toByteArray((unsigned long long)bytes.size());

                paddedMessage.push_back(0b1);

                while (!isPadded(paddedMessage.size()))
                {
                    paddedMessage.push_back(0b0);
                }

                paddedMessage.insert(paddedMessage.end(), length.begin(), length.end());

                return paddedMessage;
            }

        private:
            std::vector<char> bytes;
            std::vector<bool> bits;
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
                        result = C ^ (B | (~D));
                    }break;
                }

                return result;
            }

            std::vector<std::bitset<WORD_LENGTH>> group(const std::vector<bool>& paddedMessage)
            {
                std::vector<std::bitset<WORD_LENGTH>> words;

                std::bitset<WORD_LENGTH> w;
                size_t i = 0;

                for (auto bit : paddedMessage)
                {
                    w[i] = bit;
                    i++;

                    if (i == WORD_LENGTH)
                    {
                        words.push_back(w);
                        w.reset();
                        i = 0;
                    }
                }
                
                return words;
            }

            std::bitset<WORD_LENGTH> getK(int index)
            {
                std::vector<unsigned long long> radius =
                {
                    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
                };

                return std::bitset<WORD_LENGTH>(radius[index]);
            }

            std::bitset<WORD_LENGTH> rotateLeft(const std::bitset<WORD_LENGTH>& bits, size_t moves)
            {
                unsigned long n = bits.to_ulong();

                unsigned long shifted_n = (n >> (WORD_LENGTH - moves)) | (n << moves);

                return std::bitset<WORD_LENGTH>(shifted_n);
            }

            size_t getShiftNumber(size_t index)
            {
                std::vector<size_t> shifts =
                {
                    7, 12, 17, 22, /**/ 7, 12, 17, 22, /**/ 7, 12, 17, 22, /**/ 7, 12, 17, 22,  // 0..15
                    5,  9, 14, 20, /**/ 5,  9, 14, 20, /**/ 5,  9, 14, 20, /**/ 5, 9, 14, 20,   // 16..31
                    4, 11, 16, 23, /**/ 4, 11, 16, 23, /**/ 4, 11, 16, 23, /**/ 4, 11, 16, 23,  // 32..47
                    6, 10, 15, 21, /**/ 6, 10, 15, 21, /**/ 6, 10, 15, 21, /**/ 6, 10, 15, 21,  // 48..63
                };

                return shifts[index];
            }

            std::bitset<WORD_LENGTH> add(const std::bitset<WORD_LENGTH>& a, const std::bitset<WORD_LENGTH>& b)
            {
                return std::bitset<WORD_LENGTH>((a.to_ullong() + b.to_ullong()) & 0xffffffffL);
            }

           /* std::bitset<WORD_LENGTH> leftRotate(const std::bitset<WORD_LENGTH> word, size_t moves)
            {
                unsigned long n = word.to_ulong();

               // const unsigned int mask = (CHAR_BIT * sizeof(n) - 1);

                //c &= mask;
               // return (n << c) | (n >> ((-c) & mask));
            }*/

            void update(std::vector<bool> paddedMessage)
            {
                //std::vector<std::bitset<16>> words;

                std::vector<std::bitset<WORD_LENGTH>> words = group(paddedMessage);
                std::bitset<WORD_LENGTH> result;
                std::bitset<WORD_LENGTH> AA, BB, CC, DD;

                for (int i = 0; i < words.size(); i++)
                {
                    std::bitset<WORD_LENGTH> m = words[i];
                    
                    for (size_t round = 0; round < (size_t)MIXING_ROUND::COUNT; round++)
                    {
                        std::bitset<WORD_LENGTH> mixed = mix((MIXING_ROUND)round);

                        result = add(A, mixed);
                        result = add(result, m);
                        result = add(result, getK((i * 4) + round));

                        result = rotateLeft(result, getShiftNumber((i * 4) + round));

                        result = add(result, B);

                        AA = A;
                        BB = B;
                        CC = C;
                        DD = D;

                        A = DD;
                        B = result;
                        C = B;
                        D = C;

                        result.reset();
                    }
                }
            }

            void print()
            {
                //std::cout << A.to_string() << B.to_string() << C.to_string() << D.to_string() << std::endl;
                std::cout << std::hex << A.to_ulong() << B.to_ulong() << C.to_ulong() << D.to_ulong() << std::endl;
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
    double hash = 0;
    constexpr int PRIME = getPrimeNumber();

    for (int i = 0; i < str.length(); i++)
    {
        hash += str[i] * std::pow(PRIME, i);
    }

    return (int)hash;
}

void testMessageConversion()
{
    std::vector<std::bitset<8>> result;

    MD5::Message msg("The quick brown fox jumps over the lazy dog");


    std::vector<bool> paddedMessage = msg.pad();

    MD5::Algorithm hash;

    hash.update(paddedMessage);
    hash.print();

    //d41d8cd98f00b204e9800998ecf8427e
    //f77bf80f9ff1298c9ff1298c9ff1298c
    //f77bf80f9ff1298c9ff1298c9ff1298c

    //msg.printBinary();
    //msg.convert();

   /* result = msg.pad();

    for (auto b : result)
    {
        std::cout << b;
    }*/
}

int main()
{
    //std::cout << hash("abcde") << std::endl;

    testMessageConversion();

    return 0;
}
