#include <iostream>

template <class T>

class MyVector
{
private:
    struct Node
    {
        T value;
        Node * next;
        Node(): next(nullptr) {}
        Node(const T& val): value(val), next(nullptr) {}
    };
    Node* head;
    Node* tail;
public:
    MyVector(): head(nullptr), tail(nullptr) {}
    ~MyVector() {};

    bool empty()
    {
        return head == nullptr;
    }

    void push_back(T& val)
    {
        Node* p = new Node(val);
        if(empty())
        {
            head = p;
            tail = p;
            return;
        }
        tail->next = p;
        tail = p;

    }

    void pop_back()
    {
        if(empty())
            return;
        if (head == tail)
        {
            Node* p = head;
            head = p->next;
            delete p;
            return;
        }
        Node* t = head;
        while (t->next != tail)
            t = t->next;
        t->next = nullptr;
        delete tail;
        tail = t;
    }

    void print()
    {
        if(empty())
            return;
        Node* p = head;
        while (p)
        {
            std::cout << p->value << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }

    T front()
    {
        return head->value;
    }

    T back()
    {
        return tail->value;
    }
};


int main()
{
    MyVector<int> Vec;
    std::cout << Vec.empty() << std::endl;
    int a = 4;
    int b = 45;
    int c = 67;
    int d = 13;

    Vec.push_back(a);
    Vec.push_back(b);
    Vec.push_back(c);
    Vec.push_back(d);
    Vec.print();
    std::cout << Vec.empty() << std::endl;
    Vec.pop_back();
    Vec.print();
    Vec.pop_back();
    Vec.print();
    Vec.push_back(d);
    Vec.push_back(d);
    Vec.print();
    std::cout << Vec.front() << std::endl;
    std::cout << Vec.back() << std::endl;
    return 0;


}
