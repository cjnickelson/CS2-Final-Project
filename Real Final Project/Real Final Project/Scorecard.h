#pragma once

#include"Dice.h"
#include<vector>

using namespace std;

class Scorecard
{
	int ones = 0, twos = 0, threes = 0, fours = 0, fives = 0, sixes = 0;
	int threeOfaKind = 0, fourOfaKind = 0, fullHouse = 0, smallStraight = 0, largeStraight = 0, Yahtzee = 0, chance = 0;
	int upperScore = 0;
	int lowerScore = 0;
public:
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
