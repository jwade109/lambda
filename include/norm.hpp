#ifndef LAMBDA_NORM_HPP
#define LAMBDA_NORM_HPP

#include <cmath>
#include <sstream>

#include <matrix.hpp>

namespace lambda
{

template <size_t N>
double euclidean_norm(const column_vector<N> &v)
{
    double normsq = lambda::inner_product(v, v);
    return std::sqrt(normsq);
}

template <size_t N>
double euclidean_norm(const row_vector<N> &v)
{
    return euclidean_norm(transpose(v));
}

template <size_t N>
column_vector<N> normalize(const column_vector<N> &v)
{
    double norm = euclidean_norm(v);
    if (norm == 0)
    {
        std::stringstream ss;
        ss << "Cannot normalize vector " << v
            << ", which is of zero norm";
        throw std::domain_error(ss.str());
    }
    return v/euclidean_norm(v);
}

template <size_t N>
row_vector<N> normalize(const row_vector<N> &v)
{
    double norm = euclidean_norm(transpose(v));
    if (norm == 0)
    {
        std::stringstream ss;
        ss << "Cannot normalize vector " << v
            << ", which is of zero norm";
        throw std::domain_error(ss.str());
    }
    return v/euclidean_norm(v);
}

} // namespace lambda

#endif // LAMBDA_NORM_HPP
