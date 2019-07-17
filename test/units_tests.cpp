#include "catch.hpp"
#include <lambda>

void foo(const lambda::kilometers &km)
{
    std::cout << km.value() << " km" << std::endl;
}

TEST_CASE("Simple unit conversions and arithmetic.", "[units]")
{
    using namespace lambda;

    kilometers kil(1.54);
    meters met = kil/3;

    foo(kil);
    foo(met);

    std::cout << kil.value() << " km / 3 = " << (kil/3).value() << " km" << std::endl;
    std::cout << kil.value() << " km * 4 = " << (4*kil).value() << " km" << std::endl;
    std::cout << kil.value() << " km * 0.21 = " << (kil*0.21).value() << " km" << std::endl;
    std::cout << kil.value() << " km - " << met.value() << " m = "
        << kilometers(kil - met).value() << " km, or "
        << meters(kil - met).value() << " m" << std::endl;

    seconds sec(65.3);
    minutes min(2.3);
    std::cout << sec << " s = " << minutes(sec) << " min" << std::endl;
    std::cout << sec << " s + " << min << " min = "
        << seconds(min + sec) << " s, or "
        << minutes(min + sec) << " min" << std::endl;

    using furlongs = length<std::ratio<201168, 1000>>;
    furlongs fur(4.623);
    std::cout << fur << " furlongs is equal to "
              << kilometers(fur) << " km" << std::endl;
}

TEST_CASE("Exponentiated units.", "[units]")
{
    using namespace lambda;

    meters x(84.3), y(194.3);
    square_meters area = x*y;
    std::cout << x.value() << " meters * "
        << y.value() << " meters = "
        << area.value() << " meters^2" << std::endl;
    square_kilometers area_kilo(area);
    std::cout << " = " << area_kilo.value() << " km^2" << std::endl;

    std::cout << x.value() << " m / " << y.value()
        << " m = " << (x/y).value() << std::endl;
    std::cout << kilometers(x*1000).value() << " km / " << y
        << " m = " << (kilometers(x*1000)/y).value() << std::endl;

    miles mil(1);
    square_kilometers sqk(2);

    std::cout << sqk.value() << " km^2 / " << mil.value() << " miles = "
        << kilometers(sqk/mil).value() << " km, or "
        << miles(sqk/mil).value() << " miles" << std::endl;

    using millimeters_fifth = unit_exponent<millimeters, 5>;
    unit_exponent<millimeters, 4> mm3(65564.4);
    unit_exponent<meters, 2> m2(2.3);
    std::cout << mm3.value() << "" << m2.value() << " m^2 = " << std::endl
        << unit_exponent<millimeters, 6>(m2*mm3).value() << " mm^6" << std::endl
        << unit_exponent<meters, 6>(m2*mm3).value() << " m^6" << std::endl;

    unit_exponent<meters, -1> mn1(1.5);
    std::cout << m2.value() << " mm^2 * " << mn1.value() << " m^-1 = "
        << meters(m2*mn1).value() << " m" << std::endl;
}

TEST_CASE("Composite units.", "[units]")
{
    using namespace lambda;

    meters_per_second vel = meters(3)/seconds(2);
    meters_per_second_squared acc(6);
    newtons ns(4.32);

    std::cout << make_composite(meters(9.5)) << std::endl;
    std::cout << vel << std::endl;
    std::cout << acc << std::endl;
    std::cout << ns << std::endl;
}
