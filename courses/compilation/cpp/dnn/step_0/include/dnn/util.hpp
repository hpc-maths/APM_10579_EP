#ifndef DNN_UTIL
#define DNN_UTIL

#include <iostream>

#include "types.hpp"

namespace dnn
{
    template <class InputIt1, class InputIt2, class T, class BinaryTransformOp, class BinaryReduceOp>
    T transform_reduce(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init, BinaryTransformOp tr_op, BinaryReduceOp red_op)
    {
        T res = init;
        while (first1 != last1)
        {
            res = red_op(res, tr_op(*first1++, *first2++));
        }
        return res;
    }

    template <class InputIt1, class InputIt2, class T, class BinaryTransformOp>
    T transform_reduce(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init, BinaryTransformOp tr_op)
    {
        return transform_reduce(first1, last1, first2, init, tr_op, std::plus<>());
    }

    template <class InputIt1, class InputIt2, class T>
    T transform_reduce(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init)
    {
        return transform_reduce(first1, last1, first2, init, std::multiplies<>());
    }

    void print(const weights_t& data)
    {
        for(std::size_t layer = 0; layer < data.size(); ++layer)
        {
            for(std::size_t neuron = 0; neuron < data[layer].size(); ++neuron)
            {
                std::cout << "[" << layer << "][" << neuron << "] = { ";
                for(std::size_t i = 0; i < data[layer][neuron].size(); ++i)
                {
                    std::cout << data[layer][neuron][i] << ", ";
                }
                std::cout << "}" << std::endl;
            }
        }
    }

    void print(const matrix_t& data)
    {
        for(std::size_t layer = 0; layer < data.size(); ++layer)
        {
            std::cout << "[" << layer << "] = { ";
            for(std::size_t neuron = 0; neuron < data[layer].size(); ++neuron)
            {
                std::cout << data[layer][neuron] << ", ";
            }
            std::cout << "}" << std::endl;
        }
    }
}
#endif