#include <rnn/datasets.hpp>
#include <rnn/training.hpp>
#include <rnn/testing.hpp>

int main()
{
    auto output = rnn::dataset::iris(80);

    std::vector<std::vector<double>> train_input, train_output;
    std::tie(train_input, train_output) = output.first;

    std::vector<std::vector<double>> test_input, test_output;
    std::tie(test_input, test_output) = output.second;

    auto weights = rnn::training(train_input, train_output, {10}, 0.5, 30);
    std::cout << "accuracy: " << rnn::evaluate(test_input, test_output, weights) << std::endl;

    return 0;
}