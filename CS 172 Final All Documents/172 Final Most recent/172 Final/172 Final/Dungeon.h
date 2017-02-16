//Dungeon.h
//Primarily by Derek Price, with contributions by other memebers

#ifndef Dungeon_h
#define Dungeon_h

#include "Room.h"
#include "Character.h"
#include "Windows.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

const int room_DimX_Min = 6;
const int room_DimX_Max = 12;
const int room_DimY_Min = 6;
const int room_DimY_Max = 12;


using namespace std;

class Dungeon {
public:
	Dungeon();
	void movePlayer(int direction);
	vector<vector<char>> render();
	void GetItemsFromFile();
	void renderFrame();
	Character GetPlayer() { return Player; }
	vector<Item> AvailableItems;
	void useitem();
	void pickupItem();
	void Player_Attack();
	void Player_Defend();
	
private:

	string IntToString(int input);
	vector<Room> Rooms;
	Character Player;

	void add_Room();
	int roomCount;
	int active;
	int Threat;
	void addDestination(int roomIndex, int doorIndex);
	void Monster_Act(Character& car);
	void Monster_Move(Character& car);
	bool EndGame(Character& car);
	void KillMonster(Room& r1);
	void GenerateItems(int targetRoom);
};




#endif