#ifndef LAMBDA_DECOMPOSITION_HPP
#define LAMBDA_DECOMPOSITION_HPP

#include <tuple>

namespace lambda
{

template <size_t N, class T>
std::tuple<matrix<N, N, T>, matrix<N, N, T>>
decompose_lu(const matrix<N, N, T> &m)
{
    // TODO

    matrix<N, N, T> L, U;
    return std::make_tuple(L, U);
}

template <size_t M, size_t N, class T>
std::tuple<matrix<M, M, T>,
           matrix<M, M, T>,
           matrix<M, N, T>>
decompose_ldu(const matrix<N, N, T> &m)
{
    // TODO

    matrix<M, M, T> L, D;
    matrix<M, N, T> U;
    return std::make_tuple(L, D, U);
}

} // namespace lambda

#endif // LAMBDA_DECOMPOSITION_HPP

