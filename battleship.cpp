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
Function getCoordinate
Loops, asking user for Coordinate until valid one is inputted
Returns Valid Coordinate
*/	
coord getCoordinate()
{

	string coordName;					// string where the name of the coordinate will be stored;
	while(1)							// Loop forever until the user breaks it with a valid coordinate
	{
		cin >> coordName;				// Get the input
		if(coordName[0] > 64 && coordName[0] < 75 && coordName[1] > 47 && coordName[1] < 58 && coordName[2] == 0)
										// These are the criteria for a valid coordinate, Ascii values of the string
			break;
	
	cout << "You entered an invalid coordinate. Try again: ";
										// Loop will get to here if the coordinate was invalid
}
			
coord returned;							// From here is the conversion to a coordinate
returned.x = coordName[0] - 65;			// Subtract Ascii values to get the raw value
returned.y = coordName[1] - 48;
return returned;
}

/* 
ship class 
holds all the information about a ship
screen fires at ship and ship returns whether it was a hit or not on that ship
*/
class ship
{
	
	bool sunk=false;					// Whether the Ship is sunk
	vector<coord> blocks;				// The ships vector of all coordinates and hit state
	int length;							// Length of the Ship in blocks
	string name; 						// Name of the Ship

	
	/*
	Function getValidBackEnds
	gets the Valid back ends of the ship, given the front end passed
	Up to a maximum of 4
	*/
	void getValidBackEnds(vector<coord> & valids, coord C)
	{									// Populate vector with 4 potential back ends
		coord temp;
		int dif = length-1;
		temp = C;
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
		char c; 								// Char used in creation of player-friendly coordinates
		bool found = false;						// Bool used to break loop if player inputted valid coordinate
		coord returned;							// Coordinate which will be returned
		for(int i=0;i<valids.size();i++)		// Display valid back coordinates
			{
				c = valids[i].x + 65;
												// Coords are created from Ascii Values
				cout << c;
				c = valids[i].y + 48;
				cout << c << endl;
			}
		cout << "Enter Coord: ";
		while(1)								// Loop forever until Player breaks with valid Coordinate
		{
			returned = getCoordinate();			// Get Valid Coordinate
			for(int i=0;i<valids.size();i++)	// check if it matches any of the potentials
			{
				if(returned.x == valids[i].x && returned.y == valids[i].y)
					{
						found = true;			// if it does break out of the loop and signal the other loop to break
						break;
					}
			
			}
			if(found == true)					// Break out if matching coordinate has been found
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
		int* differencer;						// Pointer to coordinate that iterates
		int difference;							// Difference between coordinates
		coord temp;								// Temporary coordinate that will be pushed into vector 

		if(frontCoord.x != backCoord.x)			// If the x coordinates are different iterate along x axis			
		{
			differencer = &temp.x;
			difference = frontCoord.x - backCoord.x;
		}
		else									// Else iterate along y axis
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
		bool notSunk=false;					// This will be set if any of the blocks are not hit
		for(int i=0;i<blocks.size();i++)	// Cycle through the blocks
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
		name = NAME;								// Set the class' variables to the parameters given			
		length = LENGTH;
		vector<coord> validBacks;					// initialise the vector which will hold the valid back ends to show the user
		
		cout << "Enter front coordinate for the " << name << ": ";
		coord frontCoord = getCoordinate();			// ask the user for the front coordinate
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
		
		for(int i=0;i<blocks.size();i++)		//cycle through blocks and check whether the passed coordinate matches
		{
			if(blocks[i] == c)
			{	
				blocks[i].hit = true;
				hit = true;
				
			}
		}
		
		if(hit)									//if a block was hit, check whether the ship was also sunk (all blocks are now hit)
		{
			checkIfSunk();
			return true;
		}
		return false;

	}

	bool getSunkStatus()						//Getter for sunk status
	{
		return sunk;
	}

};

/*
screen class
This class is in charge of drawing the board onto the player's screen for play
This is achieved using ascii escape sequences
*/
class screen
{
	coord seaState[10][10];
	
	/*
	Function drawSea
	This function draws the initial grid which the ships will be drawn onto
	Parameters: None
	Returns: None
	*/
	
	public:	
	void drawSea()
	{
		char ESC = 0x1B;
		cout << ESC << "[2J";
		/*ANSI Escape Stuffs */
		return;
	}
	
	/*
	screen constructor
	This is called by the sea constructor at the start of the game.
	It is be passed a 2D array which the ships will have filled in.
	This shows the positions of the ships so that they can be drawn
	*/
	screen(coord grid[10][10])
	{
		for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				grid[i][j] = seaState[i][j];
		drawSea();
	}

};




/*
sea class
This class constructs and coordinates the ships, and passes coordinates between the ships and the user.
*/
class sea
{
	vector<ship*> Ships;						//Contains all ships belonging to the user
	string names[5] = {"Aircraft Carrier", "Battleship", "Submarine", "Destroyer", "Patrol Boat"};
	int lengths[5] = {5,4,3,3,2};				//Names and Lengths of the ships
	screen* sn;

	/*
	Private Function checkCollisions
	Checks whether the passed ship collides with already constructed ships
	It does this by 'firing' on every single square on the board on every ship including all ships previously constructed and the one passed
	If the passed ship returns 'hit' on the same coord as a previously constructed ship it collides and needs to be reconstructed
	This is a hack :-)
	Parameters: ship pointer s, ship to be checked for collisions
	Returns: boolean. TRUE if no collisions
	*/
	bool checkCollisions(ship* s)
	{
		coord c;								// coordinate to be used to cycle through entire board			
		bool hitPassedShip=false;				// bool used to record if the parameter ship has been 'hit' by current coord
		bool hitAddedShips=false;				// bool used to record if any of the previously constructed ships have been 'hit' by current coord
		screen* sn;
		
		
		
		for(int i=0;i<10;i++)					// cycle through all squares on board and fire on all ships in vector and also passed ship
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
												// if both have been hit on same iteration, collision!
				{
					resetAllBlocks();			// reset hit status of all boats in vector
					return false;				// return false, collision
				}
			}
		
		resetAllBlocks();						// if it gets here there was no collision, reset all blocks in vector
		s->resetAllBlocks();					// also reset all blocks in passed ship as its now going to be put into the vector
		return true;
		
	}
	
	/*
	Private Function resetAllBlocks
	Class screen
	resets the hit status of all the ships in the vector
	Parameters: None
	Returns: None
	*/
	void resetAllBlocks()
	{	
		for(int i=0;i<Ships.size();i++)
		{
			Ships[i]->resetAllBlocks();			// Call each ships reset function
		}

	}

	/*
	Private Function fireOn
	Calls the fireOn function for all the ships and returns whether it was a hit or not
	Parameters: coord c, the coordinate fired upon
	Return: bool hit, whether that was a hit or a miss
	*/
	
	bool fireOn(coord c)
	{
		bool hit;
		
		for(int i=0;i<Ships.size();i++)
		{	
				if((hit = Ships[i]->fireOn(c)))
						break;
		}
			
		return hit;
	}
	public:
	/*
	Public sea Constructor
	Constructs each ship for play, checks whether they collide.
	Parameters: None
	Returns: Constructed screen
	*/		
	sea()
	{
		bool noCollision=false;					// boolean to record if there has been a collision
		for(int i=0;i<5;i++)					// create 5 ships
		{
			noCollision=false;
			while(!noCollision)					// loop until the user makes a ship without a collision
			{
				ship* s = new ship(names[i], lengths[i]);
				if(checkCollisions(s))
				{
					noCollision = true;
					Ships.push_back(s);			// put the ship onto the vector if it doesn't collide
				}

				else
				{	
					cout << "This Ship has collided with another, please try again." << endl;
					delete s;					// delete and try again if it did collide	
				}
			}
		}
		
		coord grid[10][10];
		sn = new screen(grid);
	}
	

	/*
	Public Function Play
	Main function for flow of the entire game
	Parameters: None
	Returns: None
	*/
	void play()
	{
		bool win = false;
		bool hit = false;
		coord c;

		while(!win)
		{
			cout << "Enter Coordinate to Fire: " << endl;
			c =	getCoordinate();
			hit = fireOn(c);
			
			if(hit)
			{	
				cout << "hit!" << endl;
			}
			else
				cout << "miss!" << endl;	

		}

	}

};

int main()
{	
	sea* s = new sea();
	s->play();
}
