#include <iostream>
#include <string>
#include <iomanip>

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

        void setNext(Node* next)
        {
            this->next = next;
        }

        Node* getNext()
        {
            return next;
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

    const Node& peek() const
    {
        return length ? *top : Node();
    }

    void pop()
    {
        switch (length)
        {
            case 0:
            {

            }break;

            case 1:
            {
                delete(top);
                top = nullptr;
                bottom = nullptr;
                length = 0;
            }break;

            default:
            {
                Node* poped = top;
                top = top->getNext();

                delete(poped);
                length--;
            }
        }
    }

    void push(const std::string& data)
    {
        Node* newNode = new Node(data);

        if (isEmpty())
        {
            top = newNode;
            bottom = top;
        }
        else
        {
            newNode->setNext(top);
            top = newNode;
        }

        length++;
    }

    bool isEmpty()
    {
        return (length == 0);
    }

    void print()
    {
        Node* currentNode = top;
        const std::string connector = "-->";
        std::string removeConector;

        removeConector += std::string(connector.length(), '\b') + std::string(connector.length(), ' ');

        while (currentNode)
        {
            std::cout << currentNode->getValue() << connector;
            currentNode = currentNode->getNext();
        }

        std::cout << removeConector;
    }

private:
    Node* top = nullptr;
    Node* bottom = nullptr;
    size_t length = 0;
};

void destructive_print(Stack& s)
{
    while (!s.isEmpty())
    {
        std::cout << s.peek().getValue() << ' ';
        s.pop();
    }

    std::cout << std::endl;
}

void test_stack()
{
    Stack s;

//s.push("a");
    //s.push("b");
   // s.push("c");

    Node temp = s.peek();

    //destructive_print(s);
    //print(s);
    s.print();
}

int main()
{
    test_stack();

    return 0;
}

