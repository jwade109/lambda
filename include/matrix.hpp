#ifndef LAMBDA_MATRIX_HPP
#define LAMBDA_MATRIX_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>

/*!
    \file
    \brief Defines lambda::matrix, as well as supporting operations for
    basic matrix arithmetic.
*/

/// \brief The namespace used by all lambda classes and functions.
namespace lambda
{

/// \brief Forward declaration of lambda::quaternion.
class quaternion;
/// \brief Forward declaratuin of lambda::axis_angle.
class axis_angle;

/// \brief A statically sized matrix class. Supports basic operations like
/// addition, multiplication. Is default-constructable, copy-constructable,
/// and is constructable from quaternions and axis-angles.
template <size_t M, size_t N, typename R = double> class matrix
{
    static_assert(M > 0 && N > 0,
        "Cannot create matrix of dimension 0");

    public:

    const size_t rows = M;
    const size_t columns = N;
    using representation = R;

    /// \brief Default constructor.
    matrix() : _data() { }

    /// \brief Copy constructor.
    matrix(const matrix<M, N> &other) : _data(other.data()) { }

    /// \brief Construct a MxN matrix with a list of M*N elements.
    /// Elements are listed in row-major order.
    template <typename ...T, typename std::enable_if<
        sizeof...(T) == M*N, int>::type = 0>
    matrix(T... args) : _data({static_cast<R>(args)...}) { }

    /// \brief Construct a matrix from a quaternion. Only unit quaternions
    /// are guaranteed to produce valid rotation matrices.
    matrix(const quaternion &q);

    /// \brief Construct a rotation matrix from an axis-angle.
    matrix(const axis_angle &aa);

    /// \brief Assignment operator.
    matrix<M, N, R>& operator = (const matrix<M, N, R> &m)
    {
        for (size_t i = 0; i < M*N; ++i)
        {
            _data[i] = m[i];
        }
        return *this;
    }

    /// \brief Access an element in row i, column j.
    R operator () (size_t i, size_t j) const
    {
        return _data[N*i + j];
    }

    /// \brief Get a reference to the element (i, j).
    R& operator () (size_t i, size_t j)
    {
        return _data[N*i + j];
    }

    /// \brief Get the element at index i, interpreting the matrix
    /// as a 1-dimensional array in a row-major fashion.
    R operator [] (size_t i) const
    {
        return _data[i];
    }

    /// \brief Get a reference to the element at i, in the
    /// equivalent 1-dimensional row-major array.
    R& operator [] (size_t i)
    {
        return _data[i];
    }

    /// \brief Same as operator [], but throws an exception if
    /// the index provided is out of bounds.
    R at(size_t i) const
    {
        range_check(i);
        return _data[i];
    }

    /// \brief Same as operator [], but throws an exception if
    /// the index provided is out of bounds.
    R& at(size_t i)
    {
        range_check(i);
        return _data[i];
    }

    /// \brief Same as operator (), but throws an exception if
    /// the index provided is out of bounds.
    R at(size_t i, size_t j) const
    {
        range_check(i, j);
        return _data[N*i + j];
    }

    /// \brief Same as operator (), but throws an exception if
    /// the index provided is out of bounds.
    R& at(size_t i, size_t j)
    {
        range_check(i, j);
        return _data[N*i + j];
    }

    /// \brief Get a const ref to the underlying data of this matrix.
    const std::array<R, M*N>& data() const
    {
        return _data;
    }

    /// \brief Get a ref to the underlying data of this matrix.
    std::array<R, M*N>& data()
    {
        return _data;
    }

    private:

    /// \brief Matrix elements stored here.
    std::array<R, M*N> _data;

    /// \brief Throws an exception if an index is out of bounds.
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

    /// \brief Throws an exception if an index is out of bounds.
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



template <size_t M, size_t N>
bool operator == (const matrix<M, N> &left, const matrix<M, N> &right)
{
    for (size_t i = 0; i < M*N; ++i)
    {
        if (left[i] != right[i]) return false;
    }
    return true;
}

/// \brief Convenience typedef for column vectors.
template <size_t N, typename R = double>
using column_vector = matrix<N, 1, R>;
/// \brief Convenience typedef for row vectors.
template <size_t N, typename R = double>
using row_vector = matrix<1, N, R>;
/// \brief Convenience typedef; default vectors are column vectors.
template <size_t N, typename R = double>
using vector = column_vector<N, R>;
template <size_t M, size_t N, typename R = double>
using complex_matrix = lambda::matrix<M, N, std::complex<R>>;


/// \brief X basis vector.
const static column_vector<3> unitx(1, 0, 0);
/// \brief Y basis vector.
const static column_vector<3> unity(0, 1, 0);
/// \brief Z basis vector.
const static column_vector<3> unitz(0, 0, 1);

/// \brief Gets the identity vector of a given dimension.
template <size_t M, size_t N, typename R = double>
matrix<M, N, R> identity()
{
    matrix<M, N, R> ret;
    for (size_t i = 0; i < M && i < N; ++i)
    {
        ret(i, i) = 1;
    }
    return ret;
}

/// \brief Print a matrix to a std::ostream.
template <size_t M, size_t N, typename R>
std::ostream& operator << (std::ostream &os, const matrix<M, N, R> &m)
{
    os.precision(3);
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
    return os << "]";
}

/// \brief Produces a multiline string representation of a matrix.
template <size_t M, size_t N, typename R>
std::string pretty(const matrix<M, N, R> &m)
{
    std::stringstream ss;
    ss.precision(3);
    ss.setf(std::ios::fixed);

    size_t max_len = 0;
    for (size_t i = 0; i < M*N; ++i)
    {
        std::stringstream tiny;
        tiny.precision(3);
        tiny.setf(std::ios::fixed);
        tiny << m[i];
        size_t len = tiny.tellp();
        if (len > max_len) max_len = len;
    }

    for (size_t r = 0; r < M; ++r)
    {
        ss << "  [";
        for (size_t c = 0; c < N; ++c)
        {
            ss << std::setw(max_len + 1) << m(r, c);
        }
        ss << " ]\n";
    }
    return ss.str();
}

/// \brief Multiplication of a matrix by a scalar.
template <size_t M, size_t N, typename R, class T>
matrix<M, N, R> operator * (const matrix<M, N, R> &m, T scalar)
{
    matrix<M, N, R> ret = m;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(i, j) *= scalar;
        }
    }
    return ret;
}

/// \brief Multiplication of a matrix by a scalar.
template <size_t M, size_t N, typename R, class T>
matrix<M, N, decltype(T()*R())> operator * (T scalar, const matrix<M, N, R> &m)
{
    return m*scalar;
}

/// \brief Division of a matrix by a scalar.
template <size_t M, size_t N, typename R, class T>
matrix<M, N> operator / (const matrix<M, N, R> &m, T divisor)
{
    return m*(1.0/divisor);
}

/// \brief Addition of two matrices.
template <size_t M, size_t N, typename R1, typename R2>
matrix<M, N, decltype(R1() + R2())> operator + (const matrix<M, N, R1> &left,
                                                const matrix<M, N, R2> &right)
{
    matrix<M, N, decltype(R1() + R2())> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(i, j) = left(i, j) + right(i, j);
        }
    }
    return ret;
}

/// \brief Subtraction of two matrices.
template <size_t M, size_t N, typename R1, typename R2>
matrix<M, N, decltype(R1() - R2())> operator - (const matrix<M, N, R1> &left,
                                                const matrix<M, N, R2> &right)
{
    matrix<M, N, decltype(R1() - R2())> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(i, j) = left(i, j) - right(i, j);
        }
    }
    return ret;
}

/// \brief Multiplication of two matrices.
template <size_t M, size_t N, size_t P, typename R1, typename R2>
matrix<M, P, decltype(R1()*R2())> operator * (const matrix<M, N, R1> &left,
                                              const matrix<N, P, R2> &right)
{
    matrix<M, P, decltype(R1()*R2())> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < P; ++j)
        {
            decltype(R1()*R2()) sum = 0;
            for (size_t k = 0; k < N; ++k)
            {
                sum += left(i, k) * right(k, j);
            }
            ret(i, j) = sum;
        }
    }
    return ret;
}

/// \brief Get the transpose of a matrix.
template <size_t M, size_t N, typename R>
matrix<N, M, R> transpose(const matrix<M, N, R> &m)
{
    matrix<N, M, R> ret;
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ret(j, i) = m(i, j);
        }
    }
    return ret;
}

/// \brief Compute the hermitian, or conjugate, transpose of a matrix.
template <size_t M, size_t N, typename R>
complex_matrix<N, M, R> conjugate_transpose(const complex_matrix<M, N, R> &m)
{
    auto tr = transpose(m);
    for (auto& z : tr.data()) z = std::conj(z);
    return tr;
}

/// \brief Augment a matrix with another matrix.
template <size_t M, size_t N, size_t P, typename R>
matrix<M, N + P, R> augment(const matrix<M, N, R> &A,
                            const matrix<M, P, R> &x)
{
    matrix<M, N + P, R> ret;
    for (size_t r = 0; r < M; ++r)
    {
        for (size_t c = 0; c < N + P; ++c)
        {
            if (c < N) ret(r, c) = A(r, c);
            else ret(r, c) = x(r, c - N);
        }
    }
    return ret;
}


/// \brief Compute the determinant of a square matrix.
template <size_t N, typename R>
R det(const matrix<N, N, R> &m)
{
    R sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        R top = m(0, i);
        matrix<N-1, N-1, R> sub;

        for (size_t r = 1; r < N; ++r)
        {
            size_t j = 0;
            for (size_t c = 0; c < N - 1; ++c, ++j)
            {
                if (j == i) ++j;
                sub(r - 1, c) = m.at(r, j);
            }
        }

        R d = det(sub);
        sum += (top*d * (i % 2 == 0 ? 1.0 : -1.0));
    }
    return sum;
}

/// \brief Compute the determinant of a 2x2 matrix.
template <typename R> R det(const matrix<2, 2, R> &m)
{
    return m(0,0)*m(1,1) - m(0,1)*m(1,0);
}

/// \brief Compute the determinant of a 1x1 matrix.
template <typename R> R det(const matrix<1, 1, R> &m)
{
    return m(0,0);
}

/// \brief Compute the trace of a square matrix.
template <size_t N, typename R> R trace(const matrix<N, N, R> &m)
{
    R sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        sum += m(i, i);
    }
    return sum;
}

template <size_t N, typename R>
bool is_invertible(const matrix<N, N, R> &m)
{
    return det(m) != 0;
}

template <size_t N, typename R>
bool is_unitary(const matrix<N, N, R> &m)
{
    return m*transpose(m) == identity<N, N, R>();
}

/// \brief Compute the inverse of a square matrix.
template <typename R>
matrix<2, 2, R> inverse(const matrix<2, 2, R> &mat)
{
    if (!is_invertible(mat))
    {
        std::stringstream ss;
        ss << "Cannot invert matrix " << mat
            << ", which is singular";
        throw std::domain_error(ss.str());
    }
    return matrix<2, 2, R>( mat[4], -mat[2],
                           -mat[3],  mat[1])/det(mat);
}

/// \brief Compute the inverse of a square matrix.
template <typename R>
matrix<1, 1, R> inverse(const matrix<1, 1, R> &mat)
{
    if (!is_invertible(mat))
    {
        std::stringstream ss;
        ss << "Cannot invert matrix " << mat
            << ", which is singular";
        throw std::domain_error(ss.str());
    }
    return matrix<1, 1, R>(1.0/mat[0]);
}

/// \brief Compute the inner product of two matrices.
template <size_t M, size_t N, typename R>
double inner_product(const matrix<M, N, R> &left,
                     const matrix<M, N, R> &right)
{
    R sum = 0;
    for (size_t i = 0; i < M*N; ++i)
    {
        sum += left[i]*right[i];
    }
    return sum;
}

/// \brief Compute a matrix raised to a power.
template <size_t N, typename R>
matrix<N, N> pow(const matrix<N, N, R> &mat, size_t ex)
{
    if (ex < 0) throw std::logic_error("unimplemented");

    if (ex == 0) return identity<N, N, R>();
    else if (ex == 1) return mat;

    matrix<3, 3> ret = mat;
    for (size_t i = 0; i < ex - 1; ++i)
    {
        ret = ret * mat;
    }
    return ret;
}

/// \brief Convenience operator for matrix power.
template <size_t N>
matrix<N, N> operator ^ (const matrix<N, N> &mat, size_t ex)
{
    return pow(mat, ex);
}

/// \brief Convenience operator for skew-symmetric matrix of a vector.
template <size_t N>
matrix<N, N> operator ~ (const column_vector<N> &vec)
{
    return skew_symmetric(vec);
}

/// \brief Convenience operator for skew-symmetric matrix of a vector.
template <size_t N>
matrix<N, N> operator ~ (const row_vector<N> &vec)
{
    return skew_symmetric(vec);
}

/// \brief Compute the cross product of two vectors.
column_vector<3> cross_product(const column_vector<3> &left,
                               const column_vector<3> &right);

/// \brief Compute the cross product of two vectors.
column_vector<3> cross_product(const column_vector<3> &left,
                               const row_vector<3> &right);

/// \brief Compute the cross product of two vectors.
column_vector<3> cross_product(const row_vector<3> &left,
                               const column_vector<3> &right);

/// \brief Compute the cross product of two vectors.
column_vector<3> cross_product(const row_vector<3> &left,
                               const row_vector<3> &right);

/// \brief Compute the skew-symmetric equivalent matrix from
/// a 3D vector.
matrix<3, 3> skew_symmetric(const row_vector<3> &v);

/// \brief Compute the skew-symmetric equivalent matrix from
/// a 3D vector.
matrix<3, 3> skew_symmetric(const column_vector<3> &v);

} // namespace lambda

#endif // LAMBDA_MATRIX_HPP
