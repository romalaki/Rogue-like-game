#pragma once
#include "Classes.h"
#include "Dungeon.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;


	bool checkStr(string s) {
		for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			return false;
			}
		}
		return true;
	}

	int Dungeon::getFloor() {
		return floor;
	}


	void Dungeon::go() {
		cout << "WELCOME" << endl;
		Player* play = new Player;

		while (play->HP > 0 && floor < 6) {
			steps++;

			cout << *play;

			int event = rand() % 100;


			if (event <= 30) {

				fight(play,floor);
				cout << endl;

			}
			else if (event <= 45) {

				cout << "You found glossary. Do you want to open it?(Yes or no)" << endl;
				string ans;
				cin >> ans;
				if (ans == "Yes") {
					Glossary();
				}else{
					cout << "You walked away." << endl;
				}


				Sleep(3000);

			}
			else if (event <= 70) {

				shop(play);
				cout << endl;

				Sleep(3000);

			}
			else if (event <= 90) {

				cout << "You found strange chest, open it?(Yes or no)" << endl;
				string ans;
				cin >> ans;
				if (ans == "Yes") {
					Chest(play);
				}
				else {
					cout << "You walked away." << endl;
				}

			}
			else {
				cout << "You found campfire. Your HP is now restored" << endl;

				try {

					ifstream ifs("HP.txt");
					string strInput;

					if (!ifs)
					{
						throw "Couldnt open file!";
					}

					while (ifs)
					{
						ifs >> strInput;
					}

					if (!checkStr(strInput)) { 
						throw "Wrong information in file!"; 
					}

					play->HP = stoi(strInput);

				}

				catch (const char* error) {
					cerr <<error<<endl;
					if (play->HP < 100) play->HP = 100;			
				}

				cout << *play;
				cout << endl;
				Sleep(3000);

			}


			if (steps == 10) {

				steps = 0;
				floor++;

			}
		}

		if (play->HP > 0) {
			cout << "Win!!";
		}
		else {
			cout << "You lost!";
		}
		delete play;
	}

	void Dungeon::Chest(Player* play) {
		cout << "You tried to open chest and then";
		int event = rand() % 10;
		if (event >= 7) {
			event = rand() % 10;
			cout << " you see strange potion. After drinking it your";
				if (event >= 5) {
					cout << " damage is buffed by 10!" << endl;
					play->Dmg += 10;
				}
				else {
					cout << " HP is buffed by 20!" << endl;
					play->HP += 20;
				}
		}
		else {
			cout << " chest bit you! It was a mimic." << endl;
			play->HP -= 10;
		}
	}


	void Dungeon::Glossary() {
		Skeleton sk(floor);
		Zombie zb(floor);
		ZombieSkeleton zs(floor);
		cout << "Skeleton have 10% chance to avoid your atacks. " << sk;
		cout << "Zombie regenerates his HP by attack/2. " << zb;
		cout << "ZombieSkeleton have both abilities. " << zs;
		cout << "Glossary ends here." << endl;
	}

	void Dungeon::shop(Player* play) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		while (true) {

			cout << endl;
			cout << "Shop:" << endl;
			cout << "1:Weapon" << endl;
			cout << "2:Armor" << endl;
			cout << "3:Go away" << endl;
			cout << "You have " << play->Coins << " coins" << endl;
			try {
				vector<type>armor{ Wood,Iron,Gold,Diamond };
				vector<string>armor_str{ "Wood","Iron","Gold","Dimond" };
				string choice_str;
				cin >> choice_str;
				cout << endl;

				if (!checkStr(choice_str)) {
					throw "You typed wrond integer!";
				}
				int choice = stoi(choice_str);

				if (choice == 1) {

					for (int i = 0; i < armor.size(); i++) {

						if (armor[i] == Wood) {
							SetConsoleTextAttribute(hConsole, 8);

						}else if (armor[i] == Iron) {
							SetConsoleTextAttribute(hConsole, 15);

						}
						else if(armor[i] == Gold) {
							SetConsoleTextAttribute(hConsole, 14);

						}
						else {
							SetConsoleTextAttribute(hConsole, 11);

						}
						cout << i + 1 << ". I suggest " << armor_str[i] << " sword, the price is " << armor[i] << " and damage is " << armor[i] / 2 << endl;

					}
					SetConsoleTextAttribute(hConsole, 15);

					cin >> choice_str;

					if (!checkStr(choice_str)) {
						throw invalid_argument("You typed wrond integer, invalid argument!");
					}
					choice = stoi(choice_str);

					if (choice > 0 && choice <= 4 && play->getCoins() >= armor[choice - 1]) {

						play->Buy(armor[choice - 1]);

						play->newWeapon(armor[choice - 1]);

						cout << "Congrats, you upgraded your sword!" << endl;

					}
					else {
						cout << "Cant do it!" << endl;
					}


				}
				else if (choice == 2) {


					for (int i = 0; i < armor.size(); i++) {
						if (armor[i] == Wood) {
							SetConsoleTextAttribute(hConsole, 8);

						}
						else if (armor[i] == Iron) {
							SetConsoleTextAttribute(hConsole, 15);

						}
						else if (armor[i] == Gold) {
							SetConsoleTextAttribute(hConsole, 14);

						}
						else {
							SetConsoleTextAttribute(hConsole, 11);

						}
						cout << i + 1 << ". I suggest " << armor_str[i] << " armor, the price and buff to your HP will be " << armor[i] << endl;
					}
					SetConsoleTextAttribute(hConsole, 15);

					cin >> choice_str;
					if (!checkStr(choice_str)) {
						throw "You typed wrond integer!";
					}
					choice = stoi(choice_str);

					if (choice > 0 && choice <= 4 && play->getCoins() >= armor[choice - 1]) {

						play->Buy(armor[choice - 1]);

						play->newArmor(armor[choice - 1]);

						cout << "Congrats, you upgraded your armor!" << endl;

					}
					else {
						cout << "Cant do it!" << endl;
					}
				}

				else if (choice == 3) {

					cout << "Bye" << endl;
					break;

				}
				else {

					cout << "Repeat please?" << endl;

				}
			}
			catch (const char* error) {
				cerr << error<<endl;
			}
			catch (exception& ex) {
				cerr << ex.what() << endl;
			}
		}
	}

	void Dungeon::fight(Player* play,int dif) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		int percent = rand() % 3;


		Entity* sk = nullptr;

		cout << endl;

		if (percent == 0) {

			cout << "You got attacked by skeleton!" << endl;
			sk = new Skeleton(dif);

		}

		else if (percent == 1) {

			cout << "You got attacked by zombie!" << endl;
			sk = new Zombie(dif);

		}

		else {

			cout << "You got attacked by zombie-skeleton!" << endl;
			sk = new ZombieSkeleton(dif);

		}

		ofstream ofs("List.txt", ios::app);
		if (!ofs) {
			cout << "Error opening file!";
		}
		else {
			ofs << *sk;
		}
		cout << *sk;



		while (play->getHP() > 0) {

			cout << "What do you do?" << endl;
			cout << "1)Fight" << endl;
			cout << "2)Run away!" << endl;
			cout << "100)To open cheat menu!" << endl;

			string choice;
			cin >> choice;


			int dmg;

			cout << endl;

			if (choice == "2") {

				dmg = sk->attack();
				play->takeDmg(dmg);
				SetConsoleTextAttribute(hConsole, 12);
				cout << "You got hit by " << dmg << " damage, and ran away" << endl;
				SetConsoleTextAttribute(hConsole, 15);
				break;

			}
			else if (choice == "1") {
				SetConsoleTextAttribute(hConsole, 12);
				dmg = play->attack();
				cout << "You deal: " << dmg << endl;


				sk->takeDmg(dmg);


				if (sk->getHP() <= 0) {

					play->addCoins(sk->getCoins());
					SetConsoleTextAttribute(hConsole, 15);
					break;

				}
			}
			else if (choice == "100") {
				cout << "Type 1 to recreate enemy, 2 to choose from template and 3 to show all operators" << endl;
				cin >> choice;
				if (choice == "1") {
					cin >> *sk;
					cout << *sk;
				}
				else if (choice == "2") {
					Template(*sk);
					cout << *sk;
				}
				else if (choice == "3") {
					cout << "Stats of your enemy will not be changed" << endl;
					Entity* temp = new Zombie;
					cout << *temp;
					cout << "\n+=2\n";
					*temp += 2;
					cout << *temp;
					Entity* temp2 = new Zombie;
					cout << "\n+="<<*temp2<<endl;
					*temp += temp2;
					cout << *temp;
					cout << "\n=" << *temp2;
					*temp = temp2;
					cout << "\nnew stats:" << *temp2;
					cout << "\nare they equal now?(==) ";
					cout<<(*temp == temp2)<<endl;
					cout << "\nThats all!"<< endl;
					delete temp;
					delete temp2;
				}
				else {
					cout << "Something went wrong" << endl;
				}
			}
			else {
				cout << "You did nothing!";
			}


			dmg = sk->attack();


			play->takeDmg(dmg);

			SetConsoleTextAttribute(hConsole, 12);
			cout << "You got hit by: " << dmg << endl;
			SetConsoleTextAttribute(hConsole, 10);
			cout << "Enemy HP: " << sk->getHP() << endl;
			cout << "Your HP: " << play->getHP() << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << endl;


		}
		delete sk;
		Sleep(3000);
	}

	void Dungeon::Template(Entity& ent) {
		Entitys a;
		auto i = a.begin();
		int c = 0;
		while (i!=a.end()) {
			i->setStat(c, c, c);
			cout<<c<<")" << **i;
			c++;
			++i;
		}
		string choice;
		cin >> choice;
		try {
			if (!checkStr(choice)) {
				throw "Incorrect answer!";
			}
			int ch = stoi(choice);
			if (ch < 0 || ch>20)throw "Incorrect answer!";
			ent.setStat(ch,ch,ch);
		}
		catch (const char* err) {
			cerr << err;
		}
	}

