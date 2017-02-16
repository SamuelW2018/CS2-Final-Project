#include "MainHeader.h"

int main() {

	srand(time(NULL));

	bool stop = false;

	Dungeon world;

	while (!stop) {
		world.renderFrame();

		char input = getch();

		switch (input) {
		case 'd':world.movePlayer(0); break;
		case 'w':world.movePlayer(1); break;
		case 'a':world.movePlayer(2); break;
		case 's':world.movePlayer(3); break;
		case 'i':world.useitem(); break;
		case 'p':world.pickupItem(); break;
		case 'q':world.Player_Attack(); break;
		case 'e':world.Player_Defend(); break;
		}

	}

}

void printFrame(vector<vector<char>> map) {
	COORD spot = {0,0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), spot);
	for (int i = 0; i < room_DimX_Max; i++) {
		for (int j = 0; j < room_DimY_Max; j++) {
			cout << " ";
		}
		cout << endl;
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), spot);
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[1].size(); j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}