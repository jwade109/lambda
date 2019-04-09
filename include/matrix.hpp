#ifndef LAMBDA_MATRIX_HPP
#define LAMBDA_MATRIX_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <iostream>
#include <sstream>

namespace lambda
{

class quaternion;
class axis_angle;

template <size_t M, size_t N> class matrix
{
    static_assert(M > 0 && N > 0,
        "Cannot create matrix of dimension 0");

    public:

    matrix() : _data() { }

    matrix(const matrix<M, N> &other) : _data(other.data()) { }

    template <typename ...T, typename std::enable_if<
        sizeof...(T) == M*N, int>::type = 0>
    matrix(T... args) : _data({static_cast<double>(args)...}) { }

    matrix(const quaternion &q);

    matrix<M, N>& operator = (const matrix<M, N> &m)
    {
        for (size_t i = 0; i < M*N; ++i)
        {
            _data[i] = m[i];
        }
    }

    double operator () (size_t i, size_t j) const
    {
        return _data[N*i + j];
    }

    double& operator () (size_t i, size_t j)
    {
        return _data[N*i + j];
    }

    double operator [] (size_t i) const
    {
        return _data[i];
    }

    double& operator [] (size_t i)
    {
        return _data[i];
    }

    double at(size_t i) const
    {
        range_check(i);
        return _data[i];
    }

    double& at(size_t i)
    {
        range_check(i);
        return _data[i];
    }

    double at(size_t i, size_t j) const
    {
        range_check(i, j);
        return _data[N*i + j];
    }

    double& at(size_t i, size_t j)
    {
        range_check(i, j);
        return _data[N*i + j];
    }

    const std::array<double, M*N>& data() const
    {
        return _data;
    }

    private:

    std::array<double, M*N> _data;

    static void range_check(size_t i)
    {
        if (i >= N*M)
        {
            std::stringstream ss;
            ss << "Cannot access element (" << i
                << ") of " << M << "x" << N << "matrix";
            throw std::out_of_range(ss.str());
        }
    }

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

template <size_t N>
using column_vector = matrix<N, 1>; 
template <size_t N>
using row_vector = matrix<1, N>;
template <size_t N>
using vector = column_vector<N>;

const static vector<3>
    unitx(1, 0, 0), unity(0, 1, 0), unitz(0, 0, 1);

template <size_t M, size_t N> matrix<M, N> identity()
{
    matrix<M, N> ret;
    for (int i = 0; i < M && i < N; ++i)
    {
        ret(i, i) = 1;
    }
    return ret;
}

template <size_t M, size_t N>
std::ostream& operator << (std::ostream &os, const matrix<M, N> &m)
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

template <size_t M, size_t N, class T>
matrix<M, N> operator * (const matrix<M, N> &m, T scalar)
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

template <size_t M, size_t N, class T>
matrix<M, N> operator * (T scalar, const matrix<M, N> &m)
{
    return m*scalar;
}

template <size_t M, size_t N, class T>
matrix<M, N> operator / (const matrix<M, N> &m, T divisor)
{
    return m*(1.0/divisor);
}

template <size_t M, size_t N>
matrix<M, N> operator + (const matrix<M, N> &left,
                         const matrix<M, N> &right)
{
    matrix<M, N> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(i, j) = left(i, j) + right(i, j);
        }
    }
    return ret;
}

template <size_t M, size_t N, size_t P>
matrix<M, P> operator * (const matrix<M, N> &left,
                         const matrix<N, P> &right)
{
    matrix<M, P> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < P; ++j)
        {
            double sum = 0;
            for (size_t k = 0; k < N; ++k)
            {
                sum += left(i, k) * right(k, j);
            }
            ret(i, j) = sum;
        }
    }
    return ret;
}

template <size_t M, size_t N>
matrix<N, M> transpose(const matrix<M, N> &m)
{
    matrix<N, M> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(j, i) = m(i, j);
        }
    }
    return ret;
}

template <size_t N> double det(const matrix<N, N> &m)
{
    double sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        double top = m(0, i);
        matrix<N-1, N-1> sub;

        for (size_t r = 1; r < N; ++r)
        {
            size_t j = 0;
            for (size_t c = 0; c < N - 1; ++c, ++j)
            {
                if (j == i) ++j;
                sub(r - 1, c) = m.at(r, j);
            }
        }

        double d = det(sub);
        sum += (top*d * (i % 2 == 0 ? 1 : -1));
    }
    return sum;
}

double det(const matrix<2, 2> &m);

double det(const matrix<1, 1> &m);

template <size_t N> double trace(const matrix<N, N> &m)
{
    double sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        sum += m(i, i);
    }
    return sum;
}

template <size_t N>
matrix<N, N> inverse(const matrix<N, N> &mat)
{
    throw std::logic_error("not implemented");
}

template <size_t M, size_t N>
double inner_product(const matrix<M, N> &left,
                     const matrix<M, N> &right)
{
    double sum = 0;
    for (size_t i = 0; i < M*N; ++i)
    {
        sum += left[i]*right[i];
    }
    return sum;
}

template <size_t N>
matrix<N, N> pow(const matrix<N, N> &mat, size_t ex)
{
    if (ex < 0) throw std::logic_error("unimplemented");

    if (ex == 0) return identity<N, N>();
    else if (ex == 1) return mat;
    
    matrix<3, 3> ret = mat;
    for (size_t i = 0; i < ex - 1; ++i)
    {
        ret = ret * mat;
    }
    return ret;
}

template <size_t N>
matrix<N, N> operator ^ (const matrix<N, N> &mat, size_t ex)
{
    return pow(mat, ex);
}

column_vector<3> cross_product(const column_vector<3> &left,
                               const column_vector<3> &right);

column_vector<3> cross_product(const column_vector<3> &left,
                               const row_vector<3> &right);

column_vector<3> cross_product(const row_vector<3> &left,
                               const column_vector<3> &right);

column_vector<3> cross_product(const row_vector<3> &left,
                               const row_vector<3> &right);

matrix<3, 3> skew_symmetric(const row_vector<3> &v);

matrix<3, 3> skew_symmetric(const column_vector<3> &v);

} // namespace lambda

#endif // LAMBDA_MATRIX_HPP
