#ifndef DNN_TESTING
#define DNN_TESTING

#include "types.hpp"

namespace dnn
{
    double evaluate(const matrix_t& input, const matrix_t& output, const weights_t& weights);
}

#endif