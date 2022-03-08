#include <iostream>
#include "autodiff.hpp"

int main(int /*argc*/, char** /*argv*/)
{
    ad::variable<double> x(3.);
    ad::variable<double> y(2.);

    auto res = x + y;

    std::cout << res.value() << std::endl;

    ad::variable<double> vres = x + y;
    std::cout << vres.value() << std::endl;

    ad::variable<double> zzz = x + 2;
    return 0;
}
