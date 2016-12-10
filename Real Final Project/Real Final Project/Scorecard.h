#pragma once

#include"Dice.h"
#include<vector>
#include<iostream>

using namespace std;

class Scorecard
{
public:
	int slots[16];
	bool used[16];
public:
	Scorecard();
	void scoreRoll(vector<Dice*>);
	int getOnes();
	void setOnes(vector<Dice*>, bool& b);
	int getTwos();
	void setTwos(vector<Dice*>, bool& b);
	int getThrees();
	void setThrees(vector<Dice*>, bool& b);
	int getFours();
	void setFours(vector<Dice*>, bool& b);
	int getFives();
	void setFives(vector<Dice*>, bool& b);
	int getSixes();
	void setSixes(vector<Dice*>, bool& b);
	int get3OAK();
	void set3OAK(vector<Dice*>, bool& b);
	int get4OAK();
	void set4OAK(vector<Dice*>, bool& b);
	int getFullHouse();
	void setFullHouse(vector<Dice*>, bool& b);
	int getSStraight();
	void setSStraight(vector<Dice*>, bool& b);
	int getLStraight();
	void setLStraight(vector<Dice*>, bool& b);
	int getYahtzee();
	void setYahtzee(vector<Dice*>, bool& b);
	int getChance();
	void setChance(vector<Dice*>, bool& b);
	int getUpperScore();
	int getLowerScore();
	int getScore();
	void displayCard();
};
