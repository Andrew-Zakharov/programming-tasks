#include <iostream>
#include <string>
#include <stack>

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

    Node peek()
    {
        if (first.empty())
        {
            move(last, first);
        }

        return first.top();
    }

    void enqueue(const std::string& data)
    {
        if (last.empty()) {
            move(first, last);
        }

        last.emplace(data);
    }

    Node dequeue()
    {
        Node result = peek();

        first.pop();

        return result;
    }

    void move(std::stack<Node>& source, std::stack<Node>& destination)
    {
        size_t size = source.size();

        for (size_t i = 0; i < size; i++) {
            destination.push(source.top());
            source.pop();
        }
    }

private:
    std::stack<Node> first; // first element is on top
    std::stack<Node> last; //last element is on top
};

void test_queue()
{
    Queue q;

    q.enqueue("a");
    q.enqueue("b");
    q.enqueue("c");
    q.enqueue("d");

    std::cout << q.peek().getData() << std::endl;

    //q.print();

    q.dequeue();

    std::cout << q.peek().getData() << std::endl;

    //q.print();

    q.dequeue();

    std::cout << q.peek().getData() << std::endl;

    //q.print();

    q.dequeue();

    std::cout << q.peek().getData() << std::endl;

    //q.print();
}

int main()
{
    test_queue();

    return 0;
}
