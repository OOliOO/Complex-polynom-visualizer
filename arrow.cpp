#include "arrow.hpp"
#include <math.h>

Arrow::Arrow(std::complex<double> r, std::complex<double> dr): position(r), size(dr){
    norm = 1.;
}

void Arrow::create(std::complex<double> r, std::complex<double> dr){
    position=r;
    size=dr;
    norm=1.;
}


void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::RectangleShape line=sf::RectangleShape(sf::Vector2f(abs(size)/norm,1));
    line.setRotation(180*std::arg(size)/M_PI);
    line.setPosition(sf::Vector2f(std::real(position),std::imag(position)));

    target.draw(line);

    sf::CircleShape ball=sf::CircleShape(3);
    ball.setOrigin(3,3);
    ball.setPosition(sf::Vector2f(std::real(position),std::imag(position)));
    target.draw(ball);
}

void Arrow::normalize(double n){
    norm=n;
}

void Arrow::setLength(double length){
    norm=1.;
    if(std::abs(size)!=0)
        norm=abs(size)/length;
}

double Arrow::getLength(){
    return abs(size);
}
