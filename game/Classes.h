#pragma once
#include "Enums.h"
#include <vector>

class Entity{
public:
	virtual int attack() = 0;
	virtual void takeDmg(int dmg) = 0;
	virtual int getCoins() = 0;
	virtual int getHP() = 0;
	virtual int getDMG() = 0;
	void setStat(int f, int s, int t);

	friend ostream& operator<<(ostream& out, const Entity& ent);
	friend istream& operator>>(istream& out, Entity& ent);
	virtual void operator+=(const Entity* ent);
	virtual void operator+=(int n);
	void operator=(const Entity* ent);
	bool operator==(const Entity* ent);
	virtual ~Entity(){};
protected:
	int HP;
	int Dmg;
	int Coins;
};


class Player: public Entity{
public:
	Player();
	int attack() override;
	void takeDmg(int dmg)override;
	int getCoins()override;
	int getHP()override;
	int getDMG()override;
	void newArmor(int buffHP);
	void newWeapon(int newDmg);
	void addCoins(int coin);
	void Buy(int price);

	friend ostream& operator<<(ostream& out, const Player& ent);
	friend class Dungeon;
};


class Zombie : virtual public Entity {
public:
	Zombie(int dif=1);
	int attack() override;
	void takeDmg(int dmg)override;
	int getCoins()override;
    int getHP()override;
	int getDMG()override;
protected:
	type armor;
	type sword;

};


class Skeleton : virtual public Entity {
public:
	Skeleton(int dif);
	int attack() override;
	void takeDmg(int dmg)override;
	int getCoins()override;
	int getHP()override;
	int getDMG()override;

protected:
	type armor;
	type sword;

};

class ZombieSkeleton : public Skeleton,Zombie {
public:
	ZombieSkeleton(int dif);
	int attack() override;
	void takeDmg(int dmg)override;
	int getCoins()override;
	int getHP()override;
	int getDMG()override;

};

class Entitys {
	Zombie m_data[20];
public:
	class ZombieItterator {
	private:
		Zombie* m_ptr;
	public:
		ZombieItterator(Zombie* ent) :m_ptr(ent) {}

		Zombie* operator*() const { return m_ptr; }
		Zombie* operator->() { return m_ptr; }
		Zombie* operator++() { m_ptr++; return m_ptr; }
		Zombie* operator+=(int x) { m_ptr += x; return m_ptr; }
		Zombie* operator+(int x) { auto tmp = m_ptr + x; return tmp; }
		Zombie* operator++(int) { auto tmp = *this; ++(*this); return *tmp; }
		friend bool operator== (const ZombieItterator& a, const ZombieItterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const ZombieItterator& a, const ZombieItterator& b) { return a.m_ptr != b.m_ptr; };
		~ZombieItterator(){};
	};
	ZombieItterator begin() { return ZombieItterator(&m_data[0]); }
	ZombieItterator end() { return ZombieItterator(&m_data[20]); }
};