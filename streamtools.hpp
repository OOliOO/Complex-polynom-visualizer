#ifndef STREAM_TOOLS_HPP
#define STREAM_TOOLS_HPP
#include <iostream>
#include <sstream>
#include "polynom.hpp"

inline bool isFloat(std::string str){
    std::stringstream iss(str);
    double f;
    iss>>f;
    return iss.eof()&&!iss.fail();
}

inline double toFloat(std::string str){
    std::stringstream iss(str);
    double f;
    iss>>f;
    return f;
}


inline Polynom getPolynom(){
    Polynom ret;
    for(;;){
        int e;
        double re,im;
        ask1:;
        std::cout<<"Add term? (y/n) ";
        std::string response;
        std::cin>>response;
        std::cin.clear();
        if(response=="n")
            break;
        if(response!="y"&&response!="n"){
            std::cout<<"invalid intput!\n";
            goto ask1;
        }

        std::string exponent;
        ask2:;
        std::cout<<"Exponent: ";
        std::cin>>exponent;
        std::cin.clear();
        if(isFloat(exponent)){
            e=toFloat(exponent);
        }else{
            std::cout<<"invalid intput!\n";
            goto ask2;
        }

        std::string imag,real;
        ask3:;
        std::cout<<"Coefficient (real imag): ";
        std::cin>>real>>imag;
        std::cin.clear();
        if(isFloat(real)&&isFloat(imag)){
            re=toFloat(real);
            im=toFloat(imag);
        }else{
            std::cout<<"invalid intput!\n";
            goto ask3;
        }
        Term t(std::complex<double>(re,im),e);
        ret.add(t);
    }
    return ret;
}

#endif
