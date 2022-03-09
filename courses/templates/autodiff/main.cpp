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

    
    ad::variable<double> z = x + 2;
    std::cout << z.value() << std::endl;

    std::cout << "=========" << std::endl;
    x.activate(true);
    y.activate(true);
    z.activate(true);
    auto res2 = x + y * z;
    std::cout << res2.value() << std::endl;
    std::cout << res2.derivative() << std::endl;
    return 0;
}
