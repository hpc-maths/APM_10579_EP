#include <vector>

#include "types.hpp"

namespace art
{
    namespace spline
    {
        void spline(const array_t& xs, const array_t& ys, array_t& y2s);
        void splint(const array_t& xs, const array_t& ys, const array_t& y2s,
                    const array_t& x, array_t& y);
    }
}
