/*
battleship.cpp
Mark Brankin 2015
simple battleship game
*/
#include <iostream>
#include <vector>
using namespace std;
typedef struct
{
	int x;
	int y;
	int hit;
} coord;
/* 
ship class 
holds all the information about a ship
screen fires at ship and ship returns whether it was a hit or not on that ship
*/
class ship
{
	bool sunk;
	vector<coord> blocks;
	int length;
	string name; 
	
	public:
	ship(string NAME)
	{
		string coordName;
		name = NAME;
		cout << "Enter first coordinate for " << name << ": ";
		cin >> coordName;
		cout << "coordinate is " << coordName << "!" << endl;
	}
};

int main()
{
	cout << "hello!" << endl;
	ship* s = new ship("battleship");
	return 0;
}
