#ifndef POLYNOM_HPP
#define POLYNOM_HPP
#include "term.hpp"
#include<vector>
class Polynom{
public:
    Polynom();
    void add(Term t);
    std::complex<double> get(std::complex<double> input);
private:
    std::vector<Term> terms;
};

#endif
