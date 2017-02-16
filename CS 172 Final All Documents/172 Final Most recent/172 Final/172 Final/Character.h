#ifndef Character_h
#define Character_h
#include "Item.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Character{
private:
	int Health;
	int Mana;

public:
	int pos_x;
	int pos_y;
	vector<Item> CharacterItems;
	vector<Item> EquippedItems;
	Character();
	Character(int pos_x, int pos_y);
	Character(int pos_x, int pos_y, int Health, int Mana, int Attack_Value, int Defence_Value);
	void pAttack(Character& k);
	void Attack(Character& k);
	void pDefend(Character& k);
	void UseItem(Item I);
	void SelectItem();
	int Attack_value;
	int Defence_value;
	int GetHealth() { return Health; }
	void SetHealth(int H) { Health += H; }
	void PickUpItem(Item J);
	void TooManyItems();
	bool DropItem(int item, bool equipped);
	void UseEquippedItem(Character car);
	void StatBalance();
};

#endif
