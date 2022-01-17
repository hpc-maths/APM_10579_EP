#ifndef RNN_TYPES
#define RNN_TYPES

#include <vector>

namespace rnn
{
    using array_t = std::vector<double>;
    using matrix_t = std::vector<array_t>;

    using weights_t = std::vector<matrix_t>;
    using aggregation_t = matrix_t;
    using activation_t = matrix_t;
}

#endif