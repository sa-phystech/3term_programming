#include <iostream>
#include <ctime>

template<typename T>

T factorial(T a)
{
    if(a < 0)
        return 0;
    if(a == 0)
        return 1;
    else
        return a*factorial(a-1);
}

__int64 fact(__int64 a)
{
    if(a < 0)
        return 0;
    if(a == 0)
        return 1;
    else
        return a*fact(a-1);
}

int main()
{
    __int64 a;
    std::cin >> a;
    std::cout << std::endl;

    __int64 start_time =  clock();
    std::cout << factorial(a) << std::endl;
    __int64 end_time = clock(); // конечное время
    __int64 search_time = end_time - start_time; // искомое время
    std::cout << search_time << std::endl;
    std::cout << std::endl;

    __int64 start_time1 =  clock();
    std::cout << fact(a) << std::endl;
    __int64 end_time1 = clock(); // конечное время
    __int64 search_time1 = end_time1 - start_time1; // искомое время
    std::cout << search_time1 << std::endl;
    return 0;
}
