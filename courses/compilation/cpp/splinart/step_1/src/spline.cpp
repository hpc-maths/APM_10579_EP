#include <algorithm>

#include <generative/spline.hpp>

namespace art
{
    namespace spline
    {
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

        namespace algorithm
        {
            auto searchsorted(const array_t& v, const array_t& t)
            {
                std::vector<std::size_t> out(t.size());
                std::for_each(t.begin(), t.cend(), [&, n=0](const float &e) mutable{
                    auto lower = std::lower_bound (v.begin(), v.end(), e);
                    out[n++] = std::distance(v.begin(), lower);
                });
                return out;
            }
        }

        void splint(const array_t& xs, const array_t& ys, const array_t& y2s,
                    const array_t& x, array_t& y)
        {
            auto k = algorithm::searchsorted(xs, x);

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

    }
}
