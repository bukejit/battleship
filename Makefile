all: bs

bs: battleship.cpp
	g++ battleship.cpp -o b -g -Wno-c++11-extensions -l ncurses
	ctags -R
