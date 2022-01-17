#ifndef RNN_TRAINING
#define RNN_TRAINING

#include <algorithm>
#include <random>
#include <vector>
#include <chrono>

#include "aggregation.hpp"
#include "activation.hpp"
#include "propagation.hpp"
#include "types.hpp"
#include "util.hpp"
#include "weights.hpp"

namespace rnn
{
    weights_t training(const matrix_t& input, const matrix_t& expected,
                       const std::vector<std::size_t>& hidden_layers, double learning_rate=0.5, std::size_t epochs=20)
    {
        weights_t weights, weight_gradient;

        std::size_t n_inputs = input[0].size();
        for(auto n: hidden_layers)
        {
            weights.emplace_back(init_weights(n_inputs, n));
            weight_gradient.emplace_back(init_weights(n_inputs, n));
            n_inputs = n;
        }
        weights.emplace_back(init_weights(n_inputs, expected[0].size()));
        weight_gradient.emplace_back(init_weights(n_inputs, expected[0].size()));

        matrix_t aggregation, activation, delta;
        for(auto& w: weights)
        {
            aggregation.emplace_back(array_t(w.size()));
            activation.emplace_back(array_t(w.size()));
            delta.emplace_back(array_t(w.size()));
        }

        for(std::size_t epoch = 0; epoch < epochs; ++epoch)
        {
            std::cout << "epoch: " << epoch << std::endl;
            double error = 0;
            for(std::size_t i = 0; i < input.size(); ++i)
            {
                reset_weight_gradients(weight_gradient);
                forward_propagation(input[i], weights, aggregation, activation);

                error += transform_reduce(expected[i].cbegin(), expected[i].cend(), activation.back().cbegin(), 0., [](auto a, auto b){ return (a-b)*(a-b);});

                backward_propagation(input[i], expected[i], weights, aggregation, activation, delta);
                update_gradients(input[i], activation, delta, weight_gradient);

                update_weights(learning_rate, weights, weight_gradient);
            }
            std::cout << "error " << error << std::endl;
        }

        return weights;
    }
}
#endif