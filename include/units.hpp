// units.cpp

#ifndef LAMBDA_UNITS_HPP
#define LAMBDA_UNITS_HPP

#include <iostream>
#include <ratio>

namespace lambda
{

namespace dimensions
{

class unitless {};
class length {};
class mass {};
class time {};
class temperature {};
class current {};
class luminosity {};

}

template <class D = dimensions::unitless,
          class R = std::ratio<1>> class unit
{
    using dimension = D;
    using ratio = R;

    public:

    unit() : _value(0) { }
    explicit unit(double value) : _value(value) { }
    double value() const { return _value; }

    template <class R2>
    unit(const unit<D, R2> &other) :
        _value(other.value()*R::den/R::num*R2::num/R2::den) { }

    double _value;
};

template <class D, class R>
std::ostream& operator << (std::ostream &os, const unit<D, R> &u)
{
    return os << u.value();
}

template <class D1, class D2, class R1, class R2>
unit<D1, std::ratio_add<R1, R2>>
operator + (const unit<D1, R1> &left, const unit<D2, R2> &right)
{
    static_assert(std::is_same<D1, D2>::value,
        "Cannot add units of different dimension");

    const double value = left.value()*R2::den/R2::num +
                         right.value()*R1::den/R1::num;
    return unit<D1, std::ratio_add<R1, R2>>(value);
}

template <class D1, class D2, class R1, class R2>
unit<D1, std::ratio_add<R1, R2>>
operator - (const unit<D1, R1> &left, const unit<D2, R2> &right)
{
    static_assert(std::is_same<D1, D2>::value,
        "Cannot subtract units of different dimension");

    return left + -right;
}


template <class D, class R>
const unit<D, R> operator - (const unit<D, R> &u)
{
    return unit<D, R>(-u.value());
}

template <class D, class R, class F>
const unit<D, R> operator * (const unit<D, R> &u, F scalar)
{
    return unit<D, R>(u.value()*scalar);
}

template <class D, class R, class F>
const unit<D, R> operator * (F scalar, const unit<D, R> &u)
{
    return u*scalar;
}

template <class D, class R, class F>
const unit<D, R> operator / (const unit<D, R> &u, F scalar)
{
    return u*(1.0/scalar);
}

template <class R = std::ratio<1>>
using length = unit<dimensions::length, R>;
using meters = length<>;
using kilometers = length<std::ratio<1000>>;
using miles = length<std::ratio<1609344, 1000>>;

template <class R = std::ratio<1>>
using time = unit<dimensions::time, R>;
using seconds = time<>;
using minutes = time<std::ratio<60>>;
using hours = time<std::ratio<3600>>;

} // namespace lambda

#endif // LAMBDA_UNITS_HPP

