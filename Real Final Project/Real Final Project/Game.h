#pragma once
#include"Player.h"
#include"Scorecard.h"
#include"Dice.h"

class Game
{
public:
	Game();
	void addDie(Dice*, vector<Dice*>&);
	void firstRoll(vector<Dice*>&, int&);
	void replaceDie(Dice*, vector<Dice*>&, int);
	void newRoll(vector<Dice*>&, int, int&);
	void chooseKept(vector < Dice*>&, int&, int&);
};