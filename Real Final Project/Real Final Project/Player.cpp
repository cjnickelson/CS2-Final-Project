#include"Player.h"
#include<iostream>
#include<string>
#include<fstream>

Player::Player(string playername, int j)
{
	name = playername;
	string filename = playername + ".txt";

	ifstream file;

	file.open(filename);

	gamesPlayed = 0, highScore = 0, avgScore = 0;
	scores.push_back(0);
	
	if (!file)
	{
		if (j == 2)
			cout << "Previous data could not be found. A new account has been created." << endl;
	}
	else if (j == 1)
	{
		while (file)
		{
			cout << "Name is already used. Please re-enter" << endl;
			file.close();
			cin >> name;
			string filename = name + ".txt";
			file.open(filename);
		}
	}
	else
		{
		string nameIgnore;
		getline(file, nameIgnore);
		file >> gamesPlayed;
		file.ignore();
		if (gamesPlayed == 0)
		{
			int storage;
			file>>storage;
			file.ignore();
			scores.push_back(0);
		}
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
			s.slots[i] = slot;
			file.ignore();
		}
		for (int i = 0; i < 13; i++)
		{
			file >> s.used[i];
		}
	}
	
}

void Player::saveGame()
{
	s.slots[15] = s.slots[13] + s.slots[14];
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
	if (gamesPlayed == 0)
		file << 0<<endl;
	else {
		file << scores[0];
		for (int i = 1; i < scores.size(); i++)
		{
			file << " " << scores[i];
		}
		file << endl;
	}
	for (int i = 0; i < 16; i++)
	{
		file << s.slots[i] << endl;
	}
	for (int i = 0; i < 13; i++)
	{
		file << s.used[i] << " ";
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

void Player:: incrementGamesPlayed()
{
	gamesPlayed++;
}

void Player::addFinalScore(int finalScore)
{
	scores.push_back(finalScore);
}