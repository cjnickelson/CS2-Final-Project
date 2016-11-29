#include<iostream>
#include"Scorecard.h"

void addDie(Dice*, vector<Dice*>&);

using namespace std;

int main()
{
	vector<Dice*> d;
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
	for (int i = 0; i < 5; i++)
	{
		(*d.at(i)).roll();
		cout << (*(d.at(i))).getValue() << " ";
	}
	cout << endl;
	Scorecard s;
	s.setTwos(d);
	cout << s.getTwos();
}

void addDie(Dice* die, vector<Dice*>& d)
{
	Dice* b = new Dice(die);
	d.push_back(b);
}