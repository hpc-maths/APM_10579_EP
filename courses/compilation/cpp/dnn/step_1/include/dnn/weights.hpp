#ifndef DNN_WEIGHTS
#define DNN_WEIGHTS

#include "types.hpp"

namespace dnn
{
    array_t random_vector(std::size_t size);
    matrix_t init_weights(std::size_t n_input, std::size_t n_output);
    void update_weights(double learning_rate, weights_t& weights, const weights_t& weight_gradient);
    void reset_weight_gradients(weights_t& weight_gradient);
    void update_gradients(const array_t& input, const matrix_t& activation, const matrix_t& delta, weights_t& weight_gradient);
}

#endif