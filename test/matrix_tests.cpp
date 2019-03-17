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
