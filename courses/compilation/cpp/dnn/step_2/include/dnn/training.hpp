#ifndef DNN_TRAINING
#define DNN_TRAINING

#include <vector>

#include "types.hpp"

namespace dnn
{
    weights_t training(const matrix_t& input, const matrix_t& expected,
                       const std::vector<std::size_t>& hidden_layers, double learning_rate=0.5, std::size_t epochs=20);
}
#endif