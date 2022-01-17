#include <dnn/propagation.hpp>
#include <dnn/activation.hpp>

namespace dnn
{
    void forward_propagation(const array_t& input, const weights_t& weights, matrix_t& aggregation, matrix_t& activation)
    {
        std::size_t layers = weights.size();
        for(std::size_t layer = 0; layer < layers; ++layer)
        {
            std::size_t neurons = weights[layer].size();
            for(std::size_t neuron = 0; neuron < neurons; ++neuron)
            {
                if (layer == 0)
                {
                    aggregation[layer][neuron] = aggregation_func(input, weights[layer][neuron]);
                }
                else
                {
                    aggregation[layer][neuron] = aggregation_func(activation[layer-1], weights[layer][neuron]);
                }
                activation[layer][neuron] = sigmoid(aggregation[layer][neuron]);
            }
        }
    }

    void backward_propagation(const array_t& input, const array_t& expected,
                              const weights_t& weights, const matrix_t& aggregation,
                              const matrix_t& activation, matrix_t& delta)
    {
        for(std::size_t layer = weights.size() - 1; layer != std::size_t(-1); --layer)
        {
            for(std::size_t neuron = 0; neuron < weights[layer].size(); ++neuron)
            {
                if (layer == weights.size() - 1)
                {
                    double cost_prime = activation[layer][neuron] - expected[neuron];
                    delta[layer][neuron] = cost_prime * sigmoid_grad(aggregation[layer][neuron]);
                }
                else
                {
                    double sum = 0.;
                    for(std::size_t i = 0; i < weights[layer+1].size(); ++i)
                    {
                        sum += weights[layer+1][i][neuron] * delta[layer+1][i];
                    }
                    delta[layer][neuron] = sum * sigmoid_grad(aggregation[layer][neuron]);
                }
            }
        }
    }
}