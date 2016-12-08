#include<iostream>
#include"Scorecard.h"
#include<string>
#include"Player.h"

void addDie(Dice*, vector<Dice*>&);
void firstRoll(vector<Dice*>&, int&);
void replaceDie(Dice*, vector<Dice*>&, int);
void newRoll(vector<Dice*>&, int, int&);
void chooseKept(vector < Dice*>& , int&, int&);
void scoreRoll(vector<Dice*>);

using namespace std;

int main()
{
	srand(time(NULL));
	cout << "Are you a new or returning player?" << endl;
	cout << "New : 1" << endl << "returner: 2" << endl;
	int player;
	cin >> player;
	cout << "Enter name. " << endl;
	string name;
	cin >> name;
	Player p(name,player);

	for (int turns = 1; turns <= 3; turns++)
	{
		int rolls = 0, kept = 0;
		
		vector<Dice*> d;
		firstRoll(d, rolls);
		cout << endl;
		chooseKept(d, kept, rolls);
		cout << endl;
		newRoll(d, kept, rolls);
		cout << endl;
		chooseKept(d, kept, rolls);
		cout << endl;
		newRoll(d, kept, rolls);
		//scoreRoll(d);
		if (turns == 1)
		{
			p.s.set3OAK(d);
			cout << p.s.get3OAK() << endl;
		}
		else if (turns == 2)
		{
			p.s.set4OAK(d);
			cout << p.s.get4OAK() << endl;
		}
		else
		{
			p.s.setFullHouse(d);
			cout << p.s.getFullHouse() << endl;
		}
		cin.ignore();
	}
	p.saveGame();
}

void addDie(Dice* die, vector<Dice*>& d)
{
	Dice* b = new Dice(die);
	d.push_back(b);
}

void replaceDie(Dice* die, vector<Dice*>& d, int i)
{
	Dice* b = new Dice(die);
	d[i] = b;
}

// Problem: it's appending the new dice values, old vector<Dice*> remains the same
void firstRoll(vector<Dice*>& d, int& rolls)
{
	for (int i = 0; i < 5; i++)
	{
		Dice* temp = new Dice;
		(*temp).roll();
		addDie(temp, d);
		delete temp;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << (*(d.at(i))).getValue() << " ";
	}
	cout << endl;
}

void newRoll(vector<Dice*>& d, int kept, int& rolls)
{
	if (rolls == 3)
		return;
	for (int i = kept; i < 5; i++)
	{
		Dice* temp = new Dice;
		(*temp).roll();
		replaceDie(temp, d, i);
		delete temp;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << (*(d.at(i))).getValue() << " ";
	}
	cout << endl;
}

void chooseKept(vector<Dice*>& d, int& kept, int& rolls)
{
	if (rolls == 3)
		return;
	cout << "Options:" << endl << "Add dice to those already kept:    1" <<endl<< "Roll same dice as previous roll:   2" << endl 
		<< "Change kept dice (pick new dice):  3" << endl << "Reroll all 5 dice:                 4" 
		<< endl << "Keep all dice:                     5" << endl;
	int choice,value;
	cin >> choice;
	// copy the values of the dice into a new vector of ints to prevent cheating
	vector<int> copy;
	for (int i = 0; i < 5; i++)
	{
		copy.push_back((*(d.at(i))).getValue());
	}
	switch (choice)
	{
	case 1:
		int number;
		cout << "How many new dice?" << endl;
		cin >> number;
		cout << "Enter values of desired dice" << endl;
		while (number < 0 || (kept+number)>5)
		{
			cout << "Invalid. Reenter." << endl;
			cin >> number;
		}
		for (int i = kept; i < kept + number; i++)
		{
			bool found = false;
			while (!found) {
				cin >> value;
				for (int i = 0; i < copy.size(); i++)
				{
					if (value == copy.at(i))
					{
						found = true;
						copy.erase(copy.begin() + i);
						break;
					}
				}
				if (found)
				{
					Dice* a = new Dice(value);
					replaceDie(a, d, i);
					delete a;
				}
				else
					cout << "Die not found in roll, reenter" << endl;
			}
		}
		kept += number;
		break;
	case 4:
		kept = 0;
		break;
	case 5:
		rolls = 3;
		break;
	case 3:
		cout << "How many do you want to keep?" << endl;
		cin >> kept;
		while (kept < 0 || kept>5)
		{
			cout << "Invalid. Reenter" << endl;
			cin >> kept;
		}
		cout << "Enter values of desired dice" << endl;
		for (int i = 0; i < kept; i++)
		{
			bool found = false;
			while (!found) {
				cin >> value;
				for (int i = 0; i < copy.size(); i++)
				{
					if (value == copy.at(i))
					{
						found = true;
						copy.erase(copy.begin() + i);
					}
				}
				if (found)
				{
					Dice* a = new Dice(value);
					replaceDie(a, d, i);
					delete a;
				}
				else
					cout << "Die not found in roll, reenter" << endl;
			}
		}
		break;
	case 2:
		break;
	default:
		cout << "Invalid entry, reenter" << endl;
	}
}

void scoreRoll(vector<Dice*> d)
{

}