#include <iostream>

    int Hash_function (const std::string& word, int massive_size, const int key)
    {
        int result = 0;
        for (int i = 0; word[i] != word.size(); ++i)
        {
            result = (key * result + word[i]) % massive_size;
        }
        result = (result * 2 + 1) % massive_size;
        return result;
    }

    struct Hash_f1
    {
        int operator()(const std::string& word, int massive_size) const
        {
            return Hash_function(word, massive_size, massive_size - 1);
        }
    };

    struct Hash_f2
    {
        int operator()(const std::string& word, int massive_size) const
        {
            return Hash_function(word, massive_size, massive_size + 1);

        }
    };

    template <class T, class THash1 = Hash_f1, class THash2 = Hash_f2>
    class HashMassive
    {
        static const int default_size = 8;
        constexpr static const double rehash_size = 0.75;
        struct Node
        {
            T value;
            bool state;
            Node(const T& value_) : value(value_), state(true) {}

        };
        Node** array0;
        int size;
        int buffer_size;
        int size_all;

        void Resize()
        {
            int past_buffer_size = buffer_size;
            buffer_size *= 2;
            size_all = 0;
            size = 0;
            Node** array2 = new Node * [buffer_size];
            for (int i = 0; i < buffer_size; ++i)
                {array2[i] = nullptr;}

            std::swap(array0, array2);
            for (int i = 0; i < past_buffer_size; ++i)
            {
                if (array2[i] && array2[i]->state)
                {
                    Add(array2[i]->value);
                }
            }

            for (int i = 0; i < past_buffer_size; ++i)
            {
                if (array2[i])
                {
                    delete array2[i];
                }
                delete [] array2;
            }

        }

        void Rehash()
        {
            size_all = 0;
            size = 0;
            Node** array2 = new Node * [buffer_size];
            for (int i = 0; i < buffer_size; ++i)
            {
                array2[i] = nullptr;
            }

            std::swap(array0, array2);

            for (int i = 0; i < buffer_size; ++i)
            {
                if (array2[i] && array2[i]->state)
                {
                    Add(array2[i]->value);
                }
            }

            for (int i = 0; i < buffer_size; ++i)
            {
                if (array2[i])
                {
                     delete array2[i];
                }
            }
            delete [] array2;

        }

    public:
        HashMassive()
        {
            buffer_size = default_size;
            size = 0;
            size_all = 0;
            array0 = new Node*[buffer_size];
            for (int i = 0; i < buffer_size; ++i)
            {
                array0[i] = nullptr;
            }
        }
        ~HashMassive()
        {
            for (int i = 0; i < buffer_size; ++i)
            {
                if (array0[i])
                {
                    delete array0[i];
                }
            }
            delete [] array0;
        }



        bool Find(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())
        {
            int h1 = hash1(value, buffer_size);
            int h2 = hash2(value, buffer_size);
            int i = 0;
            while (array0[h1] != nullptr && i < buffer_size)
            {
                if (array0[h1]->value == value && array0[h1]->state)
                    return true;
                h1 = (h1 + h2) % buffer_size;
                ++i;
            }
            return false;
        }


        bool Remove(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())
        {
            int h1 = hash1(value, buffer_size);
            int h2 = hash2(value, buffer_size);
            int i = 0;
            while (array0[h1] != nullptr && i < buffer_size)
            {
                if (array0[h1]->value == value && array0[h1]->state)
                {
                    array0[h1]->state = false;
                    --size;
                    return true;

                }
                h1 = (h1 + h2) % buffer_size;
                ++i;
            }
            return false;}


        bool Add(const T& value, const THash1& hash1 = THash1(),const THash2& hash2 = THash2())
        {
            if (size + 1 > int(rehash_size * buffer_size))
                Resize();
            else if (size_all > 2 * size)
                Rehash();
            int h1 = hash1(value, buffer_size);
            int h2 = hash2(value, buffer_size);
            int i = 0;
            int first_deleted = -1;
            while (array0[h1] != nullptr && i < buffer_size)
            {
                if (array0[h1]->value == value && array0[h1]->state)
                    return false;
                if (!array0[h1]->state && first_deleted == -1)
                    first_deleted = h1;
                h1 = (h1 + h2) % buffer_size;
                ++i;
            }
            if (first_deleted == -1)
            {
                array0[h1] = new Node(value);
                ++size_all;
            }
            else
            {
                array0[first_deleted]->value = value;
                array0[first_deleted]->state = true;
            }
            ++size;
            return true;
        }
    };

int main()
{
    HashMassive<std::string> HashArray;
    std::string a;
    std::cin >> a;
    HashArray.Add(a);
    return 0;
}
