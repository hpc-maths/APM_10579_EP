#ifndef RNN_WEIGHTS
#define RNN_WEIGHTS

#include <algorithm>
#include <random>

#include "types.hpp"

namespace rnn
{
    auto random_vector(std::size_t size)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        array_t output(size);
        std::generate(output.begin(), output.end(), [&gen, &dis](){return dis(gen);});
        return output;
    }

    auto init_weights(std::size_t n_input, std::size_t n_output)
    {
        matrix_t weights;

        for(std::size_t i = 0; i < n_output; ++i)
        {
            weights.emplace_back(random_vector(n_input));
        }

        return weights;
    }

    void update_weights(double learning_rate, weights_t& weights, const weights_t& weight_gradient)
    {
        for(std::size_t layer = 0; layer < weight_gradient.size(); ++layer)
        {
            for(std::size_t neuron = 0; neuron < weight_gradient[layer].size(); ++neuron)
            {
                for(std::size_t i = 0; i < weight_gradient[layer][neuron].size(); ++i)
                {
                    weights[layer][neuron][i] -= learning_rate * weight_gradient[layer][neuron][i];
                }
            }
        }
    }

    void reset_weight_gradients(weights_t& weight_gradient)
    {
        for(std::size_t layer = 0; layer < weight_gradient.size(); ++layer)
        {
            for(std::size_t neuron = 0; neuron < weight_gradient[layer].size(); ++neuron)
            {
                std::fill(weight_gradient[layer][neuron].begin(), weight_gradient[layer][neuron].end(), 0.);
            }
        }
    }

    void update_gradients(const array_t& input, const matrix_t& activation, const matrix_t& delta, weights_t& weight_gradient)
    {
        for(std::size_t layer = 0; layer < weight_gradient.size(); ++layer)
        {
            for(std::size_t neuron = 0; neuron < weight_gradient[layer].size(); ++neuron)
            {
                for(std::size_t i = 0; i < weight_gradient[layer][neuron].size(); ++i)
                {
                    if (layer == 0)
                    {
                        weight_gradient[layer][neuron][i] += delta[layer][neuron]*input[i];
                    }
                    else
                    {
                        weight_gradient[layer][neuron][i] += delta[layer][neuron]*activation[layer-1][i];
                    }
                }
            }
        }
    }
}

#endif