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
	
	bool sunk;				// Whether the Ship is sunk
	vector<coord> blocks;			// The ships vector of all coordinates and hit state
	int length;				// Length of the Ship in blocks
	string name; 				// Name of the Ship

	/*
	Function getCoordinate
	Loops, asking user for Coordinate until valid one is inputted
	Returns Valid Coordinate
	*/	
	coord getCoordinate()
	{
		
		string coordName;		// string where the name of the coordinate will be stored;
		while(1)			// Loop forever until the user breaks it with a valid coordinate
		{
			cin >> coordName;	// Get the input
			if(coordName[0] > 64 && coordName[0] < 75 && coordName[1] > 47 && coordName[1] < 58 && coordName[2] == 0)
						// These are the criteria for a valid coordinate, Ascii values of the string
				break;
			cout << "You entered an invalid coordinate. Try again: ";
						// Loop will get to here if the coordinate was invalid
		}
					
		coord returned;			// From here is the conversion to a coordinate
		returned.x = coordName[0] - 65;	// Take away Ascii values to get the raw value
		returned.y = coordName[1] - 48;
		return returned;
	}
	/*
	Function getValidBackEnds
	gets the Valid back ends of the ship, given the front end passed
	Up to a maximum of 4
	*/
	void getValidBackEnds(vector<coord> & valids, coord C)
	{
		coord temp;
		temp = C;
		temp.x += length;
		valids.push_back(temp);
		temp = C;
		temp.x -= length;
		valids.push_back(temp);
		temp = C; 
		temp.y += length;
		valids.push_back(temp);
		temp = C;
		temp.y -= length;
		valids.push_back(temp);
		temp = C;
		
		for(int i=0; i<valids.size(); i++)
		{
			if(valids[i].x > 9 || valids[i].x < 0 || valids[i].y > 9 || valids[i].y < 0)
				valids.erase(valids.begin() + i);
		}
		return;
	}
	coord getBackEnd(vector<coord> valids)
	{
		cout << "Please enter back coordinate for the " << name << " from these coordinates: " << endl;;
		char c;
		bool found = false;
		coord returned;
		for(int i=0;i<valids.size();i++)
			{
				c = valids[i].x + 65;
				cout << c;
				c = valids[i].y + 48;
				cout << c << endl;
			}
		while(1)
		{
			returned = getCoordinate();
			for(int i=0;i<valids.size();i++)
			{
				if(returned.x == valids[i].x && returned.y == valids[i].y)
					{
						found = true;
						break;
					}
			
			}
			if(found == true)
					break;
			cout << "The Coordinate is not a valid back. Try again: ";

		}

		return returned;

	}
	public:
	ship(string NAME, int LENGTH)
	{
		name = NAME;
		length = LENGTH;
		cout << "Enter front coordinate for the " << name << ": ";

		coord frontCoord = getCoordinate();
		vector<coord> validBacks;	
		getValidBackEnds(validBacks, frontCoord);

		coord backCoord  = getBackEnd(validBacks);
		
		cout << "front is " << frontCoord.x << " " << frontCoord.y << endl;
		cout << "back is " << backCoord.x << " " << backCoord.y << endl;
	}

};

int main()
{
	cout << "hello!" << endl;
	ship* s = new ship("battleship", 3);
	return 0;
}
