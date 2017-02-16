// Item.h
// Sam Wynsma

#include <string>
#include <vector>
using namespace std;

#ifndef ITEM_h
#define ITEM_h
class Item
{
private:
	int attackValue;
	int ManaValue;
	int HealthValue;
	int StrAdd;
	int DefAdd;
	string name;
	bool HasFailed;
	bool HasSucceeded;
	vector<Item> AllowedItems();
public:
	int pos_x;
	int pos_y;
	bool IsEquippable;
	bool IsEquipped;
	int GetMana() { return ManaValue; }
	int GetHealth() { return HealthValue; }
	int GetAtt() { return attackValue; }
	int GetStr() { return StrAdd; }
	int GetDef() { return DefAdd; }
	string GetName() { return name; }
	Item(int attackValue, int ManaValue, int HealthValue, int StrAdd, int DefAdd, string name, string equip);
	~Item();
};

#endif
