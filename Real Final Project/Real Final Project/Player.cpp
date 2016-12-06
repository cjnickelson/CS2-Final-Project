#include"Player.h"
#include<iostream>
#include<string>
#include<fstream>

Player::Player(string playername, int j)
{
	string filename = playername + ".txt";
	fstream file;
	file.open(filename);
	
	/*
	if (!file)
	{
		if (j == 2)
			cout << "Your data could not be found." << endl;
		return;
	}
	else
	{
		string nameIgnore;
		getline(file, nameIgnore);
		file >> gamesPlayed;
		file.ignore();
		for (int i = 0; i < gamesPlayed; i++)
		{
			int temp;
			file >> temp;
			scores.push_back(temp);
		}
		for (int i = 0; i < 16; i++)
		{
			int slot;
			file >> slot;
			s.slots[i] == slot;
			file.ignore();
		}
	}
	*/
}

void Player::saveGame()
{
	string filename = name + ".txt";
	ofstream file;
	file.open(filename);
	if (!file)
	{
		cout << "Could not find file" << endl;
		return;
	}
	file << name << endl;
	file << gamesPlayed << endl;
	file << scores.at(0);
	for (int i = 1; i < scores.size(); i++)
	{
		file << " " << scores.at(i);
	}
	file << endl;
	for (int i = 0; i < 16; i++)
	{
		file << s.slots[i] << endl;
	}
	file.close();
}

void Player::getStats()
{
	cout << "Statistics for player: " << name << ": " << endl;
	cout << "Games played: " << gamesPlayed << endl;
	cout << "High score: " << getHighScore() << endl;
	cout << "Average Score: " << getAVGscore() << endl;
}

int Player::getGamesPlayed()
{
	return gamesPlayed;
}

vector<int> Player:: getScores()
{
	return scores;
}

string Player::getName()
{
	return name;
}

int Player::getHighScore()
{
	int high = scores.at(0);
	for (int i = 1; i < scores.size(); i++)
	{
		if (scores.at(i) > high)
			high = scores.at(0);
	}
	return high;
}

double Player::getAVGscore()
{
	int total = 0;
	for (int i = 0; i < scores.size(); i++)
	{
		total += scores.at(i);
	}
	double avg = total / scores.size();
	return avg;
}