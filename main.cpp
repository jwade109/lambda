#include <iostream>

#include <matrix.hpp>
#include <quaternion.hpp>

int main()
{
    lambda::matrix<3, 4, int> u
        (4, 5, 6, 7,
         6, 7, 8, 9,
         8, 9, 10, 11);
    lambda::matrix<4, 5, double> v
        (4, 5, 6, 7, 8,
         5, 6, 7, 8, 9,
         6, 7, 8, 9, 10,
         7, 8, 9, 10, 11);

    lambda::vector<3> x(1.1, 2, 4.5);
    lambda::vector<3, int> y(-3, 1, 7);

    std::cout << "u: " << u << std::endl;
    std::cout << "v: " << v << std::endl;
    std::cout << "2v: " << v*2 << std::endl;
    std::cout << "v/2: " << v/2 << std::endl;

    auto w = u*v;
    std::cout << "u*v: " << w << std::endl;

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "x+y: " << x+y << std::endl;
    std::cout << "x.y: " << lambda::inner_product(x, y) << std::endl;
    std::cout << "x*y: " << lambda::cross_product(x, y) << std::endl;
    std::cout << "unit vectors: " << lambda::unitx << " "
        << lambda::unity << " " << lambda::unitz << std::endl;

    lambda::matrix<2, 2> A(3, 4, 5, 6);
    std::cout << "A: " << A << ", det(A): "
        << lambda::det(A) << std::endl;

    lambda::matrix<3, 3> B
        (10, 2, 3,
         2, 30, 4,
         3, 4, 50);
    std::cout << "B: " << B << ", det(B): "
        << lambda::det(B) << std::endl;

    lambda::matrix<4, 4> C
        (6, 2, 3, 4,
         2, 6, 4, 5,
         3, 4, 7, 6,
         4, 5, 6, 7);
    std::cout << "C: " << C << ", det(C): "
        << lambda::det(C) << std::endl;

    lambda::quaternion<> q(1, 2, 3, 4);
    std::cout << q << std::endl;
    std::cout << q.vec() << std::endl;
    std::cout << q.scalar() << std::endl;

    return 0;
}
