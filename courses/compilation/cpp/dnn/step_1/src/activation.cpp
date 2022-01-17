#include <numeric>
#include <cmath>

#include "dnn/activation.hpp"

namespace dnn
{
    double aggregation_func(const std::vector<double>& input, const std::vector<double>& weights, double bias)
    {
        return std::inner_product(input.begin(), input.end(), weights.begin(), 0.) + bias;
    }

    double aggregation_func(const std::vector<double>& input, const std::vector<double>& weights)
    {
        return std::inner_product(input.begin(), input.end(), weights.begin(), 0.);
    }

    double sigmoid(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }

    double sigmoid_grad(double x)
    {
        return sigmoid(x)*(1 - sigmoid(x));
    }
}
