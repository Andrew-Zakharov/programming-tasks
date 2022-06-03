#include <iostream>
#include <stack>

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

        void setPrev(Node* prev)
        {
            this->prev = prev;
        }

        Node* getNext()
        {
            return next;
        }

        Node* getPrev()
        {
            return prev;
        }

        int getValue() const
        {
            return value;
        }

    private:
        int value = 0;
        Node* next = nullptr;
        Node* prev = nullptr;
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

        Node* getHead()
        {
            return head;
        }

        void reverse()
        {
            Node* first = head;
            Node* second = first->getNext();

            tail = first;
            first->setNext(nullptr);

            while (second)
            {
                Node* temp = second->getNext();
                second->setNext(first);

                first = second;
                second = temp;
            }

            head = first;
        }

    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        Node preHead;
        int length;
};

class DoublyLinkedList
{
    public:
        DoublyLinkedList()
        {

        }

        ~DoublyLinkedList()
        {

        }

        void append(int value)
        {
            if (tail)
            {
                tail->setNext(new Node(value));
                tail->getNext()->setPrev(tail);

                tail = tail->getNext();
            }
            else
            {
                head = new Node(value);
                tail = head;
            }

            length++;
        }

        void insert(int index, int value)
        {
            Node* node = traverseToIndex(index);

            Node* newNode = new Node(value);

            if (node == head)
            {
                newNode->setNext(node);
                node->setPrev(newNode);

                head = newNode;
            }
            else
            {
                newNode->setPrev(node->getPrev());
                newNode->setNext(node);

                node->getPrev()->setNext(newNode);
            }
        }

        Node* traverseToIndex(int index)
        {
            Node* currentNode = head;
            int i = 0;

            if (index > length)
            {
                return tail;
            }

            while (i < index)
            {
                i++;
                currentNode = currentNode->getNext();
            }

            return currentNode;
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

    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int length = 0;
};

void reverse_print(Node* node)
{
    if (node->getNext())
    {
        reverse_print(node->getNext());
    }

    std::cout << node->getValue() << ' ';
}

void test_linked_list()
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
}

void test_doubly_linked_list()
{
    DoublyLinkedList l;

    l.append(1);
    l.append(2);
    l.append(3);
    l.append(4);

    l.print();

    l.insert(2, 100);

    l.print();

    l.insert(0, 200);

    l.print();
}

void test_reverse_print()
{
    LinkedList l(1);

    l.append(2);
    l.append(3);
    l.prepend(0);

    reverse_print(l.getHead());
}

void test_reverse()
{
    LinkedList l(1);

    l.append(2);
    l.append(3);
    l.prepend(0);

    l.print();

    l.reverse();

    l.print();
}

int main()
{
    //test_doubly_linked_list();

    //test_reverse_print();

    test_reverse();

    return 0;
}
