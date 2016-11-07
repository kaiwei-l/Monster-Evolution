#ifndef BOX_H
#define BOX_H
#include <string>
#include <iostream>
#include "Unit.h"

class Box : public Unit
{
	/*
	This class is a derived class from base class Unit, which is the most base class for all objects in this program
	This class is a box class, which contains 'hp' and 'exp', two things that are normal in PC game.
	Each box either contains a hp, an exp or a punishment.
	When player opens the box which containing punishment, he will lose one health point
	*/
private:
	std::string type;
	int val;  // value is the number will be added to health point or skill level. Each box has a different value ranged from 1 to 5 if box type is exp
	// or ranged from 1 to 10 if box type is hp
public:
	Box::Box();
	~Box();
	int getVal();
	std::string getName();
	int getID() override;
};

#endif