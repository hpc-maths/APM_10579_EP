#ifndef LAP1D_DENSE_HPP
#define LAP1D_DENSE_HPP

#include <vector>

namespace lap1d
{
    class matrix
    {
    public:
        matrix(std::size_t nb_rows, std::size_t nb_cols);

        double& operator()(std::size_t i, std::size_t j);
        const double& operator()(std::size_t i, std::size_t j) const;

        std::size_t nb_rows() const;
        std::size_t nb_cols() const;

        // matrix(std::size_t nb_rows, std::size_t nb_cols)
        // : m_nb_rows(nb_rows)
        // , m_nb_cols(nb_cols)
        // , m_data(nb_rows * nb_cols)
        // {}

        // double& operator()(std::size_t i, std::size_t j)
        // {
        //     return m_data[i * m_nb_cols + j];
        // }

        // const double& operator()(std::size_t i, std::size_t j) const
        // {
        //     return m_data[i * m_nb_cols + j];
        // }

        // std::size_t nb_rows() const
        // {
        //     return m_nb_rows;
        // }

        // std::size_t nb_cols() const
        // {
        //     return m_nb_cols;
        // }

    private:
        std::size_t m_nb_rows;
        std::size_t m_nb_cols;
        std::vector<double> m_data;
    };

    std::vector<double> mat_mult(const matrix& A, const std::vector<double>& x);
}

#endif