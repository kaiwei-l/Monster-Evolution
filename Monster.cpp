#include "Monster.h"

Monster::Monster(std::string name, int id) : Unit(id)
{
	type = name;
}