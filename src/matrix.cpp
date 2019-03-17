// matrix.cpp

#include <matrix.hpp>
#include <quaternion.hpp>

namespace lambda
{

template <> matrix<3, 3>::matrix(const quaternion &q)
    : _data({1 - 2*q[2]*q[2] - 2*q[3]*q[3],
             2*q[1]*q[2] + 2*q[3]*q[0],
             2*q[1]*q[3] + 2*q[2]*q[0],
             2*q[1]*q[2] + 2*q[3]*q[0],
             1 - 2*q[1]*q[1] - 2*q[3]*q[3],
             2*q[2]*q[3] - 2*q[1]*q[0],
             2*q[1]*q[3] - 2*q[2]*q[0],
             2*q[2]*q[3] + 2*q[1]*q[0],
             1 - 2*q[1]*q[1] - 2*q[2]*q[2]}) { }

double det(const matrix<2, 2> &m)
{
    return m(0,0)*m(1,1) - m(0,1)*m(1,0); 
}

double det(const matrix<1, 1> &m)
{
    return m(0,0);
}

column_vector<3> cross_product(const column_vector<3> &left,
                               const column_vector<3> &right)
{
    return column_vector<3>(
        left[1]*right[2] - left[2]*right[1],
        left[2]*right[0] - left[0]*right[2],
        left[0]*right[1] - left[1]*right[0]);
}

column_vector<3> cross_product(const column_vector<3> &left,
                               const row_vector<3> &right)
{
    return cross_product(left, transpose(right));
}

column_vector<3> cross_product(const row_vector<3> &left,
                               const column_vector<3> &right)
{
    return cross_product(transpose(left), right);
}

column_vector<3> cross_product(const row_vector<3> &left,
                               const row_vector<3> &right)
{
    return cross_product(transpose(left), transpose(right));
}

} // namespace lambda
