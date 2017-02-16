#include "Character.h"

using namespace std;

Character::Character() { 
	pos_x = 0;
	pos_y = 0;
	Attack_value = 50;
	Defence_value = 5;
	Health = 200;
	Mana = 100;
}

Character::Character(int pos_x, int pos_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	Attack_value = 20;
	Defence_value = 5;
	Health = 100;
	Mana = 100;
}

Character::Character(int pos_x, int pos_y, int aHealth, int Mana, int Attack_Value, int Defence_Value)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->Attack_value = Attack_Value;
	this->Defence_value = Defence_Value;
	this->Health = aHealth;
	this->Mana = Mana;
}

// Cyruz Campos' functions start here
//This function is when the player attacks the monster
void Character::pAttack(Character& k){
	//Character Attacks
	Health -= k.Attack_value;
	return;
}

//This function is when the monster attacks the player
void Character::Attack(Character& k){
	//Monster Attacks
	k.SetHealth(-Attack_value);
	return;
}

//This function is when the player chooses to defend against the monster
void Character::pDefend(Character& k){
	//Character Defends
	Health += k.Defence_value;
	return; 
}
//Cyruz Campos' functions end here

// This function allows a character to use an item. If the item has a mana or health value, the item is consumed.
// Sam Wynsma's functions start here
void Character::UseItem(Item I)
{
	
	if (I.IsEquippable == false)
	{
		Health += I.GetHealth();
		Mana += I.GetMana();
		I.~Item();

	}
	else
	{
		Attack_value += I.GetAtt();
		Defence_value += I.GetDef();
		if (EquippedItems.size() <= 2)
			EquippedItems.push_back(I);
		else
		{
			bool removed = false;
			char Re;
			cout << "You cannot equip this item: you currently have to many equipped items. \n";
			cout << "Do you want to get rid of some of your current equipment? (Y/N) \n";
			cin >> Re;
			if (Re == 'Y')
			{
				while (!removed)
				{
					for (int k = 0; k < EquippedItems.size(); k++){
						removed = DropItem(k, true);
						if (removed) break;
					}
					

				}
			}
			else
				return;
		}
	}

}

// This function allows a character to drop an item. It removes an item either from the equipped items set, or
// from the non-equipped items that are in the inventory.
bool Character::DropItem(int item, bool equipped)
{
	if (equipped) {
		char answer;
		cout << "Do you want to drop the" << EquippedItems[item].GetName() << " (Y/N)";
		answer = getch();
		if (answer == 'Y')
		{
			EquippedItems.erase(EquippedItems.begin() + item);
			return true;
		}
		else
			return false;

	}
	else {
		char answer;
		cout << "Do you want to drop the" << CharacterItems[item].GetName() << " (Y/N)";
		answer = getch();
		if (answer == 'Y')
		{
			CharacterItems.erase(CharacterItems.begin() + item);
			return true;
		}
		else
			return false;
	}


}

// This function allows the user to choose which item to use in their inventory.
void Character::SelectItem()
{
	char answer = ' ';
	if (CharacterItems.size() > 0)
	{
		for (int i = 0; i < CharacterItems.size(); i++)
		{
			bool chosen = false;
			while (!chosen)
			{
				cout << CharacterItems[i].GetName() << endl;
				cout << "Do you want to use the " << CharacterItems[i].GetName() << " (Y\N) \n";
				answer = getch();
				if (answer == 'Y'){
					UseItem(CharacterItems[i]);
					CharacterItems.erase(CharacterItems.begin() + i);
					chosen = true;
				}
				else if (answer == 'N') {
					DropItem(i, false);
					chosen = true;

				}
			}
		}
	}
	else
	{
		cout << "You are not carrying anything. \n";
	}
}

// This function is called when the character picks up an item. 
// It removes the item from where it initially is and adds the item to the character's item list.
void Character::PickUpItem(Item J)
{
	CharacterItems.push_back(J);
	TooManyItems();
	J.~Item();
}

// This function is called whenever a character picks up an item. It forces the character to throw an item away.
void Character::TooManyItems()
{
	if (CharacterItems.size() > 10)
	{
		cout << "You have too many items. Choose one to throw away. \n";
		for (int i = 0; i < CharacterItems.size(); i++)
		{
			cout << i << ". " << CharacterItems[i].GetName();
		}

		int c;
		while (c > CharacterItems.size() || c < 0)
		{
			cin >> c;
			cout << "You chose to get rid of " << CharacterItems[c].GetName();
			CharacterItems[c].~Item();

		}
	}
}

// This function allows the character to use an item in combat. It is only called when a player comes into contact
// with a monster.
void Character::UseEquippedItem(Character car)
{
	char answer = ' ';
	if (EquippedItems.size() > 0)
	{
		for (int i = 0; i < EquippedItems.size(); i++)
		{
			bool chosen = false;
			while (!chosen)
			{
				cout << EquippedItems[i].GetName() << endl;
				cout << "Do you want to use the " << EquippedItems[i].GetName() << " (Y\N) \n";
				answer = getch();
				if (answer == 'Y'){
					Attack_value += EquippedItems[i].GetAtt();
					Defence_value += EquippedItems[i].GetDef();
					Attack(car);
					Attack_value -= EquippedItems[i].GetAtt();
					Defence_value -= EquippedItems[i].GetDef();
					chosen = true;
				}
				else if (answer == 'N') {
					chosen = true;

				}
			}
		}
	}
	else
	{
		cout << "You do not have anything equipped. \n";
	}
}

// End of Sam Wynsma's code for this .cpp file.



