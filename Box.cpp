#include <time.h>
#include "Box.h"

Box::Box() : Unit(5)
{
	int tmp = rand() % 3;
	if (tmp == 0)
	{
		type = "hp";  // this value can only be added to current health, not max health
		val = rand() % 10 + 1;
	}
	else if (tmp == 1)
	{
		type = "exp";  // this value can be added to max health or skill level
		val = rand() % 5 + 1;
	}
	else
	{
		type = "punish";  // minus one from current health point
		val = -1;
	}
}



Box::~Box(){}

int Box::getVal()
{
	return val;
}

std::string Box::getName()
{
	return type;
}

int Box::getID()
{
	return id;
}