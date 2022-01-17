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

        void draw_pixel(cv::Mat& img, const array_t& xs, const array_t& ys, const std::array<uchar, 4>& rgba)
        {
            std::size_t width = img.cols;
            std::size_t height = img.rows;

            double alpha = 1 - 5e-3*rgba[3];
            for(std::size_t i = 0; i < xs.size(); ++i)
            {
                std::size_t newxs = xs[i]*width;
                std::size_t newys = ys[i]*height;
                if ((newxs >=0 and newxs < width) && (newys >=0 and newys < height))
                {
                    cv::Vec4b& data = img.at<cv::Vec4b>(newys, newxs);
                    for (std::size_t c=0; c<img.channels()-1; ++c)
                    {
                        data[c] = rgba[c];
                    }
                    double to_add = data[3] + rgba[3];
                    data[3] = (to_add > 255)? 255: to_add;
                }
            }
        }
    }
}

