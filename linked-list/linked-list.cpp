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
        }

        ~LinkedList()
        {

        }

        void append(int value)
        {
            tail->setNext(new Node(value));
            tail = tail->getNext();
        }

        void prepend(int value)
        {
            Node* newHead = new Node(value);

            newHead->setNext(head);
            head = newHead;
        }

    private:
        Node* head = nullptr;
        Node* tail = nullptr;
};

int main()
{
    LinkedList l(1);

    l.append(2);
    l.append(3);
    l.prepend(0);

    return 0;
}
