#ifndef NORM_H
#define NORM_H

#include <cmath>

namespace lambda
{

template <size_t N, class T>
T euclidean_norm(const row_vector<N, T> &v)
{
    auto normsq = lambda::inner_product(v, v);
    return std::sqrt(normsq);
}

template <size_t N, class T>
T euclidean_norm(const column_vector<N, T> &v)
{
    auto normsq = lambda::inner_product(v, v);
    return std::sqrt(normsq);
}



} // namespace lambda

#endif // NORM_H
