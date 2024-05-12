#include <catch2/catch.hpp>
#include <lambda/lambda.hpp>

TEST_CASE("Test elementary cellular automata rules.", "[automata]")
{
    std::cout << lambda::pretty(30, 20, {1});
    std::cout << lambda::pretty(60, 20, {1});
    std::cout << lambda::pretty(90, 20, {1});
    std::cout << lambda::pretty(182, 20, {1});
    std::cout << lambda::pretty(220, 20, {1});
    std::cout << lambda::pretty(222, 20, {1});
    std::cout << lambda::pretty(250, 20, {1});
}
