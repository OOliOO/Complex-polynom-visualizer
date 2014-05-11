#ifndef TERM_HPP
#define TERM_HPP
#include<complex>

class Term{
public:
    Term(std::complex<double> c, int e);
    std::complex<double> get(std::complex<double> input);
private:
    std::complex<double> coeff;
    int exponent;
};

#endif
