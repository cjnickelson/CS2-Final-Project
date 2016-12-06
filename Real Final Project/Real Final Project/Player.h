#pragma once
#include"Scorecard.h"
#include<iostream>
#include<fstream>

using namespace std;

class Player
{
	string name;
	int gamesPlayed;
	int highScore;
	double avgScore;
	vector<int> scores;
public:
	Scorecard s;
	Player(string, int);

	void saveGame();
	void getStats();
	int getGamesPlayed();
	vector<int> getScores();
	string getName();
	int getHighScore();
	double getAVGscore();
};