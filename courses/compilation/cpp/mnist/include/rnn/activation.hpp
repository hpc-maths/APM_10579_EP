#ifndef RNN_ACTIVATION
#define RNN_ACTIVATION

#include <cmath>
namespace rnn
{
    double sigmoid(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }

    double sigmoid_grad(double x)
    {
        return sigmoid(x)*(1 - sigmoid(x));
    }
}

#endif