#include <iostream>
#include <string>
class Grid {
private:
    float *memory;
    size_t x_size, y_size;

public:
    Grid(size_t xsize, size_t ysize)
    {
        if(xsize == 0 || ysize == 0)
        {
            std::cout<< "Incorrect values, try again" << std::endl;
            std::cin >> xsize;
            std::cin >> ysize;
        }
        memory = new float[xsize*ysize];
        x_size = xsize;
        y_size = ysize;
        for(int i = 0; i < y_size; i++)
            {for(int j = 0; j < x_size; j++)
            {
                memory[i*x_size + j] = 0;
            }}
    }

    ~Grid()
    {
        delete [] memory;
        std::cout << "deleted" << std::endl;
    }

    void deleteelement(size_t x_idx, size_t y_idx)
    {
        memory[x_size*y_idx + x_idx] = 0;
    }

    float operator()(size_t x_idx, size_t y_idx) const
    {
        if((x_idx < x_size) && (y_idx < y_size))
           return memory[x_size*y_idx + x_idx];
        else
        {
            std::cout <<"Error" <<std::endl;
            return 0;
        }

    }
    float& operator()(size_t x_idx, size_t y_idx)
    {
        if((x_idx < x_size) && (y_idx < y_size))
           return memory[x_size*y_idx + x_idx];
        else
        {
            std::cout <<"Error" <<std::endl;
        }
        float a = 0.0;
        return a;
    }
    size_t get_xsize() const
    {
        return x_size;
    }
    size_t get_ysize() const
    {
        return y_size;
    }

    Grid& operator=(float a)
    {
        for(int i = 0; i < y_size; i++)
            for(int j = 0; j < x_size; j++)
            {
                memory[i*x_size + j] = a;
            }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, Grid const& setka)
    {
        for(int i = 0; i < setka.y_size; i++)
            {
                for(int j = 0; j < setka.x_size; j++)
                {
                    out << setka.memory[i*setka.x_size + j] <<' ';
                }
                out << '\n';}

         return out;
    }

    friend std::istream& operator>>(std::istream& in, Grid & setka)
    {
        for(int i = 0; i < setka.y_size; i++)
            {for(int j = 0; j < setka.x_size; j++)
            {
                in >> setka.memory[i*setka.x_size + j];
            }}
        return in;
    }
};


int main()
{
    Grid set1(2, 2);
    float a;
    a = 35.3;
    set1 = a;
    Grid set2(2, 2);
    std::cin >> set2;

    std::cout << set1 << std::endl;
    std::cout << set2 << std::endl;
    std::cout << set1(1, 1) << std::endl;
    std::cout << set2(0, 1) << std::endl;
    std::cout << set1.get_xsize() <<std::endl;
    std::cout << set2(3, 2) << std::endl;

    set1.deleteelement(0, 0);
    std::cout << set1 << std::endl;
    set1.~Grid();
    set2.~Grid();
    return 0;
}
