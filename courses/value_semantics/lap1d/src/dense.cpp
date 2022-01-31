#include "lap1d/dense.hpp"

namespace lap1d
{
    matrix::matrix(std::size_t nb_rows, std::size_t nb_cols)
    : m_nb_rows(nb_rows)
    , m_nb_cols(nb_cols)
    , m_data(nb_rows * nb_cols)
    {}

    double& matrix::operator()(std::size_t i, std::size_t j)
    {
        return m_data[i * m_nb_cols + j];
    }

    const double& matrix::operator()(std::size_t i, std::size_t j) const
    {
        return m_data[i * m_nb_cols + j];
    }

    std::size_t matrix::nb_rows() const
    {
        return m_nb_rows;
    }

    std::size_t matrix::nb_cols() const
    {
        return m_nb_cols;
    }

    std::vector<double> mat_mult(const matrix& A, const std::vector<double>& x)
    {
        std::vector<double> y(A.nb_rows());
        for(std::size_t i = 0; i < A.nb_rows(); ++i)
        {
            double sum = 0.;
            for(std::size_t j = 0; j < A.nb_cols(); ++j)
            {
                sum += A(i, j)*x[j];
            }
            y[i] = sum;
        }
        return y;
    }
}