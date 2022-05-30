#include <iostream>
#include <memory>

class Node
{
    public:
        Node(int value = 0) : value(value)
        {

        }

        ~Node()
        {
            next = nullptr;
        }

        void setNext(Node* next)
        {
            this->next = next;
        }

        Node* getNext()
        {
            return next;
        }

        int getValue() const
        {
            return value;
        }

    private:
        int value;
        Node* next = nullptr;
};

class LinkedList
{
    public:

        LinkedList(int value)
        {
            head = new Node(value);
            tail = head;
            length = 0;
        }

        ~LinkedList()
        {

        }

        void append(int value)
        {
            tail->setNext(new Node(value));
            tail = tail->getNext();
            length++;
        }

        void prepend(int value)
        {
            Node* newHead = new Node(value);

            newHead->setNext(head);
            head = newHead;
            length++;
        }

        void print()
        {
            Node* currentNode = head;

            while (currentNode)
            {
                std::cout << currentNode->getValue() << ' ';
                currentNode = currentNode->getNext();
            }

            std::cout << std::endl;
        }

        void insert(int index, int value)
        {
            Node* currentNode = head;
            int i = 0;

            if (index == 0)
            {
                prepend(value);
            }
            else
            {
                currentNode = traverse(index);

                Node* temp = currentNode->getNext();

                currentNode->setNext(new Node(value));
                currentNode->getNext()->setNext(temp);
                length++;
            }
        }

        Node* traverse(int index)
        {
            Node* currentNode = head;
            int i = 0;

            if (index >= length)
            {
                return tail;
            }

            while (currentNode && i < (index - 1))
            {
                currentNode = currentNode->getNext();
                i++;
            }

            return currentNode;
        }

    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int length;
};

int main()
{
    LinkedList l(1);

    l.append(2);
    l.append(3);
    l.prepend(0);

    l.print();

    l.insert(2, 100);

    l.print();

    l.insert(10, 200);

    l.print();

    l.insert(0, 300);

    l.print();

    return 0;
}
