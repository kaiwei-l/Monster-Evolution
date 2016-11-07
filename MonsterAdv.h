#ifndef MONSTERADV_H
#define MONSTERADV_H
#include <time.h>
#include <sstream>
#include "Monster.h"

class MonsterAdv : public Monster
{
	/*
	This class is a derived class of sub-base class Monster
	This class is for evolved monster and skeletor monster
	Advanced monsters have id number 3
	*/
private:	
	int skill;
	int healthMax;
	int healthCur;
	int powerModi;

public:
	MonsterAdv::MonsterAdv(std::string name, int id, int skill, int health, int powerModi);
	~MonsterAdv();
	std::string showMonster();
	int getHp();
	int getSkill();
	void addHp(int num);
	void addSkill(int num, std::string skillType);
	int getID();

};

#endif