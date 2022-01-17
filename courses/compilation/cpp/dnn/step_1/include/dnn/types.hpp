#ifndef DNN_TYPES
#define DNN_TYPES

#include <vector>

namespace dnn
{
    using array_t = std::vector<double>;
    using matrix_t = std::vector<array_t>;

    using weights_t = std::vector<matrix_t>;
    using aggregation_t = matrix_t;
    using activation_t = matrix_t;
}

#endif