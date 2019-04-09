#ifndef LAMBDA_COMPLEX_HPP
#define LAMBDA_COMPLEX_HPP

namespace lambda
{

class complex
{
    public:

    complex();

    complex(double real, double imag);

    complex(const complex &c);

    complex& operator = (complex c);

    complex& operator += (complex c);

    complex& operator -= (complex c);

    complex& operator *= (double scalar);

    complex& operator *= (complex c);

    complex& operator /= (double scalar);

    complex& operator /= (complex scalar);

    double real() const;

    double& real();

    double imag() const;

    double& imag();

    private:

    double _real;
    double _imag;
};

complex operator + (complex c1, complex c2);

complex operator - (complex c1, complex c2);

complex operator * (complex c1, complex c2);

complex operator * (complex c, double scalar);

complex operator / (complex c1, complex c2);

complex operator / (complex c, double scalar);

complex operator - (complex c);

double arg(complex c);

double norm(complex c);

complex conj(complex c);

} // namespace lambda

#endif // LAMBDA_COMPLEX_HPP
