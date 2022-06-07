#include <iostream>
#include <string>

class Node
{
    public:
        Node()
        {

        }

        ~Node()
        {

        }

        void setNext(Node* next)
        {
            this->next = next;
        }

        Node* getNext()
        {
            return next;
        }

        std::string getValue()
        {
            return data;
        }

    private:
        std::string data;
        Node* next = nullptr;
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

    Node* peek()
    {

    }

    Node* pop()
    {

    }

    void push(const std::string& data)
    {

    }

private:
    Node* top = nullptr;
    Node* bottom = nullptr;
    size_t length = 0;
};

int main()
{
    return 0;
}

