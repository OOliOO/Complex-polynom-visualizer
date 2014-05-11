#include "drawer.hpp"
#include <iostream>


Drawer::Drawer(int width, int height):w(width),h(height),origin(0,0){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode(w,h),"asdf",sf::Style::Titlebar,settings);
    window.setFramerateLimit(30);
    running=1;
    length_mode=NORMAL;
    arrow_dist=16;
    scale=1;
    data_set=0;
    setPointOfInterest(0, 0);
    recompute();
}

void Drawer::close(){
    running=0;
    window.close();
}

void Drawer::update(){
    checkEvents();
    drawAll();
    window.display();
}

void Drawer::setArrowDist(int new_dist){
    arrow_dist=new_dist;
    recompute();
}

void Drawer::setPointOfInterest(double x, double y){
    point_of_interest=std::complex<double>(x,y);
    origin=point_of_interest-std::complex<double>(w,h)/(2.*scale);
    recompute();
}

void Drawer::setScale(double s){
    scale=s;
    origin=point_of_interest-std::complex<double>(w,h)/(2.*scale);
    recompute();
}

void Drawer::setLengthMode(LengthMode mode){
    length_mode=mode;
    recompute();
}

void Drawer::setPolynom(Polynom p){
    poly=p;
    recompute();
}

bool Drawer::isRunning(){
    return running;
}

void Drawer::createMap(){
    data_w=std::max(w/arrow_dist - 1 ,0);
    data_h=std::max(h/arrow_dist - 1 ,0);
    if(data_set!=0)
        delete[] data_set;
    data_set = new Arrow*[data_h];
    for(int i=0; i<data_h; i++)
        data_set[i] = new Arrow[data_w];
}

void Drawer::checkEvents(){
    sf::Event event;
    while(window.pollEvent(event))
        if(event.type==sf::Event::Closed)
            running=0;
}

void Drawer::recompute(){
    window.clear();
    createMap();
    double max_l=0.;
    for(int i=0; i<data_h; i++)
        for(int e=0; e<data_w; e++){
            std::complex<double> r((e+1)*arrow_dist,(i+1)*arrow_dist);
            std::complex<double> r2=r/scale+origin;
            data_set[i][e].create(r,poly.get(r2));
            max_l=std::max(max_l,abs(poly.get(r2)));
        }
    double norm;
    if(max_l==0)
        norm=1;
    else
        norm=max_l/arrow_dist;

    double new_l;

    for(int i=0; i<data_h; i++)
        for(int e=0; e<data_w; e++)
            switch(length_mode){
                case NORMAL:
                    data_set[i][e].normalize(norm);
                    break;
                case UNIVERSAL:
                    data_set[i][e].setLength(arrow_dist);
                    break;
                case LOGARITHMIC:
                    new_l=std::log(1+data_set[i][e].getLength())/std::log(1+max_l);
                    data_set[i][e].setLength(new_l*arrow_dist);
                    break;
                case SQRT:
                    new_l=std::sqrt(data_set[i][e].getLength()/max_l);
                    data_set[i][e].setLength(arrow_dist*new_l);
                    break;
            }
}

void Drawer::drawAll(){
    for(int i=0; i<data_h; i++)
        for(int e=0; e<data_w; e++)
            window.draw(data_set[i][e]);
}
