#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define pi 4.*std::atan(1)

using array_t = std::vector<double>;

void spline(const array_t& xs, const array_t& ys, array_t& y2s)
{
    array_t u_i(xs.size());
    std::fill(y2s.begin(), y2s.end(), 0.);

    for (std::size_t i = 1; i < xs.size() - 1; ++i)
    {
        double xplus = xs[i+1] - xs[i];
        double xminus = xs[i] - xs[i-1];
        double sig = xminus/(xs[i+1] - xs[i-1]);

        u_i[i] = (ys[i+1] - ys[i])/xplus
               - (ys[i] - ys[i-1])/xminus;

        double p_i = sig*y2s[i-1] + 2.;
        y2s[i] = (sig - 1.)/p_i;
        u_i[i] = (6*u_i[i]/(xs[i+1] - xs[i-1]) - sig*u_i[i-1])/p_i;
    }

    for (std::size_t i = xs.size() - 2; i != std::size_t(-1); --i)
    {
        y2s[i] = y2s[i]*y2s[i+1] + u_i[i];
    }
}

auto searchsorted(const array_t& v, const array_t& t)
{
    std::vector<std::size_t> out(t.size());
    std::for_each(t.begin(), t.cend(), [&, n=0](const float &e) mutable{
        auto lower = std::lower_bound (v.begin(), v.end(), e);
        out[n++] = std::distance(v.begin(), lower);
    });
    return out;
}

void splint(const array_t& xs, const array_t& ys, const array_t& y2s,
            const array_t& x, array_t& y)
{
    auto k = searchsorted(xs, x);

    for(std::size_t i = 0; i < y.size(); ++i)
    {
        std::size_t khi = k[i];
        std::size_t klo = khi - 1;
        double step = xs[khi] - xs[klo];
        double x_right = (xs[khi] - x[i])/step;
        double x_left = (x[i] - xs[klo])/step;
        y[i] = x_right*ys[klo] + x_left*ys[khi]+(
              x_right*(x_right*x_right - 1)*y2s[klo]+
              x_left*(x_left*x_left - 1)*y2s[khi])*step*step/6.;
    }
}

auto linspace(double begin, double end, std::size_t n)
{
    std::vector<double> out(n);
    double step = (end - begin)/(n-1);

    for(std::size_t i=0; i<n; ++i)
    {
        out[i] = begin + step*i;
    }

    return out;
}

auto line(double begin, double end, double ypos=.5, std::size_t n=50)
{
    auto x = linspace(begin, end, n);
    std::vector<double> y(n, ypos);
    return std::make_pair(x, y);
}

void update_path(array_t& x, array_t& y, double scale_value)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1., 1.);

    for(std::size_t i = 0; i < x.size(); ++i)
    {
        double radius = dis(gen)*i*scale_value;
        double phi = dis(gen)*pi;
        x[i] += radius*std::cos(phi);
        y[i] += radius*std::sin(phi);
    }
}

template<class Func>
void generative_art(array_t& x, array_t& y, Func&& xs_func, std::size_t nrep)
{
    auto xspline = xs_func();
    array_t yspline(xspline.size());
    array_t yder2(x.size());

    for(std::size_t n = 0; n < nrep; ++n)
    {
        spline(x, y, yder2);
        xspline = xs_func();
        splint(x, y, yder2, xspline, yspline);

        update_path(x, y, 5e-5);
    }
}

int main()
{
    std::size_t nb_lines = 10;
    std::vector<array_t> x(nb_lines), y(nb_lines);

    double lo = .2, up = .8;
    std::size_t npoints = 15;

    auto yy = linspace(lo, up, nb_lines);
    for(std::size_t i = 0; i < x.size(); ++i)
    {
        std::tie(x[i], y[i]) = line(lo, up, yy[i], npoints);
        npoints++;
    }

    auto xs_func = [lo, up]()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0., 1.);

        std::size_t nsamples = 500;
        auto x = linspace(lo + .05, up - .05, nsamples);
        std::for_each(x.begin(), x.end(), [&dis, &gen](double& e){ e += 1e-3*dis(gen);});
        return x;
    };

    for(std::size_t i = 0; i < x.size(); ++i)
    {
        generative_art(x[i], y[i], xs_func, 1000);
    }

    return 0;
}