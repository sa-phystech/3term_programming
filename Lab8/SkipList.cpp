#include <iostream>
#include <vector>
#include <iterator>
#include <memory>
#include <limits>
#include <cmath>
#include <random>

template <class T>
struct Node
{
    T value;
    int lvl;
    std::vector<Node*> next;

    Node (const T& val)
    {
        value = val;
    }

    ~Node()
    {
        lvl = 0;
        value = 0;
        for(int i = 0; i < next.size(); i++)
        {
            delete next[i];
        }
    }
};

template <class T>
class SkipList
{
private:
    double prob;
    int length;
    int maxlvl;
    Node<T>* head;

    float GenerateRandomValue()
    {
        return (float) rand() / RAND_MAX;
    }

    int random_lvl()
    {
        static bool first = true;
        if(first)
        {
            srand((unsigned)time(NULL));
            first = false;

        }
        int random_level = (int)(log(GenerateRandomValue()) / log(1.-prob));
        return random_level < maxlvl ? random_level : maxlvl;
    }

    int choose_head()
    {
        head = new Node<T>(std::numeric_limits<T>::lowest());
        for(int i = 0; i < maxlvl; i++)
        {
            head->next.push_back(nullptr);
        }
    }
public:
    SkipList()
    {
        prob = 0.5;
        length = 0;
        maxlvl = 10;
        choose_head();
    }

    SkipList(const SkipList& skiplist)
    {
        prob = skiplist.prob;
        length = skiplist.length;
        maxlvl = skiplist.maxlvl;
        head = skiplist.head;
    }

    SkipList(SkipList&& skiplist)
    {
        prob = skiplist.prob;
        length = skiplist.length;
        maxlvl = skiplist.maxlvl;
        head = skiplist.head;

        skiplist.prob = 0;
        skiplist.length = 0;
        skiplist.maxlvl = 0;
        skiplist.head = nullptr;
    }

    bool empty()
    {
        return (length == 0);
    }

    int size()
    {
        return length;
    }

    void clear()
    {
        if(head != nullptr)
        {
            auto x = head;
            while(x != nullptr)
            {
                auto x_next = x->next[0];
                delete x;
                x = x_next
            }
        }
        choose_head();
        length = 0;
    }

    void insert(const T& val)
    {
        int lvl = random_lvl();
        Node<T>* h = head;
        Node<T>* new_node = new Node<T>(val, lvl + 1);

        for(auto i = maxlvl; i >= 0; i--)
        {
            while((h->next[i] != nullptr) && ((*h).next[i]->value < val))
            {
                h = h->next[i];
            }

            if(i <= lvl)
            {
                new_node->next[i] = h->next[i];
                h->next[i] = new_node;
            }
        }
        length++;
    }





};
