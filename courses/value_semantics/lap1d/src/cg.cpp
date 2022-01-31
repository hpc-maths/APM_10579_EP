#include "lap1d/cg.hpp"

namespace lap1d
{
    double dot(const std::vector<double>& a, const std::vector<double>& b)
    {
        return std::inner_product(a.begin(), a.end(), b.begin(), 0.);
    }

    double norm(const std::vector<double>& x)
    {
        return std::sqrt(std::accumulate(x.begin(), x.end(), 0., [](double init, double xi){return init + xi*xi;}));
    }

    void axpy(std::vector<double>& y, double alpha, const std::vector<double>& x)
    {
        std::transform(y.begin(), y.end(), x.begin(), y.begin(), [alpha](double yi, double xi){ return yi + alpha*xi;});
    }

    void aypx(std::vector<double>& y, double alpha, const std::vector<double>& x)
    {
        std::transform(y.begin(), y.end(), x.begin(), y.begin(), [alpha](double yi, double xi){ return alpha*yi + xi;});
    }
}