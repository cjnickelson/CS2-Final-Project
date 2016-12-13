#include"Dice.h"

// no arg constructor for dice gives a die with value 0
Dice::Dice()
{
	value = 0;
}

// Dice constructor which copies the value of a pointer to a dice as an argument
Dice::Dice(Dice* b)
{
	value = (*b).getValue();
}

// Dice constructor which constucts a dice with value speicified by argument integer
Dice::Dice(int b)
{
	value = b;
}

// baseic get and set member functions for value
int Dice::getValue()
{
	return value;
}

void Dice::setValue(int i)
{
	value = i;
}

// roll function, used to randomize game. Outputs random number from 1 to 6, like a 6-sided die
void Dice::roll()
{
	value = rand() % 6 + 1;
}

// overloaded == operator. When used between a die and an integer, operator returns true if the value of that die is equal to the specified integer
bool Dice::operator==(int n)
{
	if (value == n)
		return true;
	else return false;
}
