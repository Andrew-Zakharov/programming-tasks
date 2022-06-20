#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

class Node
{
    public:
        Node()
        {

        }

        Node(const std::string& data) : data(data)
        {

        }

        ~Node()
        {

        }

        std::string getValue() const
        {
            return data;
        }

        bool isInitialized()
        {
            return data.empty();
        }

    private:
        std::string data;
};

class Stack
{
public:
    Stack()
    {

    }

    ~Stack()
    {

    }

    const Node& peek() const
    {
        return data.back();
    }

    void pop()
    {
        data.pop_back();
    }

    void push(const std::string& data)
    {
        this->data.emplace_back(data);
    }

    bool isEmpty()
    {
        return data.empty();
    }

    void print()
    {
        for (auto it = data.crbegin(); it != data.crend(); it++)
        {
            std::cout << it->getValue() << ' ';
        }

        std::cout << std::endl;
    }

private:
    std::vector<Node> data;
};

void test_stack()
{
    Stack s;

    s.push("a");
    s.push("b");
    s.push("c");

    std::cout << s.peek().getValue() << std::endl;

    s.print();

    s.pop();

    s.print();

    s.pop();

    s.print();

    s.pop();

    s.print();
}

int main()
{
    test_stack();

    return 0;
}

