#include "term.hpp"

Term::Term(std::complex<double> c, int e){
    coeff=c;
    exponent=e;
}

std::complex<double> Term::get(std::complex<double> input){
    return coeff*pow(input,exponent);
}
