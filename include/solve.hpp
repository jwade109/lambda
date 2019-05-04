#ifndef LAMBDA_SOLVE_HPP
#define LAMBDA_SOLVE_HPP

#include <functional>
#include <limits>

namespace lambda
{

double newton_raphson(const std::function<double(double)> &f,
    double x0, size_t maxiter = 1000,
    double epsilon = std::numeric_limits<double>::epsilon());

double ddx(const std::function<double(double)> &f,
    double x, double epsilon = 0.01);

} // namespace lambda

#endif // LAMBDA_SOLVE_HPP
