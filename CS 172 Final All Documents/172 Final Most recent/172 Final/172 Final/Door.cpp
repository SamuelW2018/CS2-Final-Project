//Door.cpp
//By Derek Price

#include "Door.h"


Door::Door(int pX, int pY, int dir, int roomIndex, int doorIndex) {
	pos_x = pX;
	pos_y = pY;

	//if (dir > -1 && dir < 4) 
		facing = dir;
	facing_Backup = facing;
	this->roomIndex = roomIndex;
	this->doorIndex = doorIndex;

	linked = false;

	dest_doorIndex = -1;
	dest_roomIndex = -1;
}

Door::~Door()
{

}

