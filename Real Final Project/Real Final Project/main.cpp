#include<iostream>
#include"Scorecard.h"

void addDie(Dice*, vector<Dice*>&);
void newRoll(vector<Dice*>&, int);

using namespace std;

int main()
{
	srand(time(NULL));
	for (int turns = 1; turns <= 13; turns++)
	{
		int rolls = 0, kept = 0;
		
		vector<Dice*> d;
		newRoll(d, kept);
		cin >> kept;
		newRoll(d, kept);
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

// Problem: it's appending the new dice values, old vector<Dice*> remains the same
void newRoll(vector<Dice*>& d, int kept)
{
	for (int i = kept; i < 5; i++)
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