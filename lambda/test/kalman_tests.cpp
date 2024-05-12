#include <catch2/catch.hpp>
#include <lambda/lambda.hpp>

TEST_CASE("Kalman test.", "[basic kalman]")
{
    lambda::kf<5, 3> kf;
}
