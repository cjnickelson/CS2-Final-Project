#include"Dice.h"
#include"Game.h"

Game::Game()
{

}

// this functions appends a die to a vector
void Game::addDie(Dice* die, vector<Dice*>& d)
{
	// creates a copy of the die which is passed in and pushes its pointer to the back of the array of dice pointers
	Dice* b = new Dice(die);
	d.push_back(b);
}
// this function replaces a die which is already in the vector of dice
void Game::replaceDie(Dice* die, vector<Dice*>& d, int i)
{
	// becasue we are introducing a new die, we want to delete the old one to avoid memory leakage
	delete d[i];
	// creates a copy of the die which is passed in as an argument
	Dice* b = new Dice(die);
	// gives this pointer to the vector of dice pointers in the place we deleted before
	d[i] = b;
}

// this is the first roll of a player on any given turn
void Game::firstRoll(vector<Dice*>& d, int& rolls)
{
	rolls++;
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
void Game::newRoll(vector<Dice*>& d, int kept, int& rolls)
{
	// if the rolls variable has been set to three (the user wants to keep all of the dice he/she has now), exit the function
	if (rolls == 3)
		return;
	rolls++;
	if (rolls == 2)
	{
		cout << "Second roll:" << endl;
	}
	else cout << "Final roll:" << endl;
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
void Game:: chooseKept(vector<Dice*>& d, int& kept, int& rolls)
{
	// skips the choosing stage, as the player has already settled on all 5 dice
	if (rolls == 3)
		return;
	// display the players options to the screen
	cout << "Options:" << endl << "Add dice to those already kept:    1" << endl << "Roll same dice as previous roll:   2" << endl
		<< "Change kept dice (pick new dice):  3" << endl << "Reroll all 5 dice:                 4"
		<< endl << "Keep all dice:                     5" << endl;
	// initialize choice to 0, and create an int called value, to hold the player's selections of dice
	int choice = 0, value;
	// copy the values of the dice into a new vector of ints to prevent cheating
	vector<int> copy;
	// copy may still have values from previous turns, so we can't simply use push_back. We must use the basic = operator for index values less than its size
	for (int i = 0; i < copy.size(); i++)
	{
		copy[i] = (*(d[i])).getValue();
	}
	// for empty slots up to 5, push_back can be used
	for (int i = copy.size(); i<5; i++)
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
			cout << endl << "Final roll:" << endl;
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
							break;
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