#include <iostream>

#include <lambda>

int main()
{
    lambda::matrix<3, 4> u
        (4, 5, 6, 7,
         6, 7, 8, 9,
         8, 9, 10, 11);
    lambda::matrix<4, 5> v
        (4, 5, 6, 7, 8,
         5, 6, 7, 8, 9,
         6, 7, 8, 9, 10,
         7, 8, 9, 10, 11);

    lambda::matrix<3, 4> K;

    K = u;

    std::cout << "u: " << u << std::endl;
    std::cout << "K: " << K << std::endl;

    auto reduced = lambda::rref(v);
    std::cout << "v: " << v << std::endl;
    std::cout << "rref(v): " << reduced << std::endl;

    lambda::axis_angle aa;
    lambda::axis_angle ab({2, 3, 4}, 0.4);
    std::cout << "aa: " << aa << std::endl;
    std::cout << "ab: " << ab << std::endl;

    lambda::quaternion q(0.0, 0.3, 0.1, 0.4);
    aa = q;

    std::cout << "q: " << q << std::endl;
    std::cout << "aa: " << aa << std::endl;

    /* matrix, vector, quaternion tests

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
    std::cout << "q: " << q << std::endl;
    std::cout << "q vector: " << q.vec() << std::endl;
    std::cout << "q scalar: " << q.scalar() << std::endl;

    lambda::vector<3> k(4, -3, 5);
    std::cout << "k: " << k << std::endl;
    std::cout << "norm(k): " << lambda::euclidean_norm(k) << std::endl;
    std::cout << "norm(transpose(k)): "
        << lambda::euclidean_norm(lambda::transpose(k)) << std::endl;

    std::cout << lambda::identity<4>() << std::endl;

    */

    return 0;
}
