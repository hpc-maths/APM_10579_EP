#include <lap1d/csr.hpp>
#include <lap1d/dense.hpp>
#include <lap1d/cg.hpp>

int main()
{
    std::size_t n = 99;
    double dx = 1./(n + 1);
    double dx2 = dx*dx;

    std::vector<double> x(n), b(n, 1);

    // lap1d::matrix A(n, n);
    lap1d::csr A(n, n);

    A(0, 0) = 2./dx2;
    A(0, 1) = -1./dx2;
    for(std::size_t i = 1; i < n-1; ++i)
    {
        A(i, i-1) = -1./dx2;
        A(i, i) = 2./dx2;
        A(i, i+1) = -1./dx2;
    }
    A(n-1, n-1) = 2./dx2;
    A(n-1, n-2) = -1./dx2;
    
    // std::cout << A << std::endl;
    lap1d::cg(A, x, b);

    for(auto& xi: x)
    {
        std::cout << xi << std::endl;
    }
    return 0;
}