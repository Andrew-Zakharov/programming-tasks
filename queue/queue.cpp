#include <iostream>
#include <string>

class Node
{
public:
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

    std::string getData()
    {
        return data;
    }

    Node* getNext()
    {
        return next;
    }

private:
    std::string data;
    Node* next = nullptr;
};

class Queue
{
public:
    Queue()
    {

    }

    Node* peek()
    {
        return first;
    }

    void enqueue(const std::string& data)
    {
        Node* newNode = new Node(data);

        switch (length)
        {
            case 0:
            {
                first = newNode;
                last = first;
            }break;

            default:
            {
                last->setNext(newNode);
                last = newNode;
            } 
        }

        length++;
    }

    void dequeue()
    {
        switch (length)
        {
            case 0:
            {

            }break;

            case 1:
            {
                delete(first);

                first = nullptr;
                last = nullptr;
                length = 0;
            }break;

            default:
            {
                Node* holdingPointer = first;

                first = first->getNext();

                delete(holdingPointer);
                length--;
            }
        }
    }

    void print()
    {
        Node* current = first;

        while (current)
        {
            std::cout << current->getData() << ' ';
            current = current->getNext();
        }

        std::cout << std::endl;
    }

private:
    Node* first = nullptr;
    Node* last = nullptr;
    size_t length = 0;
};

void test_queue()
{
    Queue q;

    q.enqueue("a");
    q.enqueue("b");
    q.enqueue("c");
    q.enqueue("d");

    std::cout << q.peek()->getData() << std::endl;

    q.print();

    q.dequeue();

    std::cout << q.peek()->getData() << std::endl;

    q.print();

    q.dequeue();

    std::cout << q.peek()->getData() << std::endl;

    q.print();

    q.dequeue();

    std::cout << q.peek()->getData() << std::endl;

    q.print();
}

int main()
{
    test_queue();

    return 0;
}
