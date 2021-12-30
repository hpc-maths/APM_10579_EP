#include <iostream>

int main()
{
    int a = 10;
    {
        int b = 4096;
        for(int i = 0; i < a; ++i)
        {
            b /= 2;
            int c = b;
            std::cout << c << std::endl;
        }

        int a = 5;
        std::cout << a << std::endl; // error: c is not accessible
    }
    std::cout << a << std::endl; // error: b is not accessible
    return 0;
}