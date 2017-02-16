//Door.h
//By Derek Price


#ifndef Door_h
#define Door_h

#include <iostream>
using namespace std;

class Door{
public:
	int pos_x;
	int pos_y;
	Door(int pX, int pY, int dir, int roomIndex, int doorIndex);
	~Door();

	int roomIndex;
	int doorIndex;

	int dest_roomIndex;
	int dest_doorIndex;

	bool linked;
	int opposite() {
		switch (facing) {
		case 0: return 2;
		case 1: return 3;
		case 2: return 0;
		case 3: return 1;
		}
	}

	int getFacing() {if (facing != facing_Backup) facing = facing_Backup;  return facing;}
private:
	int facing;
	int facing_Backup;
};




#endif
