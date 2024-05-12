#include <catch2/catch.hpp>
#include <lambda/lambda.hpp>

#include <eigen3/Eigen/Core>

#if 0
TEST_CASE("Singular value decomposition.", "[decomposition]")
{
    lambda::matrix<4, 5> test(
        1, 0, 0, 0, 2,
        0, 0, 3, 0, 0,
        0, 0, 0, 0, 0,
        0, 2, 0, 0, 0);

    lambda::matrix<4, 4> U;
    lambda::matrix<4, 5> sigma;
    lambda::matrix<5, 5> V_star;
    std::tie(U, sigma, V_star) = lambda::svd(test);

    REQUIRE( U == lambda::matrix<4, 4>(0, 0, 1,  0,
                                       0, 1, 0,  0,
                                       0, 0, 0, -1,
                                       1, 0, 0,  0) );
    REQUIRE( sigma == lambda::matrix<4, 5>(2, 0, 1, 0, 0,
                                           0, 3, 0, 0, 0,
                                           0, 0, 2.23606797749979, 0, 0,
                                           0, 0, 0, 0, 0) );

    REQUIRE( test == U*sigma*V_star );
    REQUIRE( U*lambda::transpose(U) == lambda::identity<4, 4>() );
    REQUIRE( lambda::is_unitary(U) );
    REQUIRE( V_star*lambda::transpose(V_star) == lambda::identity<5, 5>() );
    REQUIRE( lambda::is_unitary(V_star) );
}
#endif

TEST_CASE("Using Eigen3", "[decomposition]")
{
    Eigen::Matrix3d a = Eigen::Matrix3d::Random();
    Eigen::Matrix3d b = Eigen::Matrix3d::Random();
    Eigen::Matrix3d c = a * b;
    std::cout << c << "\n";
}