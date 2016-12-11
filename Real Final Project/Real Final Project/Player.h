#pragma once
#include"Scorecard.h"
#include<iostream>
#include<fstream>

using namespace std;

// player class contains a scorecard, as well as this players statistics stored in a vector of their previous scores
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
	void incrementGamesPlayed();
	void addFinalScore(int);
	void clearGame();
};