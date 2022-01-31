#ifndef LAP1D_CG_HPP
#define LAP1D_CG_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

namespace lap1d
{
    double dot(const std::vector<double>& a, const std::vector<double>& b);
    double norm(const std::vector<double>& x);
    void axpy(std::vector<double>& y, double alpha, const std::vector<double>& x);
    void aypx(std::vector<double>& y, double alpha, const std::vector<double>& x);

    template <class Matrix>
    void cg(const Matrix& A, std::vector<double>& x, const std::vector<double>& b, std::size_t max_ite = 1000, double tol = 1e-6)
    {
        auto r = mat_mult(A, x);
        std::transform(b.begin(), b.end(), r.begin(), r.begin(), std::minus<double>{});

        std::vector<double> p;
        std::copy(r.cbegin(), r.cend(), std::back_inserter(p));

        double res_0 = norm(r);
        if (res_0 == 0)
        {
            res_0 = 1;
        }
        double residual = 1;

        double ps1 = dot(r, r);
        std::size_t ite = 1;

        while (ite < max_ite && residual > tol)
        {
            auto Ap = mat_mult(A, p);

            double alpha = ps1/dot(Ap, p);
            axpy(x, alpha, p);
            axpy(r, -alpha, Ap);

            residual = norm(r)/res_0;

            double ps2 = dot(r, r);
            double beta = ps2/ps1;

            aypx(p, beta, r);
            ps1 = ps2;

            std::cout << "Conjugate gradient: ite " << ite << " residual " << residual << std::endl;
            ite++;
        }
    }

}

#endif