#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
#include "interpolation.hpp"
#include "interpolation_impl.hpp"

namespace hpc
{
    using curve_type = std::pair<std::vector<double>, std::vector<double>>;

    curve_type make_curve()
    {
        std::vector<double> x = { -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5 };
        std::vector<double> y(x.size());
        std::transform(x.begin(), x.end(), y.begin(), [](double v)
        {
            return 1. / (1 + std::exp(-0.25 * v));
        });
        return std::make_pair(std::move(x), std::move(y));
    }

    /*spline_interpolation get_test_spline_interpolation()
    {
        auto curve = make_curve();
        return spline_interpolation(curve.first, curve.second);
    }*/

    /*void test_accessibility1()
    {
        spline_interpolation si;
        double v = si.interpolate(2.5);
    }*/

    /*void test_polymorphism(const interpolation_impl& inter)
    {
        double y = inter.interpolate(1.2);
        std::cout << y << std:endl;
    }

    void test_polymorphism()
    {
        spline_interpolation inter = get_test_spline_interpolation();
        test_polymorphism(inter);
    }*/

    /*interpolation_impl get_test_interpolation()
    {
        auto curve = make_curve();
        return interpolation_impl(curve.first, curve.second);
    }*/

    /*void test_polymorphism1()
    {
        auto curve = make_curve();
        interpolation_impl* inter = new spline_interpolation(curve.first, curve.second);
        test_polymorphism(*inter);
        delete inter;
    }*/

    /*void test_assign()
    {
        auto curve = make_curve();
        interpolation_impl* inter = new spline_interpolation(curve.first, curve.second);

        std::vector<double> x = { 1., 2., 3. };
        std::vector<double> y = { 2., 4., 6. };
        interpolation_impl* inter2 = new spline_interpolation(x, y);

        *inter2 = *inter1;

        inter1->print();
        inter2->print();

        delete inter2;
        delete inter1;
    }*/

    /*void test_api()
    {
        auto curve = make_curve();
        interpolation ip(curve.first, curve.second, interpolation_type::spline);
        double res = ip.interpolate(0.25);
        std::cout << res << std::endl;
    }*/
}

int main(int argc, char* argv[])
{
    //hpc::test_accessibility1();
    //hpc::test_polymorphism();
    //hpc::test_polymorphism1();
    //hpc::test_assign();
    //hpc::test_api();
    return 0;
}
