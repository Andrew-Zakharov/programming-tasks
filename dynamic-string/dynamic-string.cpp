#include <iostream>

#define NULL_SYMBOL_SIZE 1

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

void concatenate(char** first, const char* second)
{
    char* result = nullptr;
    unsigned int i = 0;
    unsigned int j = 0;

    const unsigned int first_size = get_size(*first);
    const unsigned int second_size = get_size(second);

    result = new char[first_size + second_size + NULL_SYMBOL_SIZE];

    for (i = 0; i < first_size; i++)
    {
        result[i] = *(*first + i);
    }

    for (j = 0; j < second_size; j++)
    {
        result[i++] = second[j];
    }

    result[i] = '\0';

    delete* first;
    *first = result;

    result = nullptr;
}

void append(char** str, char c)
{
    char* result = nullptr;
    const unsigned int size = get_size(*str);
    unsigned int i = 0;

    result = new char[size + 1 + NULL_SYMBOL_SIZE];

    if (result)
    {
        for (i = 0; i < size; i++)
        {
            result[i] = *((*str) + i);
        }

        result[i++] = c;
        result[i] = '\0';

        delete *str;
        *str = result;
        result = nullptr;
    }
}

char charAt(const char* str, unsigned int index)
{
    return str[index];
}

char* initDynamicArray(const char* str)
{
    char** p = nullptr;
    const unsigned int size = get_size(str);

    p = new char*;
    *p = new char[size + NULL_SYMBOL_SIZE];

    if (*p)
    {
        unsigned int i = 0;

        for (i = 0; i < size; i++)
        {
            *(*p + i) = str[i];
        }

        *(*p + i) = '\0';
    }

    return *p;
}

void test_dynamic_string()
{
    char* s1 = initDynamicArray("abc");
    char* s2 = initDynamicArray("def");

    concatenate(&s1, s2);

    std::cout << s1;
}

int main()
{
    test_dynamic_string();

    return 0;
}