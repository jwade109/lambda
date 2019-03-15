#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <vector>
#include <cstdint>
#include <iostream>
#include <sstream>

namespace lambda
{

template <size_t M, size_t N, class T = double> class matrix
{
    public:

    matrix() : _data() { }

    template <typename T2>
    matrix(const matrix<M, N, T2> &other) : _data(other.data()) { }

    template <typename ...T2, typename std::enable_if<
        sizeof...(T2) == M*N, int>::type = 0>
    matrix(T2... args) : _data({static_cast<T>(args)...}) { }

    T operator () (size_t i, size_t j) const
    {
        return _data[N*i + j];
    }

    T& operator () (size_t i, size_t j)
    {
        return _data[N*i + j];
    }

    T at(size_t i, size_t j) const
    {
        range_check(i, j);
        return _data[N*i + j];
    }

    T& at(size_t i, size_t j)
    {
        range_check(i, j);
        return _data[N*i + j];
    }

    const std::array<T, M*N>& data() const
    {
        return _data;
    }

    private:

    std::array<T, M*N> _data;

    static void range_check(size_t i, size_t j)
    {
        if (N*i + j >= N*M)
        {
            std::stringstream ss;
            ss << "Cannot access element (" << i << ", " << j
                << ") of " << M << "x" << N << " matrix";
            throw std::out_of_range(ss.str());
        }
    }
};

template <size_t N, class T = double>
using column_vector = matrix<N, 1, T>; 
template <size_t N, class T = double>
using row_vector = matrix<1, N, T>;
template <size_t N, class T = double>
using vector = column_vector<N, T>;

const static vector<3, uint8_t>
    unitx(1, 0, 0), unity(0, 1, 0), unitz(0, 0, 1);

template <size_t M, size_t N, class T>
std::ostream& operator << (std::ostream &os, const matrix<M, N, T> &m)
{
    os.precision(2);
    os.setf(std::ios::fixed);
    os << "[";
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            os << +m(i, j);
            if (j < N - 1) os << ", ";
        }
        if (i < M - 1) os << "; ";
    }
    os << "]";
}

template <size_t M, size_t N, class T1, class T2>
auto operator * (const matrix<M, N, T1> &m, T2 scalar)
-> matrix<M, N, decltype(m(0,0)*scalar)>
{
    auto ret = m;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(i, j) *= scalar;
        }
    }
    return ret;
}

template <size_t M, size_t N, class T1, class T2>
auto operator * (T1 scalar, const matrix<M, N, T2> &m)
-> matrix<M, N, decltype(m(0,0)*scalar)>
{
    return m*scalar;
}

template <size_t M, size_t N, class T1, class T2>
auto operator / (const matrix<M, N, T1> &m, T2 divisor)
-> matrix<M, N, decltype(m(0,0)/divisor)>
{
    return m*(1.0/divisor);
}

template <size_t M, size_t N, class T1, class T2>
auto operator + (const matrix<M, N, T1> &left,
                 const matrix<M, N, T2> &right)
-> matrix<M, N, decltype(left(0,0)*right(0,0))>
{
    using T3 = decltype(left(0,0)*right(0,0));
    matrix<M, N, T3> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(i, j) = left(i, j) + right(i, j);
        }
    }
    return ret;
}

template <size_t M, size_t N, size_t P, class T1, class T2>
auto operator * (const matrix<M, N, T1> &left,
                 const matrix<N, P, T2> &right)
-> matrix<M, P, decltype(left(0,0)*right(0,0))>
{
    using T3 = decltype(left(0,0)*right(0,0));
    matrix<M, P, T3> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < P; ++j)
        {
            T3 sum = 0;
            for (size_t k = 0; k < N; ++k)
            {
                sum += left(i, k) * right(k, j);
            }
            ret(i, j) = sum;
        }
    }
    return ret;
}

template <size_t M, size_t N, class T>
matrix<N, M, T> transpose(const matrix<M, N, T> &m)
{
    matrix<N, M, T> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(j, i) = m(i, j);
        }
    }
    return ret;
}

template <size_t N, class T> T det(const matrix<N, N, T> &m)
{
    static_assert(N > 2, "Cannot take the determinant of a matrix smaller than 2x2");

    T sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        T top = m(0, i);
        matrix<N-1, N-1, T> sub;

        for (size_t r = 1; r < N; ++r)
        {
            size_t j = 0;
            for (size_t c = 0; c < N - 1; ++c, ++j)
            {
                if (j == i) ++j;
                sub(r - 1, c) = m.at(r, j);
            }
        }

        T d = det(sub);
        sum += (top*d * (i % 2 == 0 ? 1 : -1));
    }
    return sum;
}

template <class T> T det(const matrix<2, 2, T> &m)
{
    return m(0,0)*m(1,1) - m(0,1)*m(1,0); 
}

template <size_t N, class T1, class T2>
auto inner_product(const vector<N, T1> &left,
                   const vector<N, T2> &right)
-> decltype(left(0,0)*right(0,0))
{
    using T3 = decltype(left(0,0)*right(0,0));
    T3 sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        sum += left(i, 0)*right(i, 0);
    }
    return sum;
}

template <class T1, class T2>
auto cross_product(const vector<3, T1> &left,
                   const vector<3, T2> &right)
-> vector<3, decltype(left(0,0)*right(0,0))>
{
    using T3 = decltype(left(0,0)*right(0,0));
    return vector<3, T3>(
        left(1,0)*right(2,0) - left(2,0)*right(1,0),
        left(2,0)*right(0,0) - left(0,0)*right(2,0),
        left(0,0)*right(1,0) - left(1,0)*right(0,0));
}

} // namespace lambda

#endif // MATRIX_H
