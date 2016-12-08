#include"Scorecard.h"

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
		total += (*(d.at(i))).getValue();
	}
	return total;
}

vector<int> sortdice(vector<Dice*> d)
{
	vector<int> random;
	return random;
}

Scorecard::Scorecard() {
	for (int i = 0; i < 16; i++)
	{
		slots[i] = 0;
	}
}

int Scorecard::getOnes() { return slots[0]; }
void Scorecard::setOnes(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 1);
	slots[0] = score;
	slots[13] += score;
}
int Scorecard::getTwos() { return slots[1]; }
void Scorecard::setTwos(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 2);
	slots[1] = score;
	slots[13] += score;
}
int Scorecard::getThrees() { return slots[2]; }
void Scorecard::setThrees(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 3);
	slots[2] = score;
	slots[13] += score;
}
int Scorecard::getFours() { return slots[3]; }
void Scorecard::setFours(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 4);
	slots[3] = score;
	slots[13] += score;
}
int Scorecard::getFives() { return slots[4]; }
void Scorecard::setFives(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 5);
	slots[4] = score;
	slots[13] += score;
}
int Scorecard::getSixes() { return slots[5]; }
void Scorecard::setSixes(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 6);
	slots[5] = score;
	slots[13] += score;
}
int Scorecard::get3OAK() { return slots[6]; }
void Scorecard::set3OAK(vector<Dice*> d)
{
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
void Scorecard::set4OAK(vector<Dice*> d)
{
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
void Scorecard::setFullHouse(vector<Dice*> d)
{
	int numbers[6] = { 0,0,0,0,0,0 };
	int counts[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 5; i++)
	{
		numbers[(*(d.at(i))).getValue()-1]=1;
		counts[(*(d.at(i))).getValue() - 1]++;
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
void Scorecard::setSStraight(vector<Dice*> d)
{

}
int Scorecard::getLStraight() { return slots[10]; }
void Scorecard::setLStraight(vector<Dice*> d)
{

}
int Scorecard::getYahtzee() { return slots[11]; }
void Scorecard::setYahtzee(vector<Dice*> d)
{

}
int Scorecard::getChance() { return slots[12]; }
void Scorecard::setChance(vector<Dice*> d)
{

}
int Scorecard::getUpperScore() { return slots[13]; }
int Scorecard::getLowerScore() { return slots[14]; }
int Scorecard::getScore() { return slots[15]; }