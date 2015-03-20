all: bs

bs: battleship.cpp
	g++ battleship.cpp -o b -g -std=c++11 -l ncurses
	ctags -R
