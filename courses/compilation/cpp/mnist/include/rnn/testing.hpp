#ifndef RNN_TESTING
#define RNN_TESTING

#include "types.hpp"
#include "propagation.hpp"

namespace rnn
{
    double evaluate(const matrix_t& input, const matrix_t& output, const weights_t& weights)
    {
        matrix_t aggregation, activation;
        for(auto& w: weights)
        {
            aggregation.emplace_back(array_t(w.size()));
            activation.emplace_back(array_t(w.size()));
        }

        double accuracy = 0;
        for(std::size_t i = 0; i < input.size(); ++i)
        {
            forward_propagation(input[i], weights, aggregation, activation);

            std::size_t predicted = std::distance(activation.back().cbegin(), std::max_element(activation.back().cbegin(), activation.back().cend()));
            std::size_t expected = std::distance(output[i].cbegin(), std::max_element(output[i].cbegin(), output[i].cend()));
            if (predicted == expected)
            {
                accuracy++;
            }
        }
        return 100*accuracy/input.size();
    }
}

#endif