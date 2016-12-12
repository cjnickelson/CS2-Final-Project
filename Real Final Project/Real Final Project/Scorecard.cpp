#include"Scorecard.h"
#include<iomanip>
#include<string>

// constructs a scorecard with 0 for each of the scores and false for the used status of each category
Scorecard::Scorecard() {
	for (int i = 0; i < 16; i++)
	{
		slots[i] = 0;
		used[i] = false;
	}
}

// standard get and set functions for the arrays slots[] and used[] at a given index i
int Scorecard::getSlots(int i)
{
	return slots[i];
}

void Scorecard::setSlots(int i, int contents)
{
	slots[i] = contents;
}

bool Scorecard::getUsed(int i)
{
	return used[i];
}

void Scorecard::setUsed(int i, bool b)
{
	used[i] = b;
}

// this function is called when a player is done rolling and needs to choose a category for which to apply his/her roll
void Scorecard::scoreRoll(vector<Dice*> d)
{
	// initialize the bool used to be true, such that the while loop will execute at least once
	bool used = true;
	// show the user thier card so they can make an infromed decision
	displayCard();
	// repeat asking the user for a category as long as what they have supplied is already used
	while (used)
	{
		// create decision variables and initialize them to unacceptable values, again so the while loop is guaranteed to execute once
		int choice = 0, choice2 = 0;
		char choice3 = 'q';
		// continue getting a number from the user until they enter something valid
		while (choice != 1 && choice != 2 && choice != 3)
		{
			// ask them if they want to apply their score to the "upper" half of the card or the "lower"
			cout << "What would you like to do?" << endl << "Score roll to upper portion:    1" << endl << "Score roll to lower portion:    2" << endl << "View your scorecard:            3" << endl;
			// get this value
			cin >> choice;
			switch (choice)
			{
				// for the case of upper, we only need now to ask which number. We also give them the option of returning to the previous junction
			case 1:
				cout << "Which number would you like to score to? To go back, choose 7." << endl;
				// continue retrieving values form the user until something valid is entered
				while (choice2 < 1 || choice2>7)
				{
					cin >> choice2;
					// for each number enetered, call the correct scoring function from below. Also, the used variable is passed in by reference, so the while loop will continue to run if each category has been used
					switch (choice2)
					{
					case 1:
						setOnes(d, used); 
						break;
					case 2:
						setTwos(d, used);
						break;
					case 3:
						setThrees(d, used);
						break;
					case 4:
						setFours(d, used);
						break;
					case 5:
						setFives(d, used);
						break;
					case 6:
						setSixes(d, used);
						break;
					case 7:
						choice = 0;
						break;
					default:
						cout << "Invalid entry." << endl;
						break;
					}
				}
				break;
				// in the case of the lower score, we have the choice variable as a char, such that the abbreviations make more sense
			case 2:
				cout << "Which category do you want to score to?" << endl;
				cout << "Three of a Kind: 3" << endl<< "Four of a kind:  4" << endl<< "Full House:      f" << endl<<"Small straight:  s" << endl<< "Large straight:  l" << endl
				<< "Yahtzee:         y" << endl<< "Chance:          c" << endl<< "Go back:         b" << endl;
				while (choice3 != '3'&&choice3 != '4'&&choice3 != 'f'&&choice3 != 's'&&choice3 != 'l'&&choice3 != 'y'&&choice3 != 'c'&&choice3!='b')
				{
					cin >> choice3;
					// for each choice, call the correct scoring function from below, again passing in the used bool
					switch (choice3)
					{
					case '3':
						set3OAK(d,used);
						break;
					case '4':
						set4OAK(d, used);
						break;
					case 'f':
						setFullHouse(d, used);
						break;
					case 's':
						setSStraight(d, used);
						break;
					case 'l':
						setLStraight(d, used);
						break;
					case 'y':
						setYahtzee(d, used);
						break;
					case 'c':
						setChance(d, used);
						break;
					case 'b':
						choice = 0;
						break;
					default:
						cout << "Invalid entry." << endl;
						break;
					}
				}
				break;
			case 3:
				// display the card when requested
				displayCard();
				break;
			default:
				cout << "Invalid entry." << endl;
			}
		}
	}
}
// because scoring for each of the upper categories (ones, twos, etc) is so similar, this function is called from each of those scoring functions
int Scorecard::evaluateUpperScore(vector<Dice*> d, int n) // takes the five dice and the integer n which is the number to be scored for
{
	// initializes a counter variable to 0
	int total = 0;
	// for each of the 5 dice, if the value of the die is equal to the specified number, we add that number to the total
	for (int i = 0; i < 5; i++)
	{
		// overloaded == operator checks if the value of the Dice object is equal to the integer
		total += (*(d[i]) == n ? n : 0);
	}
	// returns that total
	return total;
}

// function counts the total of all five dice, a useful function all five dice are added up for 3 of a kind, 4 of a kind, and chance
int Scorecard::evaluateTotal(vector<Dice*>d)
{
	// initializes a coutner variable to 0
	int total = 0;
	// for each of five dice, adds that die's total
	for (int i = 0; i < 5; i++)
	{
		total += (*(d[i])).getValue();
	}
	// returns the sum
	return total;
}
// displaycard() function prints the players scorecard to the screen
void Scorecard::displayCard()
{
	// creates an array of strings called categoryNames containing the names of each of the scoring categories sans chance
	string categoryNames[12] = { "1's","2's", "3's", "4's", "5's", "6's", "3OAK", "4OAK", "FH", "SS", "LS", "Yaht" };
	cout << endl;
	// In order to keep the scorecard in a reasonable space, we had the program print out the upper score on the left hand side and the lower scores on the right
	// for each of six rows...
	for (int i = 0; i < 6; i++)
	{
		// print out the first and seventh category names, followed by their values. If the category is unused, a blank space is output, otherwise, the scored value is shown
		cout << categoryNames[i] << setw(3) << (used[i] == false ? "  " : to_string(slots[i])) << "    " << setw(4) << categoryNames[i + 6] <<
			setw(3) << (used[i + 6] == false ? "  " : to_string(slots[i + 6])) << endl;
	}
	// for the final seventh row, do the same for the chance category, keeping it in line with the other lower scores
	cout << "          Chan" << setw(3) << (used[12] == false ? "  " : to_string(slots[12])) << endl << endl;
}
// This function disallows the user to attempt to use the same category multiple times in the same game
bool Scorecard::checkIfUsed(bool&b, bool used[], int n) // takes a pass by reference bool, the vector os used categories and an int n, the indicator of which category is being referred to
{
	// set the pass by reference variable to the status of the used vector at the specified index. This causes the scoreRoll() function to repreat until the user selects an unused category, as 
	// described in the scoreRoll() function
	b = used[n];
	// if the category was already used...
	if (b == true)
	{
		// tell the user to select another category
		cout << endl << "Category already used. Please select another." << endl << endl;
		// return a true bool. This will let the scoring functions know to stop the scoring process
		return true;
	}
	// if we make it to this point, the category must not have been used yet. Therefore, change the status of the category to used, and proceed to scoring
	used[n] = true;
	return false;
}

// all following get functions are the standard get functions for each index in the scoring array slots[]
// all following set functions use checkIfUsed to determine availablility. If checkIfUsed returns true, the functions immediately return withour scoring, and the scoreRoll() function makes the user
// choose a new category
// each upper scoring function adds its value to the upperTotal category

int Scorecard::getOnes() { return slots[0]; }
// uses evaluateUpperScore() to score ones and gives that value to the slots[] array
void Scorecard::setOnes(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 0) == true)
		return;
	int score = evaluateUpperScore(d, 1);
	slots[0] = score;
	slots[13] += score;
}
int Scorecard::getTwos() { return slots[1]; }
// uses evaluateUpperScore() to score twos and gives that value to the slots[] array
void Scorecard::setTwos(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 1) == true)
		return;
	int score = evaluateUpperScore(d, 2);
	slots[1] = score;
	slots[13] += score;
}
int Scorecard::getThrees() { return slots[2]; }
// uses evaluateUpperScore() to score threes and gives that value to the slots[] array
void Scorecard::setThrees(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 2) == true)
		return;
	int score = evaluateUpperScore(d, 3);
	slots[2] = score;
	slots[13] += score;
}
int Scorecard::getFours() { return slots[3]; }
// uses evaluateUpperScore() to score fours and gives that value to the slots[] array
void Scorecard::setFours(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 3) == true)
		return;
	int score = evaluateUpperScore(d, 4);
	slots[3] = score;
	slots[13] += score;
}
int Scorecard::getFives() { return slots[4]; }
// uses evaluateUpperScore() to score fives and gives that value to the slots[] array
void Scorecard::setFives(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 4) == true)
		return;
	int score = evaluateUpperScore(d, 5);
	slots[4] = score;
	slots[13] += score;
}
int Scorecard::getSixes() { return slots[5]; }
// uses evaluateUpperScore() to score sixes and gives that value to the slots[] array
void Scorecard::setSixes(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 5) == true)
		return;
	int score = evaluateUpperScore(d, 6);
	slots[5] = score;
	slots[13] += score;
}
int Scorecard::get3OAK() { return slots[6]; }

// all lower score functions add their value to the lower score category
// scores the dice for three of a kind
void Scorecard::set3OAK(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 6) == true)
		return;
	// initializes a bool to false, to indicate that the roll does not qualify for three of a kind
	bool qualify = false;
	// for each of six possible values of the dice, check the dice to see how many appear. 
	// This is done in reverse order to assist with efficiency, as a player is more likely to use 3OAK for larger values
	for (int i = 6; i >= 1; i--)
	{
		// initialize a counter to 0 (done inside the for() loop to reset the counter for each value of dice 1-6)
		int count = 0;
		// search the five dice for the value specified by the outer for loop
		for (int j = 0; j < 5; j++)
		{
			// if the value of the die at that index is equal to the index, increment the count
			if ((*(d[j])).getValue() == i)
				count++;
		}
		// if the a number has been counted thrice, set the qualify bool to true and break out of the outer for() loop
		if (count >= 3)
		{
			qualify = true;
			break;
		}
	}
	// if the roll did not have three dice of the same value, set the value of slots to 0
	if (qualify == false)
		slots[6] = 0;
	// if it did qualify, use the evaluateTotal() function to score the roll. Set this total equal to the value of slots
	else
		slots[6] = evaluateTotal(d);
	slots[14] += slots[6];
}
int Scorecard::get4OAK() { return slots[7]; }
// The same process as outlined for three of a kind is used here, requiring a fourth die of the same value to be found
void Scorecard::set4OAK(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 7) == true)
		return;
	bool qualify = false;
	for (int i = 6; i >= 1; i--)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
		{
			if ((*(d[j])).getValue() == i)
				count++;
		}
		if (count >= 4)
		{
			qualify = true;
		}
	}
	if (qualify == false)
		slots[7] = 0;
	else
		slots[7] = evaluateTotal(d);
	slots[14] += slots[7];
}
int Scorecard::getFullHouse() { return slots[8]; }
// scores the dice for qualification for full house, three dice of one value, two of another
void Scorecard::setFullHouse(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 8) == true)
		return;
	// creates two arrays of 6 values each, one to count how many dice having a given value are found, the other to simply track IF ANY dice of the certain value are found
	int numbers[6] = { 0,0,0,0,0,0 };
	int counts[6] = { 0,0,0,0,0,0 };
	// for each of the five dice...
	for (int i = 0; i < 5; i++)
	{
		// set the numbers[] array equal to one at the index of the die's value minus 1
		numbers[(*(d[i])).getValue() -1]=1;
		// increment the counts[] array at the index of the die's value minus 1
		counts[(*(d[i])).getValue() - 1]++;
	}
	// initialize a counter to 0
	int sum = 0;
	// increment the sum variable for each number present in the roll
	for (int i = 0; i < 6; i++)
	{
		sum += numbers[i];
	}
	// for a full house to be true, there must be exaclty two values represented.
	if (sum != 2)
	{
		// if there are not, set the slots to 0
		slots[8] = 0;
	}
	// if there are, we must make sure there are not four of one and one of the other (whatever the value of the first die is, there must be either two or three of them present)
	else if (counts[(*(d[0])).getValue() - 1] == 2 || counts[(*(d[0])).getValue() - 1] == 3)
		// if so, give 25 to the slots category
		slots[8] = 25;
	// if not, give 0
	else slots[8] = 0;
	slots[14] += slots[8];

}
int Scorecard::getSStraight() { return slots[9]; }
// evaluates the dice for qualification as a small straight
void Scorecard::setSStraight(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 9) == true)
		return;
	// creates the same array as in full house to track which numbers are present
	int numbers[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 5; i++)
	{
		// sets the value of the numbers[] array equal to 1 at the index of the value of the die minus 1
		numbers[(*(d[i])).getValue() - 1] = 1;
	}
	// small straight could be either: 1,2,3,4 2,3,4,5 or 3,4,5,6.
	// thuse, 3 and 4 are necessary. Check if they are present. If not, set slots to 0
	if (numbers[2] == 0 || numbers[3] == 0)
		slots[9] = 0;
	// if they are, check the presence of one of the three options described above
	else if ((numbers[0] == 1 && numbers[1] == 1) || (numbers[1] == 1 && numbers[4] == 1) || (numbers[4] == 1 && numbers[5] == 1))
		// if one is found, give 30 to the slots array
		slots[9] = 30;
	// otherwise, give 0
	else slots[9] = 0;
	slots[14] += slots[9];
}
int Scorecard::getLStraight() { return slots[10]; }
// same process as small striaght is used here, but the possibilities are now just 1,2,3,4,5 and 2,3,4,5,6. Thus 2,3,4 and 5 are necessary and we check if either 1 or 6 is present given those 4
void Scorecard::setLStraight(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 10) == true)
		return;
	int numbers[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 5; i++)
	{
		numbers[(*(d[i])).getValue() - 1] = 1;
	}
	if (numbers[1] == 0 || numbers[2] == 0 || numbers[3] == 0 || numbers[4] == 0)
		slots[10] = 0;
	else if (numbers[0] == 0 && numbers[5] == 0)
		slots[10] = 0;
	else slots[10] = 40;
	slots[14] += slots[10];
}
int Scorecard::getYahtzee() { return slots[11]; }
// used to evaluate Yahtzee qualification
void Scorecard::setYahtzee(vector<Dice*> d, bool& b)
{
	// initialize a counter to 0
	int yaht = 0;
	// for the four dice following the first, see if they are all ewual to the first
	for (int i = 1; i < 5; i++)
	{
		yaht += ((*(d[i])).getValue() == (*(d[0])).getValue() ? 1 : 0);
	}
	// set the pass by reference bool equal to the status of the used vector at the yahtzee location
	b = used[11];
	// if the category has already been used, and the roller did not roll a yahtzee, tell them to choose something else
	if (b == true && yaht!=4)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	// however, even if the category has been used, they can score a bonus yahtzee if they already have at least one yahtzee for the game
	if (b==true && yaht == 40 && slots[11]!=0)
	{
		// bonus yahtzees are worth 100
		slots[11] += 100;
		// the player is required to scratch a category in substitution for their bonus yahtzee
		cout << "Bonus Yahtzee! Please select a category to substitute for." << endl;
		// set each of the dice to 0, so that nothing is scored on thier substitution
		for (int i = 0; i < 5; i++)
		{
			(*(d[i])).setValue(0);
		}
		return;
	}
	// if we get to here, the category must not have been used. Set the used[] array to true
	used[11] = true;
	// if the player has a yahtzee, score fifty
	if (yaht == 4)
		slots[11] = 50;
	// otherwise, score 0
	else slots[11] = 0;
	slots[14] += slots[11];
}
int Scorecard::getChance() { return slots[12]; }
// scores the value of all five dice regardless of values, utilizes evaluateTotal() function
void Scorecard::setChance(vector<Dice*> d, bool& b)
{
	if (checkIfUsed(b, used, 12) == true)
		return;
	slots[12] = evaluateTotal(d);
	slots[14] += slots[12];
}
// return values of the upper and lower total categories
int Scorecard::getUpperScore() { return slots[13]; }
int Scorecard::getLowerScore() { return slots[14]; }
// getScore() sets the totalScore equal to the sum of the upper and lower scores, adding a 35 point bonus if the upper score is at least 63
int Scorecard::getScore() { 
	slots[15] = slots[13] + slots[14];
	slots[15] += (slots[13] >= 63 ? 35 : 0);
	return slots[15]; }


