// units.cpp

#include <units.hpp>

namespace lambda
{

// ===============================================================
// SI BASE UNITS STRINGS

namespace dimensions
{

const char* dimensionless::str = "~";
const char* length::str = "m";
const char* mass::str = "kg";
const char* time::str = "s";
const char* temperature::str = "K";
const char* current::str = "A";
const char* luminosity::str = "cd";
const char* substance::str = "mol";

} // namespace dimensions

} // namespace lambda
