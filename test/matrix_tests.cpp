#include "catch.hpp"
#include <lambda>

TEST_CASE("Quaternion to rotation matrix.", "[matrix]")
{
    lambda::quaternion q(0.5080005, 0.3810004, 0.1270001, 0.7620008);
    lambda::matrix<3, 3> m = q;

    REQUIRE(m(0, 0) == Approx(-0.1935484));
    REQUIRE(m(0, 1) == Approx(-0.6774194));
    REQUIRE(m(0, 2) == Approx(0.7096774));
    REQUIRE(m(1, 0) == Approx(0.8709677));
    REQUIRE(m(1, 1) == Approx(-0.4516129));
    REQUIRE(m(1, 2) == Approx(-0.1935484));
    REQUIRE(m(2, 0) == Approx(0.4516129));
    REQUIRE(m(2, 1) == Approx(0.5806451));
    REQUIRE(m(2, 2) == Approx(0.6774194));
    REQUIRE(lambda::det(m) == Approx(1));
}

TEST_CASE("Throw out of bounds exception.", "[matrix]")
{
    lambda::matrix<3, 4> m;
    
    REQUIRE_THROWS_WITH( m.at(45, 3),
        "Cannot access element (45, 3) of 3x4 matrix");
}

TEST_CASE("Matrix power calculation.", "[matrix]")
{
    lambda::matrix<3, 3> m(3.4,  2.1, -5.0,
                           7.2, -9.1, -4.0,
                           0.8,  4.2,  4.1);

    lambda::matrix<3, 3> identity = lambda::pow(m, 0);
    lambda::matrix<3, 3> copy = lambda::pow(m, 1);
    auto m2 = m^2;
    auto m5 = m^5;

    REQUIRE(identity(0, 0) == 1);
    REQUIRE(identity(1, 1) == 1);
    REQUIRE(identity(2, 2) == 1);
    REQUIRE(identity(0, 1) == 0);
    REQUIRE(identity(0, 2) == 0);
    REQUIRE(identity(1, 0) == 0);
    REQUIRE(identity(1, 2) == 0);
    REQUIRE(identity(2, 0) == 0);
    REQUIRE(identity(2, 1) == 0);

    REQUIRE(copy(0, 0) == Approx(3.4));
    REQUIRE(copy(0, 1) == Approx(2.1));
    REQUIRE(copy(0, 2) == Approx(-5));
    REQUIRE(copy(1, 0) == Approx(7.2));
    REQUIRE(copy(1, 1) == Approx(-9.1));
    REQUIRE(copy(1, 2) == Approx(-4.0));
    REQUIRE(copy(2, 0) == Approx(0.8));
    REQUIRE(copy(2, 1) == Approx(4.2));
    REQUIRE(copy(2, 2) == Approx(4.1));

    REQUIRE(m2(0, 0) == Approx(22.68));
    REQUIRE(m2(0, 1) == Approx(-32.97));
    REQUIRE(m2(0, 2) == Approx(-45.9));
    REQUIRE(m2(1, 0) == Approx(-44.24));
    REQUIRE(m2(1, 1) == Approx(81.13));
    REQUIRE(m2(1, 2) == Approx(-16));
    REQUIRE(m2(2, 0) == Approx(36.24));
    REQUIRE(m2(2, 1) == Approx(-19.32));
    REQUIRE(m2(2, 2) == Approx(-3.99));

    REQUIRE(m5(0, 0) == Approx(-17469.7));
    REQUIRE(m5(0, 1) == Approx(22338.6));
    REQUIRE(m5(0, 2) == Approx(7241.08));
    REQUIRE(m5(1, 0) == Approx(43169.4));
    REQUIRE(m5(1, 1) == Approx(-83500.3));
    REQUIRE(m5(1, 2) == Approx(-4272.05));
    REQUIRE(m5(2, 0) == Approx(-15195));
    REQUIRE(m5(2, 1) == Approx(22031.2));
    REQUIRE(m5(2, 2) == Approx(-2406.84));
}
