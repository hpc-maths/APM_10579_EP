#include <iostream>
#include <cmath>

double f(std::size_t n)
{
    double out = 0;
    for (std::size_t i=0; i<n; ++i)
    {
        out += 1./n*std::sqrt(1 - (i*1./n*i*1./n));
    }
    return 4*out;
}

int main(int argc, char *argv[])
{
    std::cout << f(1000) << std::endl;
    return 0;
}