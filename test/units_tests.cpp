#include "catch.hpp"
#include <lambda>

TEST_CASE("Simple unit conversions and arithmetic.", "[units]")
{
    using namespace lambda;

    kilometers kil = 1.54;
    meters met = kil/3;

    std::cout << kil << " km / 3 = " << kil/3 << " km" << std::endl;
    std::cout << kil << " km * 0.21 = " << kil*0.21 << " km" << std::endl;
    std::cout << kil << " km - " << met << " m = "
        << kilometers(kil - met) << " km, or "
        << meters(kil - met) << " m" << std::endl;

    seconds sec = 65.3;
    minutes min = 2.3;
    std::cout << sec << " s = " << minutes(sec) << " min" << std::endl;
    std::cout << sec << " s + " << min << " min = "
        << seconds(min + sec) << " s, or "
        << minutes(min + sec) << " min" << std::endl;

    using furlongs = length<std::ratio<201168, 1000>>;
    furlongs fur(4.623);
    std::cout << fur << " furlongs is equal to " 
              << kilometers(fur) << " km" << std::endl;
}
