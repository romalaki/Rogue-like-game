#include "Dungeon.h"
#include <iostream>
#include <fstream>

int main()
{
	srand(time(NULL));
	Dungeon game;
	std::ofstream ofs("List.txt");
	if (!ofs) {
		std::cout << "Error opening file!";
	}
	else {
		ofs << "Game started!" << std::endl;
	}
	game.go();
	return 0;
}
