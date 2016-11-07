#include "Player.h"

Player::Player(std::string userName) : Unit(0)
{
	name = new std::string(userName);
	healthCur = new int(10);
	healthMax = new int(10);
	skill = new int(7);
	bag.reserve(10);
	

	for (int i = 0; i < 3; i++)
	{
		int tmp = 0;
		monsterCount.push_back(tmp);
	}
}

Player::~Player()
{
	delete name;
	delete healthCur;
	delete healthMax;
	delete skill;
}

int Player::getHp(std::string healthType, std::string role)
{/*
 First part of this fucntion simply returns the HP of player during the fight with octopod
 Second part provides an interface to get the hp of evolved monster when user finds the exit
 */
	
	if (role == "player")
	{
		if (healthType == "current")
		{
			return *healthCur;
		}
		else
		{
			return *healthMax;
		}
	}
	else
	{
		if (evolved.size() != 0)
		{
			return evolved[0].getHp();
		}
		else
		{
			std::cout << "Get HP failed: No Evolved Monster" << std::endl;
		}
	}
}

void Player::addHp(int num, std::string role)
{
	/*
	This function acts as an interface to add health point to evolved monster when hp type box is
	used by player
	*/
	if (role == "player")
	{
		if (*healthCur + num >= *healthMax)
		{
			*healthCur = *healthMax;
		}
		else
		{
			*healthCur += num;
		}
	}
	else  // evolved monster
	{
		if (evolved.size() != 0)
		{
			evolved[0].addHp(num);
		}
		else
		{
		std::cout << "Add HP failed: No Evolved Monster" << std::endl;  // waste one bottle of HP
		}
	}
}

int Player::getSkill(std::string role)
{
	if (role == "evolved")
	{
		if (evolved.size() != 0)
		{
			return evolved[0].getSkill();
		}
		else  // if player doesn't have evolved monster
		{
			return -100;
		}
	}
	else
	{
		return *skill;
	}
}

void Player::addSkill(std::string skillType, std::string role, int num, int index = -1)
{
	/*
	this function has an interface to add player or evolved monster's skill points
	*/
	if (role == "player")
	{
		*skill += num;
	}
	else if (role == "evolved")
	{
		evolved[0].addSkill(num, skillType);
	}
}

std::string Player::showPlayer()
{
	std::stringstream ss;

	ss << "\n=====Player Info====="
		<< "\nName: " << *name
		<< "\nCurrent Health: " << *healthCur
		<< "\nMax Health: " << *healthMax
		<< "\nSkill Level: " << *skill
		<< "\nNumber of items in bag: " << bag.size()
		<< "\nNumber of monsters in collection: " << collection.size()
		<< "\nNumber of Evolved Monster: " << evolved.size();

	return ss.str();
}

std::string Player::showBag()
{
	std::stringstream ss;
	ss << "\n\n---Bag Info---";
	if (bag.size() != 0)
	{
		for (int i = 0; i < bag.size(); i++)
		{
			ss << "\nNo." << i << " " << "Item: " << bag[i].getName()
				<< " " << "Value: " << bag[i].getVal();
		}

		return ss.str();
	}
	else
	{
		ss << "\nEmpty";
		return ss.str();
	}
}

std::string Player::showCollection()
{
	/*
	When the number of a type of monster has reached five, we need to get an evolved monster.
	Hence, I change the MonsterNorm type pointer in the collection pointing to NULL.
	Because we don't need them anymore, which should be deleted
	*/
	std::stringstream ss;
	ss << "\n\n---Collection Info---";

	if (collection.size() != 0)
	{
		int j = 1;
		for (int i = 0; i < collection.size(); i++)
		{
			if (collection[i] != NULL)
			{
				ss << "\nNo." << j;
				ss << collection[i]->showMonster();
				j++;
			}
		}

		return ss.str();
	}
	else
	{
		ss << "\nEmpty";
		return ss.str();
	}
}

std::string Player::shouldEvolved()
{
	/*
	This function returns the name of the monster if the total number of this type in collection
	is 5.
	None if condition is not meet, i.e. 5 monsters with the same type
	*/
	for (int i = 0; i < monsterCount.size(); i++)
	{
		if (monsterCount[i] == 5)
		{
			if (i == 0)
			{
				return "bugbear";
			}
			else if (i == 1)
			{
				return "platypie";
			}
			else
			{
				return "emoo";
			}
		}
	}
	return "None";
}

bool Player::haveEvolved()
{
	if (evolved.size() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::updateEvolved(std::string name, int skill, int health, int powerModi)
{
	/*
	Add evolved monster to vector evolved
	*/
	if (evolved.size() == 0)
	{
		MonsterAdv tmp(name, 3, skill, health, powerModi);
		evolved.push_back(tmp);
	}
	else
	{
		MonsterAdv tmp(name, 3, skill, health, powerModi);
		evolved[0] = tmp;
	}
}

void Player::updateCollection(MonsterNorm* tmp)
{
	collection.push_back(tmp);
	std::string type = tmp->getType();

	if (type == "bugbear")
	{
		monsterCount[0] += 1;
	}
	else if (type == "platypie")
	{
		monsterCount[1] += 1;
	}
	else
	{
		monsterCount[2] += 1;
	}
}

void Player::useBag(int index, int itemType, int role, int skillType)
{
	Box tmp = bag[index];
	bag.erase(bag.begin() + index); // delete that item in bag

	if (itemType == 1) // item: hp
	{
		if (role == 1)   // player
		{
			addHp(tmp.getVal(), "player");
		}
		else  // evolved
		{
			evolved[0].addHp(tmp.getVal());
		}
	}
	else  // item: exp
	{
		if (role == 1)  // player
		{
			if (skillType == 1)  // health
			{
				(*healthCur) += tmp.getVal();
				(*healthMax) += tmp.getVal();
			}
			else  // skill
			{
				(*skill) += tmp.getVal();
			}
		}
		else  // evolved
		{
			if (skillType == 1)  // add to health
			{
				evolved[0].addSkill(tmp.getVal(), "healthMax");
			}
			else  // add to skill level
			{
				evolved[0].addSkill(tmp.getVal(), "skill");
			}
		}
	}
}

void Player::getEvolved(std::string monsterType)
{
	/*
	Get an evolved monster.
	This function provides an interface to create an evolved monster when providing a
	monster type
	*/
	int skill = 0;
	int health = 0;
	int powerModi = 0;
	if (monsterType == "bugbear")
	{
		powerModi = 1;
		monsterCount[0] = 0;
	}
	else if (monsterType == "platypie")
	{
		powerModi = 2;
		monsterCount[1] = 0;
	}
	else  // type: emoo
	{
		powerModi = 3;
		monsterCount[2] = 0;
	}

	for (int i = 0; i < collection.size(); i++)
	{
		if (collection[i] != NULL && collection[i]->getType() == monsterType)
		{
			skill += collection[i]->getSkill();
			health += collection[i]->getHp();
			delete collection[i];
			collection[i] = NULL;
		}
	}

	updateEvolved(monsterType, skill, health, powerModi);
}

bool Player::updateBag(Box* tmp)
{
	/*
	add item to bag
	*/
	if (tmp->getName() == "punish")
	{
		(*healthCur) += tmp->getVal();
		return false;
	}
	else
	{
		std::cout << "\nThe item you got is: " << tmp->getName() << std::endl;
		bag.push_back(*tmp);
		return true;
	}
}

int Player::getBagSize()
{
	return bag.size();
}

int Player::getItemInfo(int index)
{
	if (bag[index].getName() == "hp")
	{
		return 1;
	}
	else
	{
		return 2;
	}
}


std::string Player::displayEvoleved()
{
	std::stringstream ss;
	ss << "\n---Evolved Monster Info---\n";
	if (evolved.size() == 0)
	{
		ss << "No Evolved Monster";
	}
	else
	{
		ss << evolved[0].showMonster();
	}

	return ss.str();
}

int Player::getID()
{
	return id;
}
