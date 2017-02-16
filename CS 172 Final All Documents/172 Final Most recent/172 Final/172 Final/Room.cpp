//Room.cpp
//Primarily by Derek Price


#include "Room.h"
#include <ctime>
//Contructor, adds doors and monsters
Room::Room(int sX, int sY, int index)
{
	dim_x = sX;
	dim_y = sY;
	roomCount = 0;

	int num_Baby_Unicorns = rand() % 2 + 1;
	int num_Items = (rand() % 3) + 1;

	this->index = index;


	for (int i = 0; i < (rand() % 3) + 2; i++) {
		add_Door();
	}

	for (int i = 0; i < num_Baby_Unicorns; i++) {
		add_Baby_Unicorn();
	}

}

//Adds door to current room, door will not occupy the same space as other doors
void Room::add_Door() {

	int facing = rand() % 4;



	int x,y;

	switch(facing) {
	case 0: x = dim_x - 1; y = rand() % (dim_y - 3) + 2; break;
	case 1: y = dim_y - 1; x = rand() % (dim_x - 3) + 2; break;
	case 2: x = 0; y = rand() % (dim_y - 3) + 2; break;
	case 3: y = 0; x = rand() % (dim_x - 3) + 2; break;
	}

	bool occupied = false;

	for (int i = 0; i < Doors.size(); i++) {
		if (Doors[i].pos_x == x && Doors[i].pos_y == y)
			occupied = true;
	}

	if (!occupied) {
		Door tmp =  Door(x, y, facing, index, roomCount++);
		Doors.push_back(tmp);

	}

}

Room::~Room() {


}

// Sam Wynsma's function for Room starts here.
// This function is called when a character touches an item. It removes the item from the room and adds it to the character's inventory.
void Room::CharacterEncounterItem(Character C)
{
	for (int n = 0; n < RoomItems.size(); n++)
	{
		if (C.pos_x = RoomItems[n].pos_x)
		{
			if (C.pos_y = RoomItems[n].pos_y)
			{
				RoomItems[n].pos_x = NULL;
				RoomItems[n].pos_y = NULL;
				C.PickUpItem(RoomItems[n]);
				C.TooManyItems();
			}
		}
	}
}
// Sam Wynsma's function for room ends here.

//Adds a monster to the current room
void Room::add_Baby_Unicorn() {
	bool stop = true;

	while (stop) {
		bool valid = true;
		int pos_x = rand() % (dim_x - 3) + 1;
		int pos_y = rand() % (dim_y - 3) + 1;

		for (int i = 0; i < Baby_Unicorns.size(); i++) {
			if (pos_x == Baby_Unicorns[i].pos_x && pos_y == Baby_Unicorns[i].pos_y)
				valid = false;
		}

		if (valid) {
			Character tmp(pos_x, pos_y);
			Baby_Unicorns.push_back(tmp);
			stop = false;
		}
	}
}


