//Room.h
//Primarily by Derek Price

#ifndef Room_h
#define Room_h

#include "Door.h"
#include <vector>
#include <iostream>
#include "Item.h"
#include "Character.h"

using namespace std;

class Room{
private:
	
public:
	Room(int sX, int sY, int index);
	~Room();
	int dim_x;
	int dim_y;
	int roomCount;

	vector<Item> RoomItems;
	int index;

	vector<Door> Doors;
	void add_Baby_Unicorn();
	vector<Character> Baby_Unicorns;
	void add_Door();
	// void GenerateItems();
	void CharacterEncounterItem(Character C);

};




#endif