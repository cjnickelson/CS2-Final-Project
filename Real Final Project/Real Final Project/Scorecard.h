#pragma once

#include"Dice.h"
#include<vector>

using namespace std;

class Scorecard
{
public:
	int slots[16];
public:
	Scorecard();
	int getOnes();
	void setOnes(vector<Dice*>);
	int getTwos();
	void setTwos(vector<Dice*>);
	int getThrees();
	void setThrees(vector<Dice*>);
	int getFours();
	void setFours(vector<Dice*>);
	int getFives();
	void setFives(vector<Dice*>);
	int getSixes();
	void setSixes(vector<Dice*>);
	int get3OAK();
	void set3OAKs(vector<Dice*>);
	int get4OAK();
	void set4OAK(vector<Dice*>);
	int getFullHouse();
	void setFullHouse(vector<Dice*>);
	int getSStraight();
	void setSStraight(vector<Dice*>);
	int getLStraight();
	void setLStraight(vector<Dice*>);
	int getYahtzee();
	void setYahtzee(vector<Dice*>);
	int getChance();
	void setChance(vector<Dice*>);
	int getUpperScore();
	int getLowerScore();
	int getScore();
};
