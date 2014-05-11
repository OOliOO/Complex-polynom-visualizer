#include "polynom.hpp"
#include <iostream>
Polynom::Polynom(){}

void Polynom::add(Term t){
    terms.push_back(t);

}

std::complex<double> Polynom::get(std::complex<double> input){
    std::complex<double> ret;
    for(Term t:terms)
        ret+=t.get(input);
    return ret;
}


