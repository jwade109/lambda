#ifndef LAMBDA_AXIS_ANGLE_HPP
#define LAMBDA_AXIS_ANGLE_HPP

#include <cmath>
#include <matrix.hpp>

namespace lambda
{

class quaternion;

class axis_angle
{
    public:

    axis_angle();

    axis_angle(const vector<3> &axis, double angle);

    axis_angle(const axis_angle &aa);

    axis_angle(const quaternion &q);

    axis_angle& operator = (const axis_angle &aa);

    axis_angle& operator = (const quaternion &q);

    const vector<3>& axis() const;

    vector<3>& axis();

    double angle() const;

    double& angle();

    private:

    vector<3> _axis;
    double _angle;
};

std::ostream& operator << (std::ostream& os, const axis_angle &aa);

} // namespace lambda

#endif // LAMBDA_AXIS_ANGLE_HPP
