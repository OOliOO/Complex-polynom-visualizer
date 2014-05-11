#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "UI.hpp"
using namespace std;

int main(){
    UI ui(1024,576);
    ui.start();

    return 0;
}
