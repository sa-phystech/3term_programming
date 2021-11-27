#include <iostream>

template<typename T>

T maximum(T a, T b)
{
    return (a > b) ? a : b;
}

int main()
{
    int a, b;
    double c, d;
    bool f, g;
    char q, x;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;
    std::cin >> f;
    std::cin >> g;
    std::cout << maximum(a, b) << std::endl;
    std::cout << maximum(c, d) << std::endl;
    std::cout << maximum(f, g) << std::endl;

    return 0;
}
