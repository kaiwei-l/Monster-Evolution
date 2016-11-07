#include "MonsterAdv.h"

MonsterAdv::MonsterAdv(std::string name, int id, int skillVal, int health, int powerVal) : Monster(name, id)
{
	skill = skillVal;
	healthMax = health;
	healthCur = health;
	powerModi = powerVal;

}

MonsterAdv::~MonsterAdv(){}


std::string MonsterAdv::showMonster()
{
	std::stringstream ss;

	ss << "\n=====Monster Info====="
		<< "\nType: " << type
		<< "\nSkill Level: " << skill
		<< "\nCurrent Health: " << healthCur
		<< "\nMax Health: " << healthMax
		<< "\nPower Modifier: " << powerModi << std::endl;

	return ss.str();
}

int MonsterAdv::getHp()
{
	return healthCur;
}

void MonsterAdv::addHp(int num)
{
	if (healthCur + num > healthMax)
	{
		healthCur = healthMax;
	}
	else
	{
		healthCur += num;
	}
}

int MonsterAdv::getSkill()
{
	return (skill + powerModi);
}

void MonsterAdv::addSkill(int num, std::string skillType)
{
	if (skillType == "skill")
	{
		skill += num;
	}
	else  // add bothe the current health and the max health
	{
		healthMax += num;
		healthCur += num;
	}
}

int MonsterAdv::getID()
{
	return id;
}