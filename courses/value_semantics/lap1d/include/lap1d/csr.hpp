#ifndef LAP1D_CSR_HPP
#define LAP1D_CSR_HPP

#include <iostream>
#include <vector>

namespace lap1d
{
    class csr
    {
    public:
        csr(std::size_t nb_rows, std::size_t nb_cols);

        double* find_element(std::size_t i, std::size_t j);
        auto insert_element(std::size_t i, std::size_t j);

        double& operator()(std::size_t i, std::size_t j);

        std::size_t nb_rows() const;
        std::size_t nb_cols() const;

        auto val() const;
        auto row_ptr() const;
        auto col() const;
        
    private:
        std::size_t m_nb_rows;
        std::size_t m_nb_cols;
        std::vector<std::size_t> m_row_ptr;
        std::vector<std::size_t> m_col;
        std::vector<double> m_val;
    };

    std::vector<double> mat_mult(const csr& A, const std::vector<double>& x);

    std::ostream& operator<<(std::ostream& out, const csr& m);
}
#endif