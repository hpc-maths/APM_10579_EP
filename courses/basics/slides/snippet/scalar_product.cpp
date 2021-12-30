#include <iostream>

int main()
{
    double x[2] = {1, 3}, y[2] = {-2, .5};
    double sum = 0;
    for(int i = 0; i < 2; ++i)
    {
        sum += x[i]*y[i];
    }
    std::cout << sum << std::endl;
    return 0;
}