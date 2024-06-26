#pragma once
#include "Classes.h"

using namespace std;

void Entity::setStat(int f, int s, int t) {
	HP = f;
	Dmg = s;
	Coins = t;
}


type randtool(int dificulty) {

		int r = rand() % 100;

		if (r <= 25) {
			return None;
		}
		else if (r <= 75 && dificulty >= 2) {
			return Iron;
		}

		else if (r <= 90 && dificulty >= 3) {
			return Gold;
		}

		else if (r > 90 && dificulty >= 4) {
			return Diamond;
		}

		else {
			return Wood;
		}

}


	Player::Player() {
		HP = 100;
		Dmg = 10;
		Coins = 0;
	}

	int Player::getHP()  {
		return HP;
	}

	int Player::getDMG()  {
		return Dmg;
	}


	int Player::attack() {
		return Dmg + rand() % 5 - 2;
	}


	void Player::takeDmg(int dmg) {
		HP -= dmg;
	}

	void Player::newArmor(int buffHP) {
		HP += buffHP;
	}


	void Player::newWeapon(int newDmg) {
		Dmg += newDmg / 2;
	}


	int Player::getCoins()  {
		return Coins;
	}


	void Player::addCoins(int coin) {
		Coins += coin;
	}


	void Player::Buy(int price) {
		Coins -= price;
	}


	ostream& operator<<(ostream& out, const Entity& ent) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		out << "Enemy stats: ";
		SetConsoleTextAttribute(hConsole, 12);
		out << ent.Dmg << " Dmg, ";
		SetConsoleTextAttribute(hConsole, 10);
		out << ent.HP << " HP, ";
		SetConsoleTextAttribute(hConsole, 14);
		out << ent.Coins << " Coins." << endl;
		SetConsoleTextAttribute(hConsole, 15);
		return out;
	}

	ostream& operator<<(ostream& out, const Player& ent) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		out << "Your stats: ";
		SetConsoleTextAttribute(hConsole, 12); 
		out << ent.Dmg << " Dmg, ";
		SetConsoleTextAttribute(hConsole, 10);
		out << ent.HP << " HP, ";
		SetConsoleTextAttribute(hConsole, 14);
		out<< ent.Coins << " Coins." << endl;
		SetConsoleTextAttribute(hConsole, 15);
		return out;
	}

	istream& operator>>(istream& in, Entity& ent) {
		in >> ent.Dmg;
		in >> ent.HP;
		in >> ent.Coins;
		return in;
	}

	void Entity::operator+=(const Entity* ent) {
		HP += ent->HP;
		Dmg += ent->Dmg;
		Coins += ent->Coins;

	}

	void Entity::operator+=(int n) {
		HP += n;
		Dmg += n;
		Coins += n;

	}

	void Entity::operator=(const Entity* ent) {
		HP = ent->HP;
		Dmg = ent->Dmg;
		Coins = ent->Coins;
	}

	bool Entity::operator==(const Entity* ent) {
		return HP == ent->HP && Dmg == ent->Dmg && Coins == ent->Coins;
	}

	
	Skeleton::Skeleton(int dificulty) {

		sword = randtool(dificulty);
		armor = randtool(dificulty);

		Coins = 10 + (sword + armor) / 2;

		Dmg = 7 + sword / 2;

		HP = 5 + armor;
	}

	int Skeleton::getHP()  {
		return HP;
	}

	int Skeleton::getDMG()  {
		return Dmg;
	}

	int Skeleton::attack() {
		return Dmg + rand() % 4 - 2;
	}

	void Skeleton::takeDmg(int dmg) {
		int evasion = rand() % 100;

		if (evasion < 90) {
			HP -= dmg;
			if (HP <= 0) {
				cout << "You won, your price: " << Coins << " coins" << endl;
			}
		}else {
			cout << "Enemy evaded your attack!" << endl;
		}
	}

	int Skeleton::getCoins()  {
		return Coins;
	}



	Zombie::Zombie(int dificulty) {
		sword = randtool(dificulty);
		armor = randtool(dificulty);

		Coins = 15 + (sword + armor) / 2;

		Dmg = 5 + sword / 2;

		HP = 15 + armor;
	}

	int Zombie::getHP()  {
		return HP;
	}

	int Zombie::getDMG()  {
		return Dmg;
	}

	void Zombie::takeDmg(int dmg) {
		HP -= dmg;

		if (HP <= 0) {

			cout << "You won, your price: " << Coins << " coins" << endl;

		}
	}

	int Zombie::attack() {

		int dealDmg = Dmg + rand() % 4 - 2;

		HP += dealDmg / 2;

		return dealDmg;
	}

	int Zombie::getCoins()  {
		return Coins;
	}


	ZombieSkeleton::ZombieSkeleton(int dificulty):Skeleton(dificulty), Zombie(dificulty){
		Coins += 10;
	}

	void ZombieSkeleton::takeDmg(int dmg) {
		Skeleton::takeDmg(dmg);

	}

	int ZombieSkeleton::getCoins()  {
		return Coins;
	}

	int ZombieSkeleton::getHP() {
		return HP;
	}

	int ZombieSkeleton::getDMG() {
		return Dmg;
	}

	int ZombieSkeleton::attack() {
		return Zombie::attack();
	}

