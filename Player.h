#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include <vector>
#include "Unit.h"
#include "Box.h"
#include "MonsterAdv.h"
#include "MonsterNorm.h"

class Player : public Unit
{
	/*
	Player class is a derived class with vietual base class: Unit
	It provides an interface to do some operations on evolved monster
	*/
private:
	std::string* name;
	int* healthCur;
	int* healthMax;
	int* skill;
	std::vector<Box> bag;  // Box items (hp or exp) are put in the bag
	std::vector<int> monsterCount; // records the total number of each type of monsters player has
	std::vector<MonsterNorm*> collection;  // all captured monsters are in there
	std::vector<MonsterAdv> evolved;  // a vector which holding the evolved monster 
	                                  // and the size should always be one

public:
	Player::Player(std::string userName);
	~Player();
	int getHp(std::string healthType, std::string role);
	void addHp(int num, std::string role);
	int getSkill(std::string role);
	void addSkill(std::string skillType, std::string role, int num, int index);
	std::string showPlayer();  // return player information in a readable way
	std::string showBag();  // return the content in the bag in a readable way
	std::string showCollection();  // return the content in the collection in a readable way
	std::string shouldEvolved();  // return type of the monster whose total number is 5
	bool haveEvolved();  // check if player have evolved monster
	void updateEvolved(std::string name, int skill, int health, int powerModi);
	void updateCollection(MonsterNorm* tmp);
	bool updateBag(Box* tmp);
	void useBag(int index, int itemType, int role, int skillType = -1);  // use the item in bag
	int getID();
	void getEvolved(std::string monsterType);
	int getBagSize();
	int getItemInfo(int index);
	std::string displayEvoleved();  // return the information of evolved monster i player has one, none if player doesn't have one
	
};


#endif