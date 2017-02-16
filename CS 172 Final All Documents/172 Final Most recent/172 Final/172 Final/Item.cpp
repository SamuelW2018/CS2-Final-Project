#include "Item.h"

// This entire file was coded by Sam Wynsma.
// Constructor for item function. The item function is used a lot in functions but it does not enact many functions of its own.
Item::Item(int attackValue, int ManaValue, int HealthValue, int StrAdd, int DefAdd, string name, string Equip)
{
	this->name = name;
	this->attackValue = attackValue;
	this->DefAdd = DefAdd;
	this->HealthValue = HealthValue;
	this->ManaValue = ManaValue;
	this->StrAdd = StrAdd;
	bool HasFailed = false;
	bool HasSucceeded = false;
	bool IsEquipped = false;
	if (Equip == "Yes")
		IsEquippable = true;
	else
		IsEquippable = false;
}







Item::~Item()
{

}
