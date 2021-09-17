#include <iostream>
#include <vector>

int main()
{
    class Matrix
    {
    private:
        int** M;
        int m;
        int n;
    public:
        Matrix(int length, int width)
        {
            m = length;
            n = width;
            M = new int* [m];
            for(int i = 0; i < m; i++)
                M[i] = new int[n];
        }
        ~Matrix()
        {
            for(int i = 0; i < m; i++)
                delete[] M[i];
            delete [] M;
        }
        void Set_element(int i, int j, int value)
        {
            M[i][j] = value;
        }
        void PrintMatrix()
        {
            for(int i = 0; i < m; i++)
                {for(int j = 0; j < m; j++)
                    std::cout << M[i][j] <<' ';
                    std::cout << std::endl;}

        }


    };
    Matrix T(4, 5);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 5; j++)
            T.Set_element(i, j, rand() % 20 +10 );
    T.PrintMatrix();
    return 0;
}
