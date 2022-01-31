#include <algorithm>

#include "lap1d/csr.hpp"

namespace lap1d
{
    csr::csr(std::size_t nb_rows, std::size_t nb_cols)
    : m_nb_rows(nb_rows)
    , m_nb_cols(nb_cols)
    , m_row_ptr(nb_rows + 1)
    {}

    double* csr::find_element(std::size_t i, std::size_t j)
    {
        if (m_row_ptr.size() == 0 || m_row_ptr[i] == m_row_ptr[i+1])
        {
            return nullptr;
        }
        auto it = std::find(m_col.cbegin() + m_row_ptr[i], 
                            m_col.cbegin() + m_row_ptr[i+1],
                            j);
        if (it != m_col.cbegin() + m_row_ptr[i+1])
        {
            std::ptrdiff_t dst = std::distance(m_col.cbegin(), it);
            return &(*(m_val.begin() + dst));
        }

        return nullptr;
    }

    auto csr::insert_element(std::size_t i, std::size_t j)
    {
        auto it = std::find_if(m_col.begin() + m_row_ptr[i], 
                                m_col.begin() + m_row_ptr[i+1],
                                [j](auto e){return e >= j;});
        if (it == m_col.begin() + m_row_ptr[i+1] || *it != j)
        {
            auto it_val = m_val.insert(m_val.begin() + std::distance(m_col.begin(), it), 0);
            m_col.insert(it, j);
            std::transform(m_row_ptr.begin() + i + 1, m_row_ptr.end(), m_row_ptr.begin() + i + 1, [](auto x){return x+1;});
            return it_val;
        }
        return m_val.end();
    }

    double& csr::operator()(std::size_t i, std::size_t j)
    {
        auto it = find_element(i, j);
        if (it == nullptr)
        {
            return *insert_element(i, j);
        }
        return *it;
    }

    std::size_t csr::nb_rows() const
    {
        return m_nb_rows;
    }

    std::size_t csr::nb_cols() const
    {
        return m_nb_cols;
    }

    auto csr::val() const
    {
        return m_val;
    }
    
    auto csr::row_ptr() const
    {
        return m_row_ptr;
    }
    
    auto csr::col() const
    {
        return m_col;
    }

    std::vector<double> mat_mult(const csr& A, const std::vector<double>& x)
    {
        std::vector<double> y(A.nb_rows());
        for(std::size_t i = 0; i < A.nb_rows(); ++i)
        {
            double sum = 0.;
            for(std::size_t j = A.row_ptr()[i]; j < A.row_ptr()[i + 1]; ++j)
            {
                sum += A.val()[j]*x[A.col()[j]];
            }
            y[i] = sum;
        }
        return y;
    }

    std::ostream& operator<<(std::ostream& out, const csr& m)
    {
        for(std::size_t i = 0; i < m.nb_rows(); ++i)
        {
            for(std::size_t j = m.row_ptr()[i]; j < m.row_ptr()[i + 1]; ++j)
            {
                out << "( " << i << ", " << m.col()[j] << " ): " << m.val()[j] << " ";
            }
            if (m.row_ptr()[i] != m.row_ptr()[i+1])
            {
                out << std::endl;
            }
        }
        return out;
    }
}