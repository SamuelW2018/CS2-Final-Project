//Dungeon.cpp
//Primarily by Derek Price, with contributions by other memebers

#include "Dungeon.h"


Dungeon::Dungeon() {
	GetItemsFromFile();
	roomCount = 0;
	active = 0;

	add_Room();
	Player.pos_x = Rooms[0].dim_x / 2;
	Player.pos_y = Rooms[0].dim_y / 2;

	Threat = 0;
}

void Dungeon::add_Room() {

	Room tmp(rand() % (room_DimX_Max - room_DimX_Min) + room_DimX_Min, rand() % (room_DimY_Max - room_DimY_Min) + room_DimY_Min, roomCount);
	int target = roomCount;
	roomCount++;
	Rooms.push_back(tmp);

	int Num_Items = (rand() % 3) + 1;
	for (int k = 0; k < Num_Items; k++)
		GenerateItems(target);
}

void Dungeon::movePlayer(int direction) {
	for (int i = 0; i < Rooms[active].Baby_Unicorns.size(); i++) {
		Monster_Act(Rooms[active].Baby_Unicorns[i]);
	}

	for (int i = 0; i < Rooms[active].Baby_Unicorns.size(); i++) {
		Monster_Move(Rooms[active].Baby_Unicorns[i]);
	}

	switch (direction) {
	case 0 :if (Player.pos_x < Rooms[active].dim_x - 1) Player.pos_x++; break;
	case 1 :if (Player.pos_y  > 0) Player.pos_y--; break;
	case 2 :if (Player.pos_x > 0) Player.pos_x--; break;
	case 3 :if (Player.pos_y < Rooms[active].dim_y - 1) Player.pos_y++; break;
	}

	for (int i = 0; i < Rooms[active].Doors.size(); i++) {
		if (Player.pos_x == Rooms[active].Doors[i].pos_x && Player.pos_y == Rooms[active].Doors[i].pos_y) {
			if (!(Rooms[active].Doors[i].linked)){
				addDestination(active, i);
			}
			int dest_room = Rooms[active].Doors[i].dest_roomIndex;
			int dest_door = Rooms[active].Doors[i].dest_doorIndex;
			if (dest_door < 0 || dest_room < 0) break;
			Player.pos_x = Rooms[dest_room].Doors[dest_door].pos_x;
			Player.pos_y = Rooms[dest_room].Doors[dest_door].pos_y;
			active = dest_room;
			if (active >= Rooms.size()){
				cout << "Active room index out of range" << " press enter to continue";
				char empty;
				cin >> empty;
			}
			if (Player.pos_x > Rooms[active].dim_x || Player.pos_y > Rooms[active].dim_y)
				cout << "Player postion out of range";
			break;
		}
	}
}

void Dungeon::addDestination(int roomIndex, int doorIndex){
	if (Rooms[roomIndex].Doors[doorIndex].roomIndex != roomIndex){
		cout << "Start door lost";
		cin >> roomIndex;
		return;
	}
	Door start_Backup = Rooms[roomIndex].Doors[doorIndex];
	int count = 0;
	while (true) {
		add_Room(); //This is the spot where Start has it's values jumbled
		vector<Door*> Viable;
		/*if (start.sourceIndex != roomIndex){
		cout << "Start door lost";
		cin >> roomIndex;
		return;
		}*/
		for (int i = 0; i < Rooms.size(); i++) 
			for (int j = 0; j < Rooms[i].Doors.size(); j++)
				if ((!Rooms[i].Doors[j].linked)/**/)
					if (abs(Rooms[i].Doors[j].getFacing() - Rooms[roomIndex].Doors[doorIndex].getFacing()) == 2)
						Viable.push_back(& Rooms[i].Doors[j]);

		if (Viable.size() != 0) {		
			int pick = rand() % Viable.size();
			Rooms[roomIndex].Doors[doorIndex].dest_roomIndex = Viable[pick]->roomIndex;
			Rooms[roomIndex].Doors[doorIndex].dest_doorIndex = Viable[pick]->doorIndex;
			Viable[pick]->dest_roomIndex = Rooms[roomIndex].Doors[doorIndex].roomIndex;
			Viable[pick]->dest_doorIndex = Rooms[roomIndex].Doors[doorIndex].doorIndex;
			Rooms[roomIndex].Doors[doorIndex].linked = true;
			Viable[pick]->linked = true;
			//cout << "Door " << &start << " Linked to door " << Viable[pick] << endl;
			break;
		}
		count++;
	
		if (count > 50)
			break;
		//if (start.getFacing() < 0 || start.getFacing() > 3)
		//	cout << "Door facing out of range: " << start.getFacing() << endl;
	}
}

vector<vector<char>> Dungeon::render() {
	vector<vector<char>> tmp;
	for (int i = 0; i < Rooms[active].dim_y; i++) {
		vector<char> line;
		for (int j = 0; j < Rooms[active].dim_x; j++) {
			if (i == 0 || i == Rooms[active].dim_y - 1 || j == 0 || j == Rooms[active].dim_x - 1){
				line.push_back('=');
			} else {
				line.push_back('.');
			}
		}
	tmp.push_back(line);
	}
	for (int i = 0; i < Rooms[active].Doors.size(); i++){

		tmp[Rooms[active].Doors[i].pos_y][Rooms[active].Doors[i].pos_x] = '0';
	}

	for (int i = 0; i < Rooms[active].Baby_Unicorns.size(); i++) {
		tmp[Rooms[active].Baby_Unicorns[i].pos_y][Rooms[active].Baby_Unicorns[i].pos_x] = '&';
	}

	for (int i = 0; i < Rooms[active].RoomItems.size(); i++)
	{
		tmp[Rooms[active].RoomItems[i].pos_y][Rooms[active].RoomItems[i].pos_x] = '+';
	}

	tmp[Player.pos_y][Player.pos_x] = '@';


	return tmp;
}


// Start of Cyruz Campos' (mostly) code for dungeon.
//This function allows the monster to attack the player when in range
void Dungeon::Monster_Act(Character& car){
	if (abs(Player.pos_x - car.pos_x) < 2 && abs(Player.pos_y - car.pos_y) < 2){

		char choice;
		cout << "You are being attacked by a monster. What do you wish to do? \n";
		cout << " 1. Attack \n 2. Defend \n 3. Use Item ";
		choice = getch();
		if (choice == '1')
		{
			Player.Attack(car);
			car.Attack(Player);
		}
		else if (choice == '2')
		{
			Player.pDefend(Player);
			car.Attack(Player);
		}
		else if (choice == '3')
		{
			Player.UseEquippedItem(car);
			car.Attack(Player);
		}
		else
		{
			Player.Attack(car);
			car.Attack(Player);
		}

		KillMonster(Rooms[active]);
		if (EndGame(Player))
		{
			exit(0);
		}
	}
}

//This function allows the monster to move freely towards the player
void Dungeon::Monster_Move(Character& car){
	if (Player.pos_x > car.pos_x){
		car.pos_x++;
	}
	if (Player.pos_x < car.pos_x){
		car.pos_x--;
	}

	if (Player.pos_y > car.pos_y){
		car.pos_y++;
	}
	if (Player.pos_y < car.pos_y){
		car.pos_y--;
	}
}

//This function allows the game to end when the player reaches 0 health points
bool Dungeon::EndGame(Character& car)
{
	if (car.GetHealth() <= 0)
	{
		cout << "You have expired. You lose. " << endl;
		return true;
		
	}
	return false;
}

//This function ensures that the monster will be removed from the active room when their health reaches 0 
void Dungeon::KillMonster(Room& r1)
{
	for (int i = 0; i < r1.Baby_Unicorns.size(); i++)
	{
		if (r1.Baby_Unicorns[i].GetHealth() <= 0)
		{
			r1.Baby_Unicorns.erase(r1.Baby_Unicorns.begin() + i);
			cout << "Monster has been defeated. " << endl;
		}
	}
}

//This function allows the player to attack whenever they choose
void Dungeon::Player_Attack(){
	for (int i = 0; i < Rooms[active].Baby_Unicorns.size(); i++) {
		if (abs(Player.pos_x - Rooms[active].Baby_Unicorns[i].pos_x) < 2 && abs(Player.pos_y - Rooms[active].Baby_Unicorns[i].pos_y) < 2){
			Rooms[active].Baby_Unicorns[i].pAttack(Player);
		}
	}
}

//This function allows the player to defend whenever they choose
void Dungeon::Player_Defend(){
	Player.pDefend(Player);
}
// Cyruz Campos' code for this .cpp file ends here.

void Dungeon::renderFrame() {
	const int screenDimX = 72;
	const int screenDimY = 24;

	vector<vector<char>> GUI;

	for (int i = 0; i < screenDimY; i++) {
		vector<char> line;
		for (int j = 0; j < screenDimX; j++) {
			if (i == 0 || i == screenDimY - 1 || j == 0 || j == screenDimX - 1 || (i == 19 && j < 20) || (j == 19 && i < 20)){
				line.push_back('#');
			}
			else {
				line.push_back(' ');
			}
		}
		GUI.push_back(line);
	}


	vector<vector<char>> Room = render();

	int Xoffset = 4 + ((12 - Room[0].size()) / 2);
	int Yoffset = 4 + ((12 - Room.size()) / 2);

		for (int i = 0; i < Room.size(); i++) {
			for (int j = 0; j < Room[0].size(); j++) {
				GUI[i + Yoffset][j + Xoffset] = Room[i][j];
			}
		}

	string roomNumber = "Room: " + IntToString(active);

	for (int i = 0; i < roomNumber.size(); i++) {
		GUI[20][i + 2] = roomNumber[i];
	}

	string threatLevel = "Threat: " + IntToString(Threat);

	for (int i = 0; i < threatLevel.size(); i++) {
		GUI[21][i + 2] = threatLevel[i];
	}

	string playerHealth = "Health: " + IntToString(Player.GetHealth());

	for (int i = 0; i < playerHealth.size(); i++) {
		GUI[2][i + 20] = playerHealth[i];
	}

	string potions = "Items: " + IntToString(Player.CharacterItems.size());

	for (int i = 0; i < potions.size(); i++) {
		GUI[3][i + 20] = potions[i];
	}


	COORD spot = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), spot);
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < screenDimX; j++) {
			cout << ' ';
		}
		cout << endl;
	}




	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), spot);
	for (int i = 0; i < GUI.size(); i++) {
		for (int j = 0; j < GUI[0].size(); j++) {
			cout << GUI[i][j];
		}
		cout << endl;
	}

}

string Dungeon::IntToString(int input) {
	string output;
	bool start = false;
	for (int i = 0; i < 16; i++) {
		int tmp = input / pow(10, 15 - i);
		if (tmp != 0 || start == true){
			output += static_cast<char>(tmp + 48);
			start = true;
		}
		input -= tmp * pow(10, 15 - i);
	}
	if (output.size() == 0)
		output += '0';

	return output;

}

// Start of Sam Wynsma's (mostly) code for dungeon.
// This function allows rooms to generate items in them.
void Dungeon::GenerateItems(int targetRoom)
{
	bool stop = true;

	while (stop) {
		bool valid = true;
		int pos_x = rand() % (Rooms[targetRoom].dim_x - 3) + 1;
		int pos_y = rand() % (Rooms[targetRoom].dim_y - 3) + 1;

		// for (int i = 0; i < Rooms[active - 1].RoomItems.size(); i++) {
			// if (pos_x == Rooms[active - 1].RoomItems[i].pos_x && pos_y == Rooms[active - 1].RoomItems[i].pos_y)
				// valid = false;
		// }

		if (valid) {

			int INumber = rand() % (AvailableItems.size());
			Item tmp = AvailableItems[INumber];
			tmp.pos_x = pos_x;
			tmp.pos_y = pos_y;
			Rooms[targetRoom].RoomItems.push_back(tmp);
			stop = false;
		}
	}
}

// This function takes a list of items from a file. This allows the program to take a specified list of items.
// Each item from the file has a name, an attack stat, a defense stat, a health stat, a strength stat, and a mana stat.
void Dungeon::GetItemsFromFile()
{
	ifstream fin;

	fin.open("ItemFile.txt");
	if (fin.fail())
	{
		cout << "Cannot open file of items";
		return;
	}

	int att;
	int def;
	int he;
	int mana;
	int str;
	string name;
	string Yes;
	while (!fin.eof())
	{
		fin >> name;
		fin >> att;
		fin >> mana;
		fin >> he;
		fin >> def;
		fin >> str;
		fin >> Yes;
		Item I(att, def, he, mana, str, name, Yes);
		AvailableItems.push_back(I);
	}
}

// This function allows the player to use an item.
void Dungeon::useitem(){
	Player.SelectItem();
}

// This function allows a player to pick up an item. It checks to see if the player is at the same position as the item.
// If the player is in the same location as the item, it removes the item from the room and adds it to the player.
void Dungeon::pickupItem() {
	for (int i = 0; i < Rooms[active].RoomItems.size(); i++) {
		if (Rooms[active].RoomItems[i].pos_x == Player.pos_x && Rooms[active].RoomItems[i].pos_y == Player.pos_y){

			Player.PickUpItem(Rooms[active].RoomItems[i]);

			Rooms[active].RoomItems.erase(Rooms[active].RoomItems.begin() + i);
		}


	}

}
// Sam Wynsma's code for this .cpp file ends here.


