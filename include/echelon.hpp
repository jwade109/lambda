#ifndef LAMBDA_ECHELON_HPP
#define LAMBDA_ECHELON_HPP

#include <sstream>
#include <algorithm>

#include <matrix.hpp>

/*!
    \file
    \brief Implements RREF matrix reduction, as well as
           some convenient matrix manipulation operations.
*/

namespace lambda
{

/// \brief Swap two rows in a matrix.
template <size_t M, size_t N, typename R>
matrix<M, N, R> swap_rows(const matrix<M, N, R> &m, size_t r1, size_t r2)
{
    if (r1 >= M)
    {
        std::stringstream ss;
        ss << "Row " << r1 << " is out of bounds of "
            << M << "x" << N << " matrix";
        throw std::out_of_range(ss.str());
    }
    if (r2 >= M)
    {
        std::stringstream ss;
        ss << "Row " << r2 << " is out of bounds of "
            << M << "x" << N << " matrix";
        throw std::out_of_range(ss.str());
    }

    auto ret = m;
    for (size_t i = 0; i < N; ++i)
    {
        std::swap(ret(r1, i), ret(r2, i));
    }
    return ret;
}

/// \brief Swap two columns in a matrix.
template <size_t M, size_t N, typename R>
matrix<M, N, R> swap_cols(const matrix<M, N, R> &m, size_t c1, size_t c2)
{
    if (c1 >= M)
    {
        std::stringstream ss;
        ss << "Column " << c1 << " is out of bounds of "
            << M << "x" << N << " matrix";
        throw std::out_of_range(ss.str());
    }
    if (c2 >= M)
    {
        std::stringstream ss;
        ss << "Column " << c2 << " is out of bounds of "
            << M << "x" << N << " matrix";
        throw std::out_of_range(ss.str());
    }

    auto ret = m;
    for (size_t i = 0; i < M; ++i)
    {
        std::swap(ret(i, c1), ret(i, c2));
    }
    return ret;
}

/// \brief Get the RREF form of a matrix.
template <size_t M, size_t N, typename R>
matrix<M, N, R> rref(const matrix<M, N, R> &m)
{
    auto ret = m;
    size_t lead = 0;
    for (size_t r = 0; r < M; ++r)
    {
        size_t i = r;
        while (ret(i, lead) == R(0))
        {
            ++i;
            if (M == i)
            {
                i = r;
                ++lead;
                if (N == lead)
                {
                    return ret;
                }
            }
        }
        swap_rows(ret, i, r);
        if (ret(r, lead) != R(0))
        {
            auto div = ret(r, lead);
            for (size_t k = 0; k < N; ++k)
            {
                ret(r, k) /= div;
            }
        }
        for (size_t p = 0; p < M; ++p)
        {
            if (p != r)
            {
                auto mult = ret(p, lead);
                for (size_t k = 0; k < N; ++k)
                {
                    ret(p, k) -= mult*ret(r, k);
                }
            }
        }
        ++lead;
    }
    return ret;
}

/// \brief Get the RREF of a 1x1 matrix.
template <typename R>
matrix<1, 1, R> rref(const matrix<1, 1, R> &m)
{
    return m;
}

/// \brief Compute the inverse of a square matrix.
template <size_t N, typename R>
matrix<N, N, R> inverse(const matrix<N, N, R> &mat)
{
    if (!is_invertible(mat))
    {
        std::stringstream ss;
        ss << "Cannot invert matrix " << mat
            << ", which is singular";
        throw std::domain_error(ss.str());
    }
    auto reduced = rref(augment(mat, identity<N, N>()));
    matrix<N, N> inv;
    for (size_t r = 0; r < N; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            inv(r, c) = reduced(r, N + c);
        }
    }
    return inv;
}

/// \brief Returns the matrix produced by excluding row i, column j
/// from the given matrix.
template <size_t M, size_t N, typename R>
matrix<M-1, N-1, R> submatrix(const matrix<M, N, R> &m, size_t i, size_t j)
{
    matrix<M-1, N-1, R> ret;
    for (size_t r = 0; r < M-1; ++r)
    {
        for (size_t c = 0; c < N-1; ++c)
        {
            size_t get_row = r < i ? r : r + 1;
            size_t get_col = c < j ? c : c + 1;
            ret.at(r, c) = m.at(get_row, get_col);
        }
    }
    return ret;
}

/// \brief Gets the cofactor expansion at a given index in a matrix.
template <size_t M, size_t N, typename R>
R cofactor_expansion(const matrix<M, N, R> &m, size_t i, size_t j)
{
    return det(submatrix(m, i, j));
}

template <typename R>
std::array<R, 4> characteristic_polynomial(const matrix<3, 3, R> &m)
{
    std::array<R, 4> coefficients;
    coefficients[0] = det(m);
    coefficients[1] = cofactor_expansion(m, 0, 0) +
                      cofactor_expansion(m, 1, 1) +
                      cofactor_expansion(m, 2, 2);
    coefficients[2] = -trace(m);
    coefficients[3] = 1;
    return coefficients;
}

template <typename R>
std::array<R, 3> characteristic_polynomial(const matrix<2, 2, R> &m)
{
    std::array<R, 3> coefficients;
    coefficients[0] = det(m);
    coefficients[1] = -trace(m);
    coefficients[2] = 1;
    return coefficients;
}

template <typename R>
std::array<std::complex<R>, 2> roots(const std::array<std::complex<R>, 3> &coefficients)
{
    auto a = std::complex<double>(coefficients[2]);
    auto b = std::complex<double>(coefficients[1]);
    auto c = std::complex<double>(coefficients[0]);

    auto disc = std::pow(b, 2) - 4.0*a*c;
    auto r1 = (-b + std::sqrt(disc))/(2.0*a);
    auto r2 = (-b - std::sqrt(disc))/(2.0*a);
    return { r1, r2 };
}

} // namespace lambda

#endif // LAMBDA_ECHELON_HPP
