#include <iostream>

template <typename T>
 struct Node
 {
     T value;
     Node** DifferentLevels
     /*Node* next;
     Node* previous;*/
 };

 class SkipList
 {
 private:
    Node * head;
    Node * tail;
    float probability;
    int MaxLevel;
    int ListSize;
 public:
    SkipList();
    SkipList();
    ~SkipList();

    int RandomLevel()
    {
        int lvl = 1;
        float a = (rand() % 100 + 1) / 100.0;
        while((a < probability) && (lvl < MaxLevel))
        {
            lvl += 1;
        }

        return lvl;
    }

    Node* Find(T val)
    {
       Node* a = head;
       Node* M[MaxLevel + 1];
       for (int i = MaxLevel; i >= 0; i--)
       {
           while((x->DifferentLevels != nullptr) && (a->DifferentLevels[i]->value < val))
           {
               a = a->DifferentLevels[i];
           }
       }
       a = a->DifferenyLevels[0];
       return ((a != nullptr) && (x->value == val));
    }
    void Insert(T val)
    {
        Node* a = head;
        Node* DifferentLevels[MaxLevel + 1];
        for (int i = MaxLevel; i >= 0; i--)
        {
            while((a->DifferentLevels[i] != nullptr) && (a->DifferentLevels[i]->value < val))
            {
                a = a->DifferentLevels[i];
            }
            update[i] = a;
        }
        a = a->DifferentLevels[0];
        if ((a == nullptr) || (a->value != val))
        {
            int lvl = RandomLevel();
            if (lvl > MaxLevel)
            {
                for (int i = MaxLevel + 1; i <= lvl; i++)
                {
                    update[i] = head;
                }
                MaxLevel = lvl;
            }
            res = new Node;
            for (int i = 0; i <= lvl; i++)
            {
                x->DifferentLevels[i] = update[i]->DifferentLevels[i];
                update[i]->DifferentLevels[i] = x;
            }
        }
    }

    void PrintList();
    void Erase(T value)
    {
        Node *a = head;
        Node *update[MaxLevel + 1];
        for(int i = MaxLevel; i >= 0; i--)
        {
            while((a->DifferentLevels[i] != nullptr)&&(a->DifferentLevels->value < val))
            {
                a = a->DifferentLevels[i];
            }
        }


    }

    void Clear();
    bool Empty()
    {
        if (head == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    int Size()
    {
        return ListSize;
    }
    int Count(T val)
    Node* Upper_bound();
    Node* Lower_bound();
 };
