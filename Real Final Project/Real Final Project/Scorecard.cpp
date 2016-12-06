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
void Scorecard::set3OAKs(vector<Dice*> d)
{

}
int Scorecard::get4OAK() { return slots[7]; }
void Scorecard::set4OAK(vector<Dice*> d)
{

}
int Scorecard::getFullHouse() { return slots[8]; }
void Scorecard::setFullHouse(vector<Dice*> d)
{

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