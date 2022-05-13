#include <iostream>

unsigned int get_size(const char* str)
{
    unsigned int size = 0;

    if (str)
    {
        unsigned int i = 0;

        while (str[i] != '\0') i++;

        size = i;
    }

    return size;
}

char* concatenate(const char* first, const char* second)
{
    char* result = nullptr;
    unsigned int i = 0;

    const unsigned int first_size = get_size(first);
    const unsigned int second_size = get_size(second);

    result = new char[first_size + second_size + 1];

    for (i = 0; i < (first_size + second_size); i++)
    {
        if (i < first_size)
        {
            result[i] = first[i];
        }
        else
        {
            result[i] = second[i - first_size];
        }
        
    }

    result[i] = '\0';

    return result;
}

char* append(const char* str, char c)
{
    return nullptr;
}

char charAt(const char* str, unsigned int index)
{
    return 0;
}

void test_dynamic_string()
{
    const char* s1 = "abc";
    const char* s2 = "def";

    std::cout << get_size(s1) << std::endl;
    std::cout << concatenate(s1, s2);
}

int main()
{
    test_dynamic_string();

    return 0;
}