
#include"Scorecard.h"
#include<string>
#include"Player.h"

void addDie(Dice*, vector<Dice*>&);
void firstRoll(vector<Dice*>&, int);
void replaceDie(Dice*, vector<Dice*>&, int);
void newRoll(vector<Dice*>&, int, int);
void chooseKept(vector < Dice*>& , int&, int&);

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
	int turns = 0;
	// a game lasts 13 turns, so put the gameplay inside a while loop whose condition is that turns stays below 13
	while (turns<13)
	{
		// create a vector of pointers to dice objects for use in the game
		vector<Dice*> d;
		// initialize two variables, rolls and kept to 0
		int rolls = 0, kept = 0;
		// give the player their first roll
		firstRoll(d, rolls);
		cout << endl;
		// call the chooseKept() functin to let the user decide which of the five dice he/she wants to keep
		chooseKept(d, kept, rolls);
		cout << endl;
		// do two more rolls, the first time letting the user choose which dice to keep.
		newRoll(d, kept, rolls);
		cout << endl;
		chooseKept(d, kept, rolls);
		cout << endl;
		newRoll(d, kept, rolls);
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
// this functions appends a die to a vector
void addDie(Dice* die, vector<Dice*>& d)
{
	// creates a copy of the die which is passed in and pushes its pointer to the back of the array of dice pointers
	Dice* b = new Dice(die);
	d.push_back(b);
}
// this function replaces a die which is already in the vector of dice
void replaceDie(Dice* die, vector<Dice*>& d, int i)
{
	// becasue we are introducing a new die, we want to delete the old one to avoid memory leakage
	delete d[i];
	// creates a copy of the die which is passed in as an argument
	Dice* b = new Dice(die);
	// gives this pointer to the vector of dice pointers in the place we deleted before
	d[i] = b;
}

// this is the first roll of a player on any given turn
void firstRoll(vector<Dice*>& d, int rolls)
{
	// append 5 pointers to dice objects to d using the addDie() function
	for (int i = 0; i < 5; i++)
	{
		// temporarily create a new Dice object
		Dice* temp = new Dice;
		// randomize that Die
		(*temp).roll();
		// add it to the vector
		addDie(temp, d);
		// delete the temporary object
		delete temp;
	}
	// display the five dice values to the screen
	for (int i = 0; i < 5; i++)
	{
		cout << (*(d[i])).getValue() << " ";
	}
	cout << endl;
}
// this is used for second and third rolls in a turn
void newRoll(vector<Dice*>& d, int kept, int rolls)
{
	// if the rolls variable has been set to three (the user wants to keep all of the dice he/she has now), exit the function
	if (rolls == 3)
		return;
	// otherwise, starting at the value of kept (the number of dice being stored from previous rolls by the player), use the replaceDie() function to switch out values in the vector
	for (int i = kept; i < 5; i++)
	{
	// same process as described above in addDie()
		Dice* temp = new Dice;
		(*temp).roll();
		replaceDie(temp, d, i);
		delete temp;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << (*(d[i])).getValue() << " ";
	}
	cout << endl;
}
// this function lets the user choose the values of those dice that he/she wants to keep
void chooseKept(vector<Dice*>& d, int& kept, int& rolls)
{
	// skips the choosing stage, as the player has already settled on all 5 dice
	if (rolls == 3)
		return;
	// display the players options to the screen
	cout << "Options:" << endl << "Add dice to those already kept:    1" << endl << "Roll same dice as previous roll:   2" << endl
		<< "Change kept dice (pick new dice):  3" << endl << "Reroll all 5 dice:                 4"
		<< endl << "Keep all dice:                     5" << endl;
	// initialize choice to 0, and create an int called value, to hold the player's selections of dice
	int choice=0, value;
	// copy the values of the dice into a new vector of ints to prevent cheating
	vector<int> copy;
	// copy may still have values from previous turns, so we can't simply use push_back. We must use the basic = operator for index values less than its size
	for (int i = 0; i < copy.size(); i++)
	{
		copy[i] = (*(d[i])).getValue();
	}
	// for empty slots up to 5, push_back can be used
	for (int i=copy.size();i<5;i++)
	{
		copy.push_back((*(d[i])).getValue());
	}
	while (choice < 1 || choice>5)
	{
		// get the player's choice
		cin >> choice;
		switch (choice)
		{
		// they've selected 1, add new dice
		case 1:
			// find out how many
			int number;
			cout << "How many new dice?" << endl;
			cin >> number;
			// this cannot be negaitve, and cannot exceed 5, the number of dice in the game
			while (number < 0 || (kept + number)>5)
			{
				cout << "Invalid. Reenter." << endl;
				cin >> number;
			}
			// for each die requested, get the value from the user
			cout << "Enter values of desired dice" << endl;
			for (int i = kept; i < kept + number; i++)
			{
				// initialize a bool to false, indicating that the requested value has not been found
				bool found = false;
				// as long as the value requested by the user cannot be found, continue asking for new values
				while (!found) {
					cin >> value;
					// check to see if the value is found 
					// for each int in the copy vector...
					for (int i = 0; i < copy.size(); i++)
					{
						// check to see if the requested value is equal to that found in the vector
						if (value == copy[i])
						{
							// if it is, we can set found to true
							found = true;
							// we also want to delete that value from the copy vector, so as to not allow the user to keep 4 twos after they rolled 1
							copy.erase(copy.begin() + i);
							// at this point, we can break out of the for loop
							break;
						}
					}
					// if the die has been found, we can go ahead and replace that die on the vector of dice pointers
					if (found)
					{
						Dice* a = new Dice(value);
						replaceDie(a, d, i);
						delete a;
					}
					// if it is not, tell the user that they did not roll this number, or have already kept its die
					else
						cout << "Die not found in roll, reenter" << endl;
				}
			}
			// add the number entered by the user to the kept variable
			kept += number;
			break;
		case 4:
			// they have selected to scrap all previous rolling, so set kept equal to 0. This will essentially reset the vector of dice pointers
			kept = 0;
			break;
		case 5:
			// they have chosen to keep all five dice
			// display the dice to the screen (for benefit of user)
			for (int i = 0; i < 5; i++)
			{
				cout << (*(d[i])).getValue() << " ";
			}
			// set rolls to 3 such that the other roll and score functions will be skipped
			rolls = 3;
			break;
		case 3:
			// they have chosen to reselect die values
			// ask them how many they want to keep
			cout << "How many do you want to keep?" << endl;
			// set the variable kept to that number
			cin >> kept;
			// again, this has to be between 0 and 5
			while (kept < 0 || kept>5)
			{
				cout << "Invalid. Reenter" << endl;
				cin >> kept;
			}
			// process is the same as that described above in case 1
			cout << "Enter values of desired dice" << endl;
			for (int i = 0; i < kept; i++)
			{
				bool found = false;
				while (!found) {
					cin >> value;
					for (int i = 0; i < copy.size(); i++)
					{
						if (value == copy[i])
						{
							found = true;
							copy.erase(copy.begin() + i);
						}
					}
					if (found)
					{
						Dice* a = new Dice(value);
						replaceDie(a, d, i);
						delete a;
					}
					else
						cout << "Die not found in roll, reenter" << endl;
				}
			}
			break;
		case 2:
			// the user has chosen to reroll the same dice that he/she did last turn. So we just break out of the switch statement
			break;
		default:
			// tell the user their entry was invalid
			cout << "Invalid entry, reenter" << endl;
		}
	}
}

