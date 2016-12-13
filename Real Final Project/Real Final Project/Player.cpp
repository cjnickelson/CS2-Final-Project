#include"Player.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

// constructor for player includes arguments for their name, as well as an integer. This int represents their position as either a returning player or a new one, which affects the way we recall files
Player::Player(string playername, int j)
{
	// sets the member variable name to the specified name
	name = playername;
	// creates a text file fo this name
	string filename = playername + ".txt";
	// creates an input file stream for possible data retrieval
	ifstream file;
	// attempts to open this file
	file.open(filename);
	// initializes these statistics to 0 for each new player (will be overwritten if it turns out to be a returning player)
	gamesPlayed = 0;
	scores.push_back(0);
	// if the file fails, we must distinguish whether the player thought he was a returner. 
	if (!file)
	{
		// if this is the case, we alert them that their file has not been found, and a new one will be created for them
		if (j == 2)
			cout << "Previous data could not be found. A new account will be created." << endl;
		// ohterwise we proceed as normal, creating a new file
	}
	// if the file does open, we also must distinguish whether the player said they were new or returning
	else if (j == 1)
	{
		// if they said they were a new player, alert them that this name has already been taken and prompt for new names until an unused one is entered
		while (file)
		{
			cout << "Name is already used. Please re-enter" << endl;
			// close the previously opened file
			file.close();
			// repeat the naming and file opening process
			cin >> name;
			string filename = name + ".txt";
			file.open(filename);
		}
	}
	// finally, if a returning player's file is found, we retrieve the data from it
	else
	{
		// create a string to store the name which appears at the top of the file
		string nameIgnore;
		// get and ignore that name
		getline(file, nameIgnore);
		// the next line has stored how many games this player has played
		file >> gamesPlayed;
		// account for the newline character
		file.ignore();
		// if they have no games in their file (saved in the middle of their first one), we ignore the 0 that is automatically placed there
		if (gamesPlayed == 0)
		{
			int storage;
			file>>storage;
			file.ignore();
		}
		// otherwise, we take the first value present and store it to the first place in the scores vector
		else file >> scores[0];
		// get the rest of the final scores from the file and append them to the scores vector
		for (int i = 1; i < gamesPlayed; i++)
		{
			int temp;
			file >> temp;
			scores.push_back(temp);
		}
		// next, retrieve any data from a game that was saved in progress
		for (int i = 0; i < 16; i++)
		{
			// create an int to temporarily hold the file value
			int slot;
			file >> slot;
			// give that value to the slot array that holds the scores for each Yahtzee category
			s.setSlots(i,slot);
			file.ignore();
		}
		// lastly, pull in from the file all of the data on which categroies have already been used, stored in a used[] array
		for (int i = 0; i < 13; i++)
		{
			bool b;
			file >> b;
			s.setUsed(i,b);
		}
		s.displayCard();
	}
	file.close();
}

// save game function saves a game (finished or unfinished) to the player's file
void Player::saveGame()
{
	// slots[15] is the game's total score, the sum of the upper score (slots[13]) and the lower score (slots[14]). A 35 point bonus is given if a total of 63 or higher is found in the upper score
	 int score = s.getSlots(13) + s.getSlots(14)+(s.getSlots(13) >= 63 ? 35 : 0);
	 s.setSlots(15, score);
	// repeat file naming and opening from above
	string filename = name + ".txt";
	ofstream file;
	file.open(filename);
	// if the file cannot be opened, tell the user and exit
	if (!file)
	{
		cout << "Could not find file" << endl;
		return;
	}
	// otherwise, print to the file the name of the player, their number of gamnes played, and the first value in their vector of final scores
	file << name << endl;
	file << gamesPlayed << endl;
	file << scores[0];
	// then, on the same line as their first final score, print the rest of their vector of scores separated by a space
	for (int i = 1; i < scores.size(); i++)
	{
		file << " " << scores[i];
	}
	file << endl;
	
	// print the contents of each category into the file on their own lines
	for (int i = 0; i < 16; i++)
	{
		file << s.getSlots(i) << endl;
	}
	// print the status (used/unused) for each of the categories excluding the totals
	for (int i = 0; i < 13; i++)
	{
		file << s.getUsed(i) << " ";
	}
	// close the file when we are done
	file.close();
}

// this function displays the player statistics based on their number of games played and their vector of scores, and calling the required functions
void Player::getStats()
{
	cout << "Statistics for player: " << name << endl;
	cout << "Games played: " << gamesPlayed << endl;
	cout << "High score: " << getHighScore() << endl;
	cout << "Low score: " << getLowScore() << endl;
	cout << "Average Score: " << fixed << setprecision(2) << getAVGscore() << endl;
}

// staandard get function for games played
int Player::getGamesPlayed()
{
	return gamesPlayed;
}

// returns a the vector of scores created for the player
vector<int> Player:: getScores()
{
	return scores;
}

// returns the player's name
string Player::getName()
{
	return name;
}

// determines and returns the highest value within the player's vector of scores
int Player::getHighScore()
{
	// sets the high value to the first one
	int high = scores[0];
	// for each ensuing value, if it is higher than the current high score, the high score is set equal to the new one
	for (int i = 1; i < scores.size(); i++)
	{
		if (scores[i] > high)
			high = scores[i];
	}
	// returns the highest value found
	return high;
}
// same function as getHighScore(), but searches for the lowest one
int Player::getLowScore()
{
	int low = scores[0];
	for (int i = 1; i < scores.size(); i++)
	{
		if (scores[i] < low)
			low = scores[i];
	}
	return low;
}

// determines and returns the player's average score based on their number of games played and vector of scores
double Player::getAVGscore()
{
	// initializes a counter variable to 0
	double total = 0;
	// for each value in the vector of scores, total is increased by the contents
	for (int i = 0; i < scores.size(); i++)
	{
		total += scores[i];
	}
	// the average is calculated by taking the total from above and dividing by the number of games played.
	double avg = total / scores.size();
	// returns this average
	return avg;
}
// increments the gamesPlayed variable, as it is a private variable
void Player:: incrementGamesPlayed()
{
	gamesPlayed++;
}
// function adds a final score of a finished game to the vector of scores
void Player::addFinalScore(int finalScore)
{
	// if the vector has no values, it has been given the number 0 to avoid file input errors. Thus we cannot simply append the new value
	if (scores[0] == 0)
		scores[0] = finalScore;
	// otherwise, append the value to the vector
	else
		scores.push_back(finalScore);
}
// used when a game has been finished, clears all the values from the category totals and the used[] array to start a game from scratch when the program is run by this person again
void Player::clearGame()
{
	for (int i = 0; i < 13; i++)
	{
		s.setSlots(i,0);
		s.setUsed(i,false);
	}
	for (int i = 13; i < 16; i++)
	{
		s.setSlots(i,0);
	}
}