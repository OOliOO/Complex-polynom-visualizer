#ifndef ARROW_HPP
#define ARROW_HPP

#include<SFML/Graphics.hpp>
#include<complex>

class Arrow: public sf::Drawable{
public:
    Arrow(std::complex<double> position, std::complex<double> size);
    Arrow():position(0.,0.),size(0.,0.){}

    void create(std::complex<double> position, std::complex<double> size);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void normalize(double norm);
    void setLength(double length);
    double getLength();
private:
    std::complex<double> position, size;
    double norm;
};

#endif
