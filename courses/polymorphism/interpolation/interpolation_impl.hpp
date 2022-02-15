#ifndef INTERPOLATION_IMPL_HPP
#define INTERPOLATION_IMPL_HPP

#include <vector>

namespace hpc
{
    class interpolation_impl
    {
    public:

        double interpolate(double x) const;
    };

    /*class linear_interpolation : public interpolation_impl
    {
    };*/

    class spline_interpolation : public interpolation_impl
    {
    };
}

#endif

