#ifndef ART_CORE
#define ART_CORE

#include "types.hpp"
#include "spline.hpp"

namespace art
{
    namespace core
    {
        void update_path(array_t& x, array_t& y, double scale_value);
    }

    template<class Func>
    void generative_art(array_t& x, array_t& y, Func&& xs_func, std::size_t nrep)
    {
        auto xspline = xs_func();
        array_t yspline(xspline.size());
        array_t yder2(x.size());

        for(std::size_t n = 0; n < nrep; ++n)
        {
            spline::spline(x, y, yder2);
            xspline = xs_func();
            spline::splint(x, y, yder2, xspline, yspline);

            core::update_path(x, y, 5e-5);
        }
    }
}

#endif
