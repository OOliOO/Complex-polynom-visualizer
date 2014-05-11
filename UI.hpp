#ifndef UI_HPP
#define UI_HPP

#include <future>
#include <vector>
#include <iostream>
#include <queue>

#include "drawer.hpp"
#include "streamtools.hpp"

union data_item{
    int64_t i;
    double f;
};

struct Command{
    enum CommandType{
        CLOSE,
        MOVE_TO,
        SET_ZOOM,
        ERROR,
        SET_LENGTH_MODE,
        HELP,
        SET_ARROW_DIST,
        SET_POLYNOM
    };
    data_item command_data[10];
    Polynom poly;
    CommandType type;
};

Command getCommands();

class UI{
public:
    UI(int w, int h);
    void start();
private:
    void act(Command cmd);
    void help();
    Drawer drawer;
};

#endif
