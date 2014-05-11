all:
	g++ arrow.cpp drawer.cpp main.cpp polynom.cpp term.cpp UI.cpp  -o CFV -lsfml-graphics -lsfml-window -lsfml-system -std=c++11 -Wl,--no-as-needed -pthread -s
