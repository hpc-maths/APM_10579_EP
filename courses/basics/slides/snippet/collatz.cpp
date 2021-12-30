#include <iostream>

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);

    std::cout << n << " ";
    while (n != 1)
    {
        if (n&1)
        {
            n = (3*n + 1)/2;
        }
        else
        {
            n /= 2;
        }
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}