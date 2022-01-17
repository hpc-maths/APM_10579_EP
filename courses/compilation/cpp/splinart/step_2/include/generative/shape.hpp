#ifndef ART_SHAPE
#define ART_SHAPE

#include "types.hpp"

namespace art
{
    namespace shape
    {
        // auto linspace(double begin, double end, std::size_t n);
        // auto line(double begin, double end, double ypos=.5, std::size_t n=50);

        array_t linspace(double begin, double end, std::size_t n);
        std::pair<array_t, array_t> line(double begin, double end, double ypos=.5, std::size_t n=50);
    }
}

#endif