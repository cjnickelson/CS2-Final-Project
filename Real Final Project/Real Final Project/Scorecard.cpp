#include"Scorecard.h"
#include<iomanip>

void Scorecard::scoreRoll(vector<Dice*> d)
{
	bool used = true;
	displayCard();
	while (used)
	{
		cout << "What would you like to do?" << endl<< "Score roll to upper portion:    1" << endl<< "Score roll to lower portion:    2" << endl << "View your scorecard:            3" << endl;
		int choice = 0, choice2 = 0;
		char choice3 = 'q';
		while (choice != 1 && choice != 2 && choice != 3)
		{
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Which number would you like to score to? To go back, choose 7." << endl;
				while (choice2 < 1 || choice2>7)
				{
					cin >> choice2;
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
					}
				}
				break;
			case 2:
				cout << "Which category do you want to score to?" << endl;
				cout << "Three of a Kind: 3" << endl<< "Four of a kind:  4" << endl<< "Full House:      f" << endl<<"Small straight:  s" << endl<< "Large straight:  l" << endl
				<< "Yahtzee:         y" << endl<< "Chance:          c" << endl<< "Go back:         b" << endl;
				while (choice3 != '3'&&choice3 != '4'&&choice3 != 'f'&&choice3 != 's'&&choice3 != 'l'&&choice3 != 'y'&&choice3 != 'c'&&choice3!='b')
				{
					cin >> choice3;
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
					}
				}
				break;
			case 3:
				displayCard();
				break;
			default:
				cout << "Invalid entry." << endl;
			}
		}
	}
}

int evaluateUpperScore(vector<Dice*> d, int n)
{
	int total = 0;
	for (int i = 0; i < 5; i++)
	{
		total += (*(d.at(i)) == n ? n : 0);
	}
	return total;
}

int evaluateTotal(vector<Dice*>d)
{
	int total = 0;
	for (int i = 0; i < 5; i++)
	{
		total += (*(d[i])).getValue();
	}
	return total;
}


Scorecard::Scorecard() {
	for (int i = 0; i < 16; i++)
	{
		slots[i] = 0;
		used[i] = false;
	}
}

int Scorecard::getOnes() { return slots[0]; }
void Scorecard::setOnes(vector<Dice*> d, bool& b)
{
	b = used[0];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[0] = true;
	int score = evaluateUpperScore(d, 1);
	slots[0] = score;
	slots[13] += score;
}
int Scorecard::getTwos() { return slots[1]; }
void Scorecard::setTwos(vector<Dice*> d, bool& b)
{
	b = used[1];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[1] = true;
	int score = evaluateUpperScore(d, 2);
	slots[1] = score;
	slots[13] += score;
}
int Scorecard::getThrees() { return slots[2]; }
void Scorecard::setThrees(vector<Dice*> d, bool& b)
{
	b = used[2];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[2] = true;
	int score = evaluateUpperScore(d, 3);
	slots[2] = score;
	slots[13] += score;
}
int Scorecard::getFours() { return slots[3]; }
void Scorecard::setFours(vector<Dice*> d, bool& b)
{
	b = used[3];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[3] = true;
	int score = evaluateUpperScore(d, 4);
	slots[3] = score;
	slots[13] += score;
}
int Scorecard::getFives() { return slots[4]; }
void Scorecard::setFives(vector<Dice*> d, bool& b)
{
	b = used[4];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[4] = true;
	int score = evaluateUpperScore(d, 5);
	slots[4] = score;
	slots[13] += score;
}
int Scorecard::getSixes() { return slots[5]; }
void Scorecard::setSixes(vector<Dice*> d, bool& b)
{
	b = used[5];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[5] = true;
	int score = evaluateUpperScore(d, 6);
	slots[5] = score;
	slots[13] += score;
}
int Scorecard::get3OAK() { return slots[6]; }
void Scorecard::set3OAK(vector<Dice*> d, bool& b)
{
	b = used[6];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[6] = true;
	bool correct = false;
	for (int i = 1; i <= 6; i++)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
		{
			if ((*(d.at(j))).getValue() == i)
				count++;
		}
		if (count >= 3)
		{
			correct = true;
		}
	}
	if (correct == false)
		slots[6] = 0;
	else
		slots[6] = evaluateTotal(d);
}
int Scorecard::get4OAK() { return slots[7]; }
void Scorecard::set4OAK(vector<Dice*> d, bool& b)
{
	b = used[7];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[7] = true;
	bool correct = false;
	for (int i = 1; i <= 6; i++)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
		{
			if ((*(d.at(j))).getValue() == i)
				count++;
		}
		if (count >= 4)
		{
			correct = true;
		}
	}
	if (correct == false)
		slots[7] = 0;
	else
		slots[7] = evaluateTotal(d);
}
int Scorecard::getFullHouse() { return slots[8]; }
void Scorecard::setFullHouse(vector<Dice*> d, bool& b)
{
	b = used[8];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[8] = true;
	int numbers[6] = { 0,0,0,0,0,0 };
	int counts[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 5; i++)
	{
		numbers[(*(d[i])).getValue() -1]=1;
		counts[(*(d[i])).getValue() - 1]++;
	}
	int sum = 0;
	for (int i = 0; i < 6; i++)
	{
		sum += numbers[i];
	}
	if (sum != 2)
	{
		slots[8] = 0;
	}
	else if (counts[(*(d.at(0))).getValue() - 1] == 2 || counts[(*(d.at(0))).getValue() - 1] == 3)
		slots[8] = 25;
	else slots[8] = 0;

}
int Scorecard::getSStraight() { return slots[9]; }
void Scorecard::setSStraight(vector<Dice*> d, bool& b)
{
	b = used[9];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[9] = true;
	int numbers[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 5; i++)
	{
		numbers[(*(d[i])).getValue() - 1] = 1;
	}
	if (numbers[2] == 0 || numbers[3] == 0)
		slots[9] = 0;
	else if ((numbers[0] == 1 && numbers[1] == 1) || (numbers[1] == 1 && numbers[4] == 1) || (numbers[4] == 1 && numbers[5] == 1))
		slots[9] = 30;
	else slots[9] = 0;
}
int Scorecard::getLStraight() { return slots[10]; }
void Scorecard::setLStraight(vector<Dice*> d, bool& b)
{
	b = used[10];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[10] = true;
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
}
int Scorecard::getYahtzee() { return slots[11]; }
void Scorecard::setYahtzee(vector<Dice*> d, bool& b)
{
	int yaht = 0;
	for (int i = 1; i < 5; i++)
	{
		yaht += ((*(d[i])).getValue() == (*(d.at(0))).getValue() ? 1 : 0);
	}
	b = used[11];
	if (b == true && yaht!=4)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	if (b==true && yaht == 40 && slots[11]!=0)
	{
		slots[11] += 100;
		cout << "Bonus Yahtzee! Please select a category to substitute for." << endl;
		for (int i = 0; i < 5; i++)
		{
			(*(d[i])).setValue(0);
		}
		return;
	}
	used[11] = true;
	if (yaht == 4)
		slots[11] = 50;
	else slots[11] = 0;
}
int Scorecard::getChance() { return slots[12]; }
void Scorecard::setChance(vector<Dice*> d, bool& b)
{
	b = used[12];
	if (b == true)
	{
		cout << "Category already used. Please select another." << endl;
		return;
	}
	used[12] = true;
	slots[12] = evaluateTotal(d);
}
int Scorecard::getUpperScore() { return slots[13]; }
int Scorecard::getLowerScore() { return slots[14]; }
int Scorecard::getScore() { return slots[15]; }

void Scorecard::displayCard()
{
	cout << endl;
	for (int i = 0; i < 6; i++)
	{
		cout <<setw(2)<< slots[i] <<"    " << slots[i+6]<< endl;
	}
	cout << "      " << slots[12] << endl<<endl;
}