#include <rnn/datasets.hpp>
#include <rnn/training.hpp>
#include <rnn/testing.hpp>

int main()
{
    // auto output = rnn::dataset::iris(80);
    auto output = rnn::dataset::mnist(15);

    std::vector<std::vector<double>> train_input, train_output;
    std::tie(train_input, train_output) = output.first;

    std::vector<std::vector<double>> test_input, test_output;
    std::tie(test_input, test_output) = output.second;

    std::cout << train_input.size() << std::endl;
    auto weights = rnn::training(train_input, train_output, {32, 64, 32}, 0.5, 18);
    std::cout << "accuracy: " << rnn::evaluate(test_input, test_output, weights) << std::endl;

    return 0;
}