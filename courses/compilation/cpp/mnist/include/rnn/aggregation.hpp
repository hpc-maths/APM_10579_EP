#ifndef RNN_AGGREGATION
#define RNN_AGGREGATION

#include <algorithm>
#include <vector>

namespace rnn
{
    double aggregation_func(const std::vector<double>& input, const std::vector<double>& weights, double bias)
    {
        return std::inner_product(input.begin(), input.end(), weights.begin(), 0.) + bias;
    }

    double aggregation_func(const std::vector<double>& input, const std::vector<double>& weights)
    {
        return std::inner_product(input.begin(), input.end(), weights.begin(), 0.);
    }
}
#endif