#ifndef INTERPOLATION_IMPL_HPP
#define INTERPOLATION_IMPL_HPP

#include <vector>

namespace hpc
{
    class interpolation_impl
    {
    public:

        double interpolate() const;
    };

    /*class linear_interpolation : public interpolation
    {
    };*/

    class spline_interpolation : public interpolation
    {
    };
}

#endif

