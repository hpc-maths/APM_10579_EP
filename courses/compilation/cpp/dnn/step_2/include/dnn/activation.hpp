#ifndef DNN_ACTIVATION
#define DNN_ACTIVATION

#include <vector>

namespace dnn
{
    double aggregation_func(const std::vector<double>& input, const std::vector<double>& weights, double bias);
    double aggregation_func(const std::vector<double>& input, const std::vector<double>& weights);

    double sigmoid(double x);
    double sigmoid_grad(double x);
}

#endif