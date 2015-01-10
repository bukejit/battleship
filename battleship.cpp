/*
battleship.cpp
Mark Brankin 2015
simple battleship game
*/
#include <iostream>						// cout
#include <vector>						// vector
#include <stdlib.h>						// abs
using namespace std;
class coord
{
	public:
	int x;
	int y;
	bool hit;
	
	bool operator==(const coord & c)
	{
		if(this->x == c.x && this->y == c.y)
			return true;

		else
			return false;
	}
};
	
/* 
ship class 
holds all the information about a ship
screen fires at ship and ship returns whether it was a hit or not on that ship
*/
class ship
{
	
	bool sunk=false;					// Whether the Ship is sunk
	vector<coord> blocks;					// The ships vector of all coordinates and hit state
	int length;						// Length of the Ship in blocks
	string name; 						// Name of the Ship

	/*
	Function getCoordinate
	Loops, asking user for Coordinate until valid one is inputted
	Returns Valid Coordinate
	*/	
	coord getCoordinate()
	{
		
		string coordName;				// string where the name of the coordinate will be stored;
		while(1)					// Loop forever until the user breaks it with a valid coordinate
		{
			cin >> coordName;			// Get the input
			if(coordName[0] > 64 && coordName[0] < 75 && coordName[1] > 47 && coordName[1] < 58 && coordName[2] == 0)
								// These are the criteria for a valid coordinate, Ascii values of the string
				break;
			cout << "You entered an invalid coordinate. Try again: ";
								// Loop will get to here if the coordinate was invalid
		}
					
		coord returned;					// From here is the conversion to a coordinate
		returned.x = coordName[0] - 65;			// Subtract Ascii values to get the raw value
		returned.y = coordName[1] - 48;
		return returned;
	}
	/*
	Function getValidBackEnds
	gets the Valid back ends of the ship, given the front end passed
	Up to a maximum of 4
	*/
	void getValidBackEnds(vector<coord> & valids, coord C)
	{							// Populate vector with 4 potential back ends
		coord temp;
		int dif = length-1;
		temp = C; //hello
		temp.x += dif;
		valids.push_back(temp);
		temp = C;
		temp.x -= dif;
		valids.push_back(temp);
		temp = C; 
		temp.y += dif;
		valids.push_back(temp);
		temp = C;
		temp.y -= dif;
		valids.push_back(temp);
		
		for(int i=0; i<valids.size(); i++)		//Erase potential back ends which lie outside the screen
		{
			if(valids[i].x > 9 || valids[i].x < 0 || valids[i].y > 9 || valids[i].y < 0)
				valids.erase(valids.begin() + i);
		}
		return;
	}

	/*
	Function getBackEnd
	Get the back coordinate from the user, given vector populated with valid back ends given the front coordinate
	Returns the back coordinate
	*/
	coord getBackEnd(vector<coord> valids)
	{
								// Ask user for Coordinate
		cout << "Please enter back coordinate for the " << name << " from these coordinates: " << endl;;
		char c; 					// Char used in creation of player-friendly coordinates
		bool found = false;				// Bool used to break loop if player inputted valid coordinate
		coord returned;					// Coordinate which will be returned
		for(int i=0;i<valids.size();i++)		// Display valid back coordinates
			{
				c = valids[i].x + 65;
								// Coords are created from Ascii Values
				cout << c;
				c = valids[i].y + 48;
				cout << c << endl;
			}
		cout << "Enter Coord: ";
		while(1)					// Loop forever until Player breaks with valid Coordinate
		{
			returned = getCoordinate();		// Get Valid Coordinate
			for(int i=0;i<valids.size();i++)	// check if it matches any of the potentials
			{
				if(returned.x == valids[i].x && returned.y == valids[i].y)
					{
						found = true;	// if it does break out of the loop and signal the other loop to break
						break;
					}
			
			}
			if(found == true)			// Break out if matching coordinate has been found
					break;
			cout << "The Coordinate is not a valid back. Try again: ";

		}

		return returned;

	}
	/*
	Function createFinalCoords
	Creates the vector of blocks the ship will use in the game
	Returns nothing
	*/
	void createFinalCoords(coord frontCoord, coord backCoord)
	{
		int* differencer;				// Pointer to coordinate that iterates
		int difference;					// Difference between coordinates
		coord temp;					// Temporary coordinate that will be pushed into vector 

		if(frontCoord.x != backCoord.x)			// If the x coordinates are different iterate along x axis			
		{
			differencer = &temp.x;
			difference = frontCoord.x - backCoord.x;
		}
		else						// Else iterate along y axis
		{
			differencer = &temp.y;
			difference = frontCoord.y - backCoord.y;
		}

		for(int i=0;i<=abs(difference);i++)		// This iterates and pushes the blocks into the list
		{
			temp = frontCoord;
			if(difference < 0)
				*differencer += i;
			else
				*differencer -= i;
				
			blocks.push_back(temp);

		}

	}

	/*
	Function checkIfSunk
	sets the SUNK variable if all blocks have been hit
	returns nothing
	*/
	void checkIfSunk()
	{
		bool notSunk=false;				// This will be set if any of the blocks are not hit
		for(int i=0;i<blocks.size();i++)		// Cycle through the blocks
		{
			if(blocks[i].hit == 0)			// If any of them are not hit then set the notSunk variable and break
			{
				notSunk = true;
				break;
			}
		}

		if(!notSunk)					// set sunk to true if it got all the way through that loop
		{
			sunk = true;
		}
	}
	public:
	/*
	Function resetAllBlocks
	Resets all the hit state of all the blocks to false
	Returns nothing
	*/
	void resetAllBlocks()
	{
		for(int i=0;i<blocks.size();i++)
		{
			blocks[i].hit = 0;
		}

	}

	/*
	Ship Constructor
	Constructs the ship, asking the user to input the coordinates of the front and back end
	Parameters: the NAME of the ship, the LENGTH of the ship
	Returns nothing
	*/
	ship(string NAME, int LENGTH)
	{
		name = NAME;					// Set the class' variables to the parameters given			
		length = LENGTH;
		vector<coord> validBacks;			// initialise the vector which will hold the valid back ends to show the user
		
		cout << "Enter front coordinate for the " << name << ": ";
		coord frontCoord = getCoordinate();		// ask the user for the front coordinate
		getValidBackEnds(validBacks, frontCoord);	// calculate the valid back end for the given coordinate
		coord backCoord  = getBackEnd(validBacks);	// ask the user for the back-end coord out of the valids given
		createFinalCoords(frontCoord, backCoord);	// create the vector of blocks between the front and back ends for play
	
	}
	
	/*
	Function fireOn
	This is the function used for play for firing on the ship and seeing if its been hit/sunk
	Parameters: The coordinate fired upon
	Returns: The boolean of whether the ship has been hit or not
	*/
	bool fireOn(coord c)
	{	
		bool hit = false;			
		
		for(int i=0;i<blocks.size();i++)
		{
			if(blocks[i] == c)
			{	
				blocks[i].hit = true;
				hit = true;
				
			}
		}
		
		if(hit)
		{
			checkIfSunk();
			return true;
		}
		return false;

	}

	bool getSunkStatus()
	{
		return sunk;
	}

};


class screen
{
	vector<ship*> Ships;
	string names[5] = {"Aircraft Carrier", "Battleship", "Submarine", "Destroyer", "Patrol Boat"};
	int lengths[5] = {5,4,3,3,2};	


	bool checkCollisions(ship* s)
	{
		coord c;
		bool hitPassedShip=false;
		bool hitAddedShips=false;
		for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
			{
				c.x = i;
				c.y = j;
				hitPassedShip = s->fireOn(c);
				
				for(int k=0;k<Ships.size();k++)
				{
					if(Ships[k]->fireOn(c))
					{
						hitAddedShips = true;
						break;
					}

					else
						hitAddedShips = false;
				}

				if(hitPassedShip && hitAddedShips)
				{
					cout << i << "   " << j << endl;
					resetAllBlocks();		
					return false;
				}
			}
		
		resetAllBlocks();
		s->resetAllBlocks();
		return true;
		
	}

	void resetAllBlocks()
	{
		for(int i=0;i<Ships.size();i++)
		{
			Ships[i]->resetAllBlocks();
		}

	}
	public:
	
	screen()
	{
		bool noCollision=false;
		for(int i=0;i<5;i++)
		{
			noCollision=false;
			while(!noCollision)
			{
				ship* s = new ship(names[i], lengths[i]);
				if(checkCollisions(s))
				{
					noCollision = true;
					Ships.push_back(s);
				}

				else
				{	
					cout << "Failed!" << endl;
					delete s;			
				}
			}
		}
	}


};

int main()
{
	
	screen* s = new screen();
}
