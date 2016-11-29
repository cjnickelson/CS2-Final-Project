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

int Scorecard::getOnes() { return ones; }
void Scorecard::setOnes(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 1);
	ones = score;
}
int Scorecard::getTwos() { return twos; }
void Scorecard::setTwos(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 2);
	twos = score;
}
int Scorecard::getThrees() { return threes; }
void Scorecard::setThrees(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 3);
	threes = score;
}
int Scorecard::getFours() { return fours; }
void Scorecard::setFours(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 4);
	fours = score;
}
int Scorecard::getFives() { return fives; }
void Scorecard::setFives(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 5);
	fives = score;
}
int Scorecard::getSixes() { return sixes; }
void Scorecard::setSixes(vector<Dice*> d)
{
	int score = evaluateUpperScore(d, 6);
	sixes = score;
}
int Scorecard::get3OAK() { return threeOfaKind; }
void Scorecard::set3OAKs(vector<Dice*> d)
{

}
int Scorecard::get4OAK() { return fourOfaKind; }
void Scorecard::set4OAK(vector<Dice*> d)
{

}
int Scorecard::getFullHouse() { return fullHouse; }
void Scorecard::setFullHouse(vector<Dice*> d)
{

}
int Scorecard::getSStraight() { return smallStraight; }
void Scorecard::setSStraight(vector<Dice*> d)
{

}
int Scorecard::getLStraight() { return largeStraight; }
void Scorecard::setLStraight(vector<Dice*> d)
{

}
int Scorecard::getYahtzee() { return Yahtzee; }
void Scorecard::setYahtzee(vector<Dice*> d)
{

}
int Scorecard::getChance() { return chance; }
void Scorecard::setChance(vector<Dice*> d)
{

}
int Scorecard::getUpperScore() { return upperScore; }
int Scorecard::getLowerScore() { return lowerScore; }
int Scorecard::getScore() { return lowerScore + upperScore; }