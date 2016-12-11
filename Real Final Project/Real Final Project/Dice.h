#pragma once

#include<vector>
#include<ctime>

using namespace std;

// dice class used for rolling and scoring. Overloads == operator for ease of functions
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
