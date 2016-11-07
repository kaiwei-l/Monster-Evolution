#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>
#include "Unit.h"

class Monster : public Unit
{
	/*
	This is a derived virtual class with base class Unit. 
	Itself is a base class for Monster data type, i.e. Adance Monster and Normal Monster
	It declares several virtual functions left for derived monster class implementing themselves

	*/

protected:
	std::string type;  // Monster type

public:
	Monster::Monster(std::string name, int id);
	virtual ~Monster() = default;
	virtual std::string showMonster() = 0;
	virtual int getHp() = 0;
	virtual int getSkill() = 0;
	virtual void addHp(int num) = 0;
	virtual void addSkill(int num, std::string skillType) = 0;

};


#endif