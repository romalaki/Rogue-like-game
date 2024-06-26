#pragma once

class Player;

class Dungeon{
	public:
	void go();
	int getFloor();

	private:
	void shop(Player* play);
	void Chest(Player* play);
	void fight(Player* pl,int dif);
	void Glossary();
	void Template(class Entity& sk);

	int floor=0;
	int steps=0;
};