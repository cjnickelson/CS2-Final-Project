
#include"Scorecard.h"
#include<string>
#include"Player.h"
#include"Game.h"

using namespace std;

int main()
{
	// set the seed for random die rolls
	srand(time(NULL));
	// find out from the user whether they are a new or returning player. This will allow us to make sure the user inputs an unused name, lest they get confused for a returner
	cout << "Are you a new or returning player?" << endl;
	cout << "New : 1" << endl << "returner: 2" << endl;
	int player;
	cin >> player;
	// ask the user to enter their name, and get htis name with cin
	cout << "Enter name. " << endl;
	string name;
	cin >> name;
	// construct a player with the given name. This constructor will also ensure that a new player uses a new name and a returner's file is found
	Player p(name,player);
	// set an int turns to 0
	Game g;
	int turns = 0;
	// a game lasts 13 turns, so put the gameplay inside a while loop whose condition is that turns stays below 13
	while (turns<13)
	{
		// create a vector of pointers to dice objects for use in the game
		vector<Dice*> d;
		// initialize two variables, rolls and kept to 0
		int rolls = 0, kept = 0;
		// give the player their first roll
		cout << "First roll:" << endl;
		g.firstRoll(d, rolls);
		cout << endl;
		// call the chooseKept() functin to let the user decide which of the five dice he/she wants to keep
		g.chooseKept(d, kept, rolls);
		cout << endl;
		// do two more rolls, the first time letting the user choose which dice to keep.
		g.newRoll(d, kept, rolls);
		cout << endl;
		g.chooseKept(d, kept, rolls);
		cout << endl;
		g.newRoll(d, kept, rolls);
		// after their third roll, the player's turn is over. score their roll using the scoreRoll() function in scorecard.cpp
		
		p.s.scoreRoll(d);
		// once we have scored the roll, we must delete the vector of five dice to avoid memory leakage
		for (int i = 0; i < 5; i++)
		{
			delete d[i];
		}
		// after they score the roll, show them their new scorecard
		p.s.displayCard();
		cin.ignore();
		// reset the turns int, as we need to start it over to count them
		turns = 0;
		// for each of the 13 categories...
		for (int i = 0; i < 13; i++)
		{
			// if it has been used, increment turns
			if (p.s.getUsed(i) == true)
				turns++;
		}
		// save the player's progress after every turn
		p.saveGame();
	}
	// once the outermost while loop is exited, the game must be over
	// increment the players gamesPlayed
	p.incrementGamesPlayed();
	// create an int finalScore to hold the game's final score
	int finalScore = p.s.getScore();
	// add that final score to the player's vector of game scores
	p.addFinalScore(finalScore);
	// display their score to the screen
	cout << "Your final score is " << finalScore << endl;
	// clear the game, so they may start anew when the program is started again
	p.clearGame();
	// show the player's statistics
	p.getStats();
	// save the game stats
	p.saveGame();
	return 0;

}