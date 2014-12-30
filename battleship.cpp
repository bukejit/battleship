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
	
	string getCoordinate()
	{
		string coordName;
		while(1)
		{
			cin >> coordName;
			if(coordName[0] > 64 && coordName[0] < 75 && coordName[1] > 47 && coordName[1] < 58)
				break;
			cout << "You entered an invalid coordinate. Try again: ";
		}

		return coordName;
	}
	public:
	ship(string NAME)
	{
		string coordName;
		name = NAME;
		cout << "Enter first coordinate for " << name << ": ";

		coordName = getCoordinate();
		cout << "Valid coordinate is " << coordName << endl;	
	}

};

int main()
{
	cout << "hello!" << endl;
	ship* s = new ship("battleship");
	return 0;
}
