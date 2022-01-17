#ifndef DNN_PROPAGATION
#define DNN_PROPAGATION

#include "types.hpp"

namespace dnn
{
    void forward_propagation(const array_t& input, const weights_t& weights, matrix_t& aggregation, matrix_t& activation);
    void backward_propagation(const array_t& input, const array_t& expected,
                              const weights_t& weights, const matrix_t& aggregation,
                              const matrix_t& activation, matrix_t& delta);
}
#endif