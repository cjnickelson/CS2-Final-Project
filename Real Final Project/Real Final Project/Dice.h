#pragma once

#include<vector>
#include<ctime>

using namespace std;

class Dice
{
private:
	int value;
public:
	Dice();
	Dice(Dice*);
	Dice(int);
	int getValue();
	void setValue(int);
	bool operator==(int);
	void roll();
};
