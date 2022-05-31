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
            length = 1;
            preHead.setNext(head);
        }

        ~LinkedList()
        {

        }

        void append(int value)
        {
            tail = append(tail, value);
        }

        Node* append(Node* node, int value)
        {
            Node* hold = node->getNext();

            node->setNext(new Node(value));
            node->getNext()->setNext(hold);
            length++;

            return node->getNext();
        }

        void prepend(int value)
        {
            head = append(&preHead, value);
        }

        void print()
        {
            Node* currentNode = head;

            while (currentNode)
            {
                std::cout << currentNode->getValue() << ' ';
                currentNode = currentNode->getNext();
            }

            std::cout << "( head: " << head->getValue() << ", tail: " << tail->getValue() << ")";

            std::cout << std::endl;
        }

        void insert(int index, int value)
        {
            Node* insertedNode = append(getPrevNode(index), value);

            if (index >= (length - 1))
            {
                tail = insertedNode;
            }

            if (index == 0)
            {
                head = insertedNode;
            }
        }

        Node* getPrevNode(int index)
        {
            Node* currentNode = head;
            int i = 0;

            if (index >= length)
            {
                return tail;
            }

            if (index == 0)
            {
                return &preHead;
            }

            while (currentNode && i < (index - 1))
            {
                currentNode = currentNode->getNext();
                i++;
            }

            return currentNode;
        }

        void remove(int index)
        {
            Node* prevNode = getPrevNode(index);
            Node* unwantedNode = prevNode->getNext();

            prevNode->setNext(prevNode->getNext()->getNext());
            unwantedNode->setNext(nullptr);

            delete(unwantedNode);
            

            if (index == (length - 1)) {
                tail = prevNode;
            }

            if (index == 0) {
                head = prevNode->getNext();
            }

            length--;
        }

    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        Node preHead;
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

    l.insert(1, 400);

    l.print();

    l.remove(0);

    l.print();

    l.remove(2);

    l.print();

    l.remove(4);

    l.print();

    l.remove(4);

    l.print();

    return 0;
}
