#include <vector>
#include <random>
#include <tuple>
#include <algorithm>
#include <generative/core.hpp>
#include <generative/shape.hpp>

auto init_colors(std::size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::vector<std::array<uchar, 4>> color(n);

    for(std::size_t i=0; i<n; ++i)
    {
        for(std::size_t c=0; c<3; ++c)
        {
            color[i][c] = dis(gen);
        }
        color[i][3] = 1;
    }
    return color;
}

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

    auto colors = init_colors(nb_lines);

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

    cv::Mat img(1000, 1000, CV_8UC4);
    for(std::size_t i = 0; i < x.size(); ++i)
    {
        art::generative_art(img, x[i], y[i], xs_func, 1000, colors[i]);
    }
    cv::imwrite("output.png", img);

    return 0;
}