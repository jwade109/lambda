#ifndef QUATERNION_H
#define QUATERNION_H

#include <matrix.hpp>
#include <sstream>

namespace lambda
{

template <class T = double> class quaternion
{
    public:

    quaternion() : _scalar(0),  _vec() { }

    template <typename T2>
    quaternion(const quaternion<T2> &q)
        : _scalar(q.scalar()), _vec(q.vec()) { }

    template <typename T1, typename T2>
    quaternion(T1 scalar, const vector<3, T2> &vec)
        : _scalar(scalar), _vec(vec) { }

    template <typename T1, typename T2, typename T3, typename T4>
    quaternion(T1 q1, T2 q2, T3 q3, T4 q4)
        : _scalar(q1), _vec(q2, q3, q4) { }

    T scalar() const
    {
        return _scalar;
    }

    T& scalar()
    {
        return _scalar;
    }

    const vector<3, T>& vec() const
    {
        return _vec;
    }

    vector<3, T>& vec()
    {
        return _vec;
    }

    T operator [] (size_t index) const
    {
        return index == 0 ? _scalar : _vec(index - 1, 0);
    }

    T& operator [] (size_t index)
    {
        return index == 0 ? _scalar : _vec(index - 1, 0);
    }

    T at(size_t index) const
    {
        range_check(index);
        return index == 0 ? _scalar : _vec(index - 1, 0);
    }
    
    T& at(size_t index)
    {
        range_check(index);
        return index == 0 ? _scalar : _vec(index - 1, 0);
    }

    private:

    T _scalar;
    vector<3, T> _vec;

    static void range_check(size_t i)
    {
        if (i > 3)
        {
            std::stringstream ss;
            ss << "Cannot access element (" << i
                << ") of quaternion";
            throw std::out_of_range(ss.str());
        }
    }
};

template <typename T>
std::ostream& operator << (std::ostream &os, const quaternion<T> &q)
{
    os.precision(2);
    os.setf(std::ios::fixed);
    os << "[" << +q[0] << ", " << +q[1] << " "
        << +q[2] << " " << +q[3] << "]";
    return os;
}

} // namespace lambda

#endif // QUATERNION_H
