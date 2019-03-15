#ifndef LAMBDA_ECHELON_HPP
#define LAMBDA_ECHELON_HPP

#include <sstream>
#include <algorithm>

namespace lambda
{

template <size_t M, size_t N, class T>
matrix<M, N, T> swap_rows(
    const matrix<M, N, T> &m, size_t r1, size_t r2)
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

template <size_t M, size_t N, class T>
matrix<M, N, T> swap_cols(
    const matrix<M, N, T> &m, size_t c1, size_t c2)
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

template <size_t M, size_t N, class T>
matrix<M, N, T> rref(const matrix<M, N, T> &m)
{
    auto ret = m;

    static_assert(M > 0 && N > 0, "Matrix must be atleast 1x1 "
        "to compute reduced row echelon form");

    size_t lead = 0;
    for (size_t r = 0; r < M; ++r)
    {
        size_t i = r;
        while (ret(i, lead) == 0)
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
        if (ret(r, lead) != 0)
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

template <class T>
matrix<1, 1, T> rref(const matrix<1, 1, T> &m)
{
    return m;
}

} // namespace lambda

#endif // LAMBDA_ECHELON_HPP
