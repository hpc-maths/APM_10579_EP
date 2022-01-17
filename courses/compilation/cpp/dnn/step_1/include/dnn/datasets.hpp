#ifndef DNN_IO
#define DNN_IO

#include <map>
#include <random>
#include <utility>
#include <vector>

#include "csv.hpp"
#include "types.hpp"

namespace dnn
{
    namespace dataset
    {
        using data_t = std::vector<std::vector<double>>;

        void shuffle(data_t& input, data_t& output)
        {
            std::vector<std::size_t> indices(input.size());
            std::generate(indices.begin(), indices.end(), [n = 0]() mutable {return n++;});

            std::random_device rd;
            std::mt19937 g(rd());

            std::shuffle(indices.begin(), indices.end(), g);

            for(std::size_t i=0; i<input.size(); ++i)
            {
                for(std::size_t j=0; j<input[i].size(); ++j)
                {
                    double tmp = input[i][j];
                    input[i][j] = input[indices[i]][j];
                    input[indices[i]][j] = tmp;
                }

                for(std::size_t j=0; j<output[i].size(); ++j)
                {
                    double tmp = output[i][j];
                    output[i][j] = output[indices[i]][j];
                    output[indices[i]][j] = tmp;
                }
            }
        }

        void normalize(data_t& data)
        {
            std::vector<double> max(data[0].size(), std::numeric_limits<double>::min());
            for(std::size_t i=0; i<data.size(); ++i)
            {
                for(std::size_t j=0; j<data[i].size(); ++j)
                {
                    if (abs(data[i][j]) > max[j])
                    {
                        max[j] = abs(data[i][j]);
                    }
                }
            }

            for(std::size_t i=0; i<data.size(); ++i)
            {
                for(std::size_t j=0; j<data[i].size(); ++j)
                {
                    data[i][j] /= max[j];
                }
            }

        }

        template<class Func>
        auto read_csv_data(std::string filename, double pourcent, std::size_t n_outputs, Func&& transform)
        {
            csv::CSVReader reader(filename);
            csv::CSVFileInfo info = csv::get_file_info(filename);

            data_t input(info.n_rows + 1, std::vector<double>(info.n_cols-1));
            data_t output(info.n_rows + 1, std::vector<double>(n_outputs));

            std::size_t irow = 0;
            for (csv::CSVRow& row: reader)
            {
                for(std::size_t i=0; i<info.n_cols-1; ++i)
                {
                    input[irow][i] = row[i].get<double>();
                }
                std::string col = row[info.n_cols-1].get<>();
                output[irow][transform(col)] = 1;
                irow++;
            }

            shuffle(input, output);
            normalize(input);

            std::size_t row_training = pourcent/100 * (info.n_rows + 1);
            std::size_t row_testing = (info.n_rows + 1) - row_training;

            data_t train_input(row_training, std::vector<double>(info.n_cols-1));
            data_t train_output(row_training, std::vector<double>(n_outputs));

            data_t test_input(row_testing, std::vector<double>(info.n_cols-1));
            data_t test_output(row_testing, std::vector<double>(n_outputs));

            std::copy(input.cbegin(), input.cbegin()+row_training, train_input.begin());
            std::copy(output.cbegin(), output.cbegin()+row_training, train_output.begin());

            std::copy(input.cbegin()+row_training, input.cend(), test_input.begin());
            std::copy(output.cbegin()+row_training, output.cend(), test_output.begin());

            return std::pair<std::pair<data_t, data_t>, std::pair<data_t, data_t>>({train_input, train_output}, {test_input, test_output});
        }

        auto mnist(double pourcent=80)
        {
            return read_csv_data("mnist_784.csv", pourcent, 10, [](auto data){return atoi(data.c_str());});
        }

        auto iris(double pourcent=80)
        {
            std::map<std::string, std::size_t> iris_type{{"Iris-setosa", 0},
                                                         {"Iris-versicolor", 1},
                                                         {"Iris-virginica", 2}};

            return read_csv_data("dataset_61_iris.csv", pourcent, 3, [&iris_type](auto data){return iris_type[data];});
        }
    }
}
#endif