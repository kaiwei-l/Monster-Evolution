#ifndef MONSTERNORM_H
#define MONSTERNORM_H
#include <sstream>
#include <string>
#include <time.h>
#include "Monster.h"

class MonsterNorm : public Monster
{
	/*
	This class contains four types of monster: bugbear, platypie, emoo and octopod
	*/
private:
	int* skill;  // skill level, which is used to attack or escape
	int* healthMax;  // max health level
	int* healthCur;  // current health level

public:
	MonsterNorm::MonsterNorm(std::string name, int id);
	~MonsterNorm();
	std::string showMonster();  // display basic information of monster in a readable way
	int getHp();  // return current health
	void addHp(int num);  // add number to current health level
	int getSkill();  // return skill level
	int getID();  // return id number inherited from base class
	std::string getType();  // return the type of the monster
	void addSkill(int num, std::string skillType);  // skill type can be skill level or max health
};


#endif