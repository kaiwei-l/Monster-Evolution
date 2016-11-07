#include "MonsterNorm.h"

MonsterNorm::MonsterNorm(std::string name, int id) : Monster(name, id)
{
	skill = new int(rand() % 10 + 1);
	healthMax = new int(rand() % 8 + 3);
	healthCur = new int(*healthMax);
}

MonsterNorm::~MonsterNorm()
{
	delete skill;
	delete healthCur;
	delete healthMax;
}

std::string MonsterNorm::showMonster() // return informaiton of monster in a reable format
{
	std::stringstream ss;

	ss << "\n=====Monster Info====="
		<< "\nType: " << type
		<< "\nSkill Level: " << *skill
		<< "\nCurrent Health: " << *healthCur
		<< "\nMax Health: " << *healthMax << "\n";

	return ss.str();
}

int MonsterNorm::getHp()
{
	return *healthCur;
}

void MonsterNorm::addHp(int num)
{
	if (*healthCur + num > *healthMax)  // if the result of current health adds the hp from box exceeds the max health, 
		                                // we simply reset the current health level
	{
		*healthCur = *healthMax;
	}
	else
	{
		*healthCur += num;
	}
}

int MonsterNorm::getSkill()
{
	return *skill;
}


int MonsterNorm::getID()
{
	return id;
}

std::string MonsterNorm::getType()
{
	return type;
}

void MonsterNorm::addSkill(int num, std::string skillType)
{
	if (skillType == "skill")
	{
		*skill += num;
	}
	else // when player choose to add exp to health, both current and max health are added with the same number
	{
		*healthMax += num;
		*healthCur += num;
	}
}