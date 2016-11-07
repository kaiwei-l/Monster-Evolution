#ifndef UNIT_H
#define UNIT_H
#include <iostream>

class Unit
{
	/*
	This is the most base class of all abstract data type in this program. 
	It contains only one data member called ID, which is used for identifying what derived class type might lying under 
	one object who has the class type Unit
	*/

protected:
	int id;  
	/*
	A list of ID number
	1. unit: -1
    2. player: 0  
	3. monster friendly: 1   
	4. monster attack: 2  
	5. Monster Advanced: 3   
	7. box: 5   
	8. exit: -2   
	9. visited cell: 4
	*/

public:
	Unit::Unit(int num = -1);
	virtual ~Unit() = default;
	virtual int getID();  // a virtul function left for other derived classes implementing themselves
	
};

#endif