#include <cmath>
#include <random>

#include <generative/core.hpp>
#include <generative/spline.hpp>

#define pi 4.*std::atan(1)

namespace art
{
    namespace core
    {
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
    }
}

