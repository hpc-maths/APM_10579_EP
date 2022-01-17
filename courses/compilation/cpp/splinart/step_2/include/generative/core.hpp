#ifndef ART_CORE
#define ART_CORE

#include <opencv2/opencv.hpp>

#include "types.hpp"
#include "spline.hpp"

namespace art
{
    namespace core
    {
        void update_path(array_t& x, array_t& y, double scale_value);
        void draw_pixel(cv::Mat& img, const array_t& xs, const array_t& ys, const std::array<uchar, 4>& rgba);
    }

    template<class Func>
    void generative_art(cv::Mat& img, array_t& x, array_t& y, Func&& xs_func, std::size_t nrep, const std::array<uchar, 4>& rgba)
    {
        auto xspline = xs_func();
        array_t yspline(xspline.size());
        array_t yder2(x.size());

        for(std::size_t n = 0; n < nrep; ++n)
        {
            spline::spline(x, y, yder2);
            xspline = xs_func();
            spline::splint(x, y, yder2, xspline, yspline);

            core::draw_pixel(img, xspline, yspline, rgba);
            core::update_path(x, y, 5e-5);
        }
    }
}

#endif
