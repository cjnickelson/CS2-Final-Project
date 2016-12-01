#include<iostream>
#include"Scorecard.h"

void addDie(Dice*, vector<Dice*>&);
void firstRoll(vector<Dice*>&, int&);
void replaceDie(Dice*, vector<Dice*>&, int);
void newRoll(vector<Dice*>&, int, int&);
void chooseKept(vector < Dice*>& , int&, int&);

using namespace std;

int main()
{
	srand(time(NULL));
	for (int turns = 1; turns <= 1; turns++)
	{
		int rolls = 0, kept = 0;
		
		vector<Dice*> d;
		firstRoll(d, rolls);
		chooseKept(d, kept, rolls);
		newRoll(d, kept, rolls);
		chooseKept(d, kept, rolls);
		newRoll(d, kept, rolls);
		Scorecard s;
		s.setTwos(d);
		cout << s.getTwos()<<endl;
		cin.ignore();
	}
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
	cout << "Options:" << endl << "Add dice to those already kept: 1" << endl << "Reroll all 5 dice: 2" << endl << "Keep all dice: 3" << endl << "Change kept dice (pick new dice): 4" << endl;
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
		while (number < 0 || number>5)
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
	case 2:
		kept = 0;
		break;
	case 3:
		rolls = 3;
		break;
	case 4:
		cout << "How many do you want to keep?" << endl;
		cin >> kept;
		while (kept < 0 || kept>5)
		{
			cout << "Invalid. Reenter" << endl;
			cin >> kept;
		}
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
	default:
		cout << "Invalid entry, reenter" << endl;
	}
}