#include <algorithm>
#include <iostream>

#include <dnn/testing.hpp>
#include <dnn/training.hpp>
#include <dnn/propagation.hpp>
#include <dnn/weights.hpp>

namespace dnn
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

    weights_t training(const matrix_t& input, const matrix_t& expected,
                       const std::vector<std::size_t>& hidden_layers, double learning_rate, std::size_t epochs)
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

                backward_propagation(input[i], expected[i], weights, aggregation, activation, delta);
                update_gradients(input[i], activation, delta, weight_gradient);

                update_weights(learning_rate, weights, weight_gradient);
            }
        }

        return weights;
    }
}