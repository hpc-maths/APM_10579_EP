#include <iostream>
#include <cmath>

// Compute pi using the rectangle method
// to approximate the integral of 4*sqrt(1 - x^2)
// over [0, 1]
double compute_pi(std::size_t n)
{
    double quarter_pi = 0;
    double h = 1./n; // space step
    for (std::size_t i=0; i<n; ++i)
    {
        double xi = i*h;
        quarter_pi += h*std::sqrt(1 - xi*xi);
    }
    return 4*quarter_pi;
}

int main()
{
    std::cout << compute_pi(1000) << std::endl;
    return 0;
}