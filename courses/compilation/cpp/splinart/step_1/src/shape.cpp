#include <utility>

#include <generative/shape.hpp>
#include <generative/types.hpp>

namespace art
{
    namespace shape
    {
        array_t linspace(double begin, double end, std::size_t n)
        {
            array_t out(n);
            double step = (end - begin)/(n-1);

            for(std::size_t i=0; i<n; ++i)
            {
                out[i] = begin + step*i;
            }

            return out;
        }

        std::pair<array_t, array_t> line(double begin, double end, double ypos, std::size_t n)
        {
            auto x = linspace(begin, end, n);
            array_t y(n, ypos);
            return std::make_pair(x, y);
        }
    }
}