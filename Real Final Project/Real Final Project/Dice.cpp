#include"Dice.h"

Dice::Dice()
{
	value = 0;
}

Dice::Dice(Dice* b)
{
	value = (*b).getValue();
}

int Dice::getValue()
{
	return value;
}

void Dice::setValue(int i)
{
	value = i;
}

void Dice::roll()
{
	srand(time(NULL));
	value = rand() % 6 + 1;
}

bool Dice::operator==(int n)
{
	if (value == n)
		return true;
	else return false;
}
