#include <vector>
#include <random>
#include <tuple>
#include <algorithm>
#include <generative/core.hpp>
#include <generative/shape.hpp>

int main()
{
    std::size_t nb_lines = 10;
    std::vector<art::array_t> x(nb_lines), y(nb_lines);

    double lo = .2, up = .8;
    std::size_t npoints = 15;

    auto yy = art::shape::linspace(lo, up, nb_lines);
    for(std::size_t i = 0; i < x.size(); ++i)
    {
        std::tie(x[i], y[i]) = art::shape::line(lo, up, yy[i], npoints);
        npoints++;
    }

    auto xs_func = [lo, up]()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0., 1.);

        std::size_t nsamples = 500;
        auto x = art::shape::linspace(lo + .05, up - .05, nsamples);
        std::for_each(x.begin(), x.end(), [&dis, &gen](double& e){ e += 1e-3*dis(gen);});
        return x;
    };

    for(std::size_t i = 0; i < x.size(); ++i)
    {
        art::generative_art(x[i], y[i], xs_func, 1000);
    }

    return 0;
}