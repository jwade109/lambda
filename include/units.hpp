// units.hpp

#ifndef LAMBDA_UNITS_HPP
#define LAMBDA_UNITS_HPP

#include <iostream>
#include <ratio>
#include <tuple>

namespace lambda
{

// ===============================================================
// SI DIMENSIONS

namespace dimensions
{

struct dimensionless { const static char* str; };
struct length { const static char* str; };
struct mass { const static char* str; };
struct time { const static char* str; };
struct temperature { const static char* str; };
struct current { const static char* str; };
struct luminosity { const static char* str; };
struct substance { const static char* str; };

}

// ===============================================================
// UNIT TEMPLATE DEFINITION

template <class D = dimensions::dimensionless,
          class R = std::ratio<1>,
          int8_t E = 1> class unit
{
    public:

    using dimension = D;
    using ratio = R;
    const static int8_t exponent = E;

    unit() : _value(0) { }
    explicit unit(double value) : _value(value) { }
    double value() const { return _value; }

    template <class R2>
    unit(const unit<D, R2, E> &other) :
        _value(other.value()*R::den/R::num*R2::num/R2::den) { }

    double _value;
};

// ===============================================================
// DIMENSIONLESS SPECIALIZATION

template <class R, int8_t E>
class unit<dimensions::dimensionless, R, E> { };

// ===============================================================
// PRINT TO OSTREAM

template <class D, class R, int8_t E>
std::ostream& operator << (std::ostream &os, const unit<D, R, E> &u)
{
    return os << u.value()*R::num/R::den
        << " " << D::str << "^" << (int) E;
}

// ===============================================================
// UNIT ADDITION

template <class D1, class D2, class R1, class R2, int8_t E1, int8_t E2>
unit<D1, std::ratio_add<R1, R2>>
operator + (const unit<D1, R1, E1> &left, const unit<D2, R2, E2> &right)
{
    static_assert(std::is_same<D1, D2>::value,
        "Cannot add units of different dimensions");
    static_assert(E1 == E2,
        "Cannot add units of different exponents");

    const double value = left.value()*R2::den/R2::num +
                         right.value()*R1::den/R1::num;
    return unit<D1, std::ratio_add<R1, R2>, E1>(value);
}

// ===============================================================
// UNIT SUBTRACTION

template <class D1, class D2, class R1, class R2, int8_t E1, int8_t E2>
unit<D1, std::ratio_add<R1, R2>>
operator - (const unit<D1, R1, E1> &left, const unit<D2, R2, E2> &right)
{
    static_assert(std::is_same<D1, D2>::value,
        "Cannot subtract units of different dimensions");
    static_assert(E1 == E2,
        "Cannot add units of different exponents");

    return left + -right;
}

// ===============================================================
// UNIT MULTIPLICATION

template <class D, int8_t E1, int8_t E2>
unit<D, std::ratio<1>, E1 + E2>
operator * (const unit<D, std::ratio<1>, E1> &left,
            const unit<D, std::ratio<1>, E2> &right)
{
    return unit<D, std::ratio<1>, E1 + E2>(left.value()*right.value());
}

template <class D, class R1, class R2, int8_t E1, int8_t E2>
unit<D, std::ratio_multiply<R1, R2>, E1 + E2>
operator * (const unit<D, R1, E1> &left, const unit<D, R2, E2> &right)
{
    return unit<D, std::ratio_divide<R1, R2>, E1 + E2>(
        unit<D, std::ratio<1>, E1>(left)*unit<D, std::ratio<1>, E2>(right));
}

template <class D, class R1, class R2, int8_t E1, int8_t E2>
unit<D, R1, E1>
operator * (const unit<D, R1, E1> &left,
            const unit<dimensions::dimensionless, R2, E2> &right)
{
    return left;
}

template <class D, class R1, class R2, int8_t E1, int8_t E2>
unit<D, R2, E2>
operator * (const unit<dimensions::dimensionless, R1, E1> &left,
            const unit<D, R2, E2> &right)
{
    return right;
}

// ===============================================================
// UNIT DIVISION

template <class D, int8_t E1, int8_t E2>
unit<D, std::ratio<1>, E1 - E2>
operator / (const unit<D, std::ratio<1>, E1> &left,
            const unit<D, std::ratio<1>, E2> &right)
{
    return unit<D, std::ratio<1>, E1 - E2>(left.value()/right.value());
}

template <class D, class R1, class R2, int8_t E1, int8_t E2>
unit<D, std::ratio_divide<R1, R2>, E1 - E2>
operator / (const unit<D, R1, E1> &left, const unit<D, R2, E2> &right)
{
    return unit<D, std::ratio_divide<R1, R2>, E1 - E2>(
        unit<D, std::ratio<1>, E1>(left)/unit<D, std::ratio<1>, E2>(right));
}

// ===============================================================
// NEGATION

template <class D, class R>
const unit<D, R> operator - (const unit<D, R> &u)
{
    return unit<D, R>(-u.value());
}

// ===============================================================
// MULTIPLICATION AND DIVISION BY SCALARS

template <class D, class R>
const unit<D, R> operator * (const unit<D, R> &u, double scalar)
{
    return unit<D, R>(u.value()*scalar);
}

template <class D, class R>
const unit<D, R> operator * (double scalar, const unit<D, R> &u)
{
    return u*scalar;
}

template <class D, class R>
const unit<D, R> operator / (const unit<D, R> &u, double scalar)
{
    return u*(1.0/scalar);
}

template <class D, class R, int8_t E>
const unit<D, R, -E> operator / (double scalar, const unit<D, R, E> &u)
{
    return unit<D, R, E>(scalar/u.value());
}

// ===============================================================
// MULTIPLICATION AND DIVISION HELPERS

template <class L, class R>
using unit_multiply = decltype(L()*R());
template <class L, class R>
using unit_divide = decltype(L()/R());

// ===============================================================
// EXPONENTIATION

template <class U, int8_t E>
struct unit_exponent_helper
{
    using value = unit_multiply<U, typename
        unit_exponent_helper<U, (E > 0 ? E-1 : E+1)>::value>;
};

template <class U>
struct unit_exponent_helper<U, 1>
{
    using value = unit<typename U::dimension, typename U::ratio, 1>;
};

template <class U>
struct unit_exponent_helper<U, -1>
{
    using value = unit<typename U::dimension, typename U::ratio, -1>;
};

template <class U>
struct unit_exponent_helper<U, 0>
{
    using value = unit<dimensions::dimensionless>;
};

template <class U, int8_t E>
using unit_exponent = typename unit_exponent_helper<U, E>::value;

// ===============================================================
// COMPOSITE UNIT DEFINITION

template <class ...U>
class composite_unit
{
    public:

    composite_unit() : _value(0) { };
    explicit composite_unit(double value) : _value(value) { }
    double value() const { return _value; }
    std::tuple<U...> dimensions() const { return _dimensions; };

    private:

    double _value;
    std::tuple<U...> _dimensions;
};

// ===============================================================
// COMPOSITE FACTORY FUNCTION


template <class D, class R, int8_t E>
auto make_composite(unit<D, R, E> unit)
{
    return composite_unit<decltype(unit)>(unit.value());
}

// ===============================================================
// STD::TUPLE TO OSTREAM

namespace tuple_pretty_print
{

template<std::size_t...> struct seq{};
template<std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<std::size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, seq<Is...>)
{
    using swallow = int[];
    (void) swallow{0, (void(os << (Is == 0 ? "" : ", ")
        << std::get<Is>(t)), 0)...};
}

} // namespace tuple_pretty_print

template<class Ch, class Tr, class... Args>
std::basic_ostream<Ch, Tr>& operator <<
    (std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
{
    os << "(";
    tuple_pretty_print::print_tuple(
        os, t, tuple_pretty_print::gen_seq<sizeof...(Args)>());
    return os << ")";
}

// ===============================================================
// COMPOSITE TO OSTREAM

template <class ...U>
std::ostream& operator << (std::ostream &os, const composite_unit<U...> &u)
{
    return os << u.value() << " " << u.dimensions();
}

// ===============================================================
// COMPOSITE MULTIPLICATION

template <class D1, class D2, int8_t E1, int8_t E2>
auto operator * (const unit<D1, std::ratio<1>, E1> &left,
                 const unit<D2, std::ratio<1>, E2> &right)
{
    return composite_unit<unit<D1, std::ratio<1>, E1>,
        unit<D2, std::ratio<1>, E2>>(left.value()*right.value());
}

template <class D1, class D2, class R1, class R2, int8_t E1, int8_t E2>
auto operator * (const unit<D1, R1, E1> &left, const unit<D2, R2, E2> &right)
{
    return unit<D1, std::ratio<1>, E1>(left)*
           unit<D2, std::ratio<1>, E2>(right);
}

template <class ...U1, class ...U2>
auto operator * (const composite_unit<U1...> &left,
                 const composite_unit<U2...> &right)
{
    return composite_unit<U1..., U2...>(left.value()*right.value());
}

// ===============================================================
// COMPOSITE DIVISION

template <class D1, class D2, int8_t E1, int8_t E2>
auto operator / (const unit<D1, std::ratio<1>, E1> &left,
                 const unit<D2, std::ratio<1>, E2> &right)
{
    return composite_unit<unit<D1, std::ratio<1>, E1>,
        unit<D2, std::ratio<1>, -E2>>(left.value()/right.value());
}

template <class D1, class D2, class R1, class R2, int8_t E1, int8_t E2>
auto operator / (const unit<D1, R1, E1> &left, const unit<D2, R2, E2> &right)
{
    return unit<D1, std::ratio<1>, E1>(left)/
           unit<D2, std::ratio<1>, E2>(right);
}

template <class ...U1, class ...U2>
auto operator / (const composite_unit<U1...> &left,
                 const composite_unit<U2...> &right)
{
    // return composite_unit<U1..., U2...>(left.value()/right.value());
}

// ===============================================================
// SIMPLE TYPEDEFS

template <class R = std::ratio<1>, int8_t E = 1>
using length = unit<dimensions::length, R, E>;
using meters = length<>;
using millimeters = length<std::milli>;
using kilometers = length<std::kilo>;
using miles = length<std::ratio<1609344, 1000>>;
using square_meters = unit_multiply<meters, meters>;
using square_kilometers = unit_multiply<kilometers, kilometers>;

template <class R = std::ratio<1>, int8_t E = 1>
using time = unit<dimensions::time, R>;
using seconds = time<>;
using minutes = time<std::ratio<60>>;
using hours = time<std::ratio<3600>>;
using milliseconds = time<std::milli>;
using nanoseconds = time<std::nano>;

template <class R = std::ratio<1>, int8_t E = 1>
using mass = unit<dimensions::mass, R>;
using kilograms = mass<>;
using grams = mass<std::milli>;

template <class R = std::ratio<1>, int8_t E = 1>
using time = unit<dimensions::time, R>;
using seconds = time<>;
using minutes = time<std::ratio<60>>;
using hours = time<std::ratio<3600>>;
using milliseconds = time<std::milli>;
using nanoseconds = time<std::nano>;

template <class R = std::ratio<1>, int8_t E = 1>
using mass = unit<dimensions::mass, R>;
using kilogram = mass<>;
using gram = mass<std::milli>;

// ===============================================================
// COMPOSITE TYPEDEFS

using meters_per_second = unit_divide<meters, seconds>;
using meters_per_second_squared = unit_divide<meters, unit_exponent<seconds, 2>>;

using newtons = unit_multiply<unit_multiply<kilograms, meters>,
    composite_unit<decltype(1/seconds()/seconds())>>;

} // namespace lambda

#endif // LAMBDA_UNITS_HPP
