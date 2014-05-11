#ifndef DRAWER_HPP
#define DRAWER_HPP
#include<SFML/Graphics.hpp>
#include "arrow.hpp"
#include "polynom.hpp"


class Drawer{
public:
    enum LengthMode{
        NORMAL,
        UNIVERSAL,
        LOGARITHMIC,
        SQRT
    };


    Drawer(int width, int height);
    void setArrowDist(int new_dist);
    void setPointOfInterest(double x, double y);
    void setScale(double scale);
    void setLengthMode(LengthMode mode);
    void setPolynom(Polynom p);
    bool isRunning();
    void update();
    void close();
private:
    Polynom poly;
    int w,h;
    int data_w, data_h;
    bool running;
    sf::RenderWindow window;
    int arrow_dist;
    std::complex<double> point_of_interest;
    std::complex<double> origin;
    double scale;
    Arrow** data_set;
    LengthMode length_mode;

    void checkEvents();
    void recompute();
    void drawAll();
    void createMap();
};

#endif
