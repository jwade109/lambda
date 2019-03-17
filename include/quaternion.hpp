#ifndef LAMBDA_QUATERNION_HPP
#define LAMBDA_QUATERNION_HPP

#include <sstream>

#include <axis_angle.hpp>

namespace lambda
{

class quaternion
{
    public:

    quaternion();

    quaternion(const quaternion &q);

    quaternion(double scalar, const vector<3> &vec);

    quaternion(double q1, double q2, double q3, double q4);

    quaternion(const axis_angle &aa);

    quaternion& operator = (const quaternion &q);

    quaternion& operator = (const axis_angle &aa);

    double scalar() const;

    double& scalar();

    const vector<3>& vec() const;

    vector<3>& vec();

    double operator [] (size_t index) const;

    double& operator [] (size_t index);

    double at(size_t index) const;
    
    double& at(size_t index);

    private:

    double _scalar;
    vector<3> _vec;
};

std::ostream& operator << (std::ostream &os, const quaternion &q);

} // namespace lambda

#endif // LAMBDA_QUATERNION_H
