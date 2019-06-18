#include "catch.hpp"
#include <lambda>

TEST_CASE("Compute arbitrary CRC.", "[crc]")
{
    lambda::crc(std::bitset<14>(0b11010011101100),
                std::bitset<4>(0b1011));

    lambda::crc(12345678, 
}

