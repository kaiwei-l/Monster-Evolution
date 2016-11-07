#include "GameController.h"

GameController::GameController()
{
	std::string name = getString("name");

	for (int i = 0; i < 10; i++)  // initialise board
	{
		std::vector<Unit*> tmp;
		for (int j = 0; j < 20; j++)
		{
			tmp.push_back(new Unit());
		}
		board.push_back(tmp);
	}

	int playerRow = rand() % 10;  // player original column number is always 0
	int skeletorRow = rand() % 10;  // skeletor original column number is always 19
	board[playerRow][0] = new Player(name);
	board[skeletorRow][18] = new MonsterAdv("skeletor", 3, 20, 30, 2);
	board[skeletorRow][19] = new Unit(-2); // exit

	// initialising player position and skeletor position
	playerPos.push_back(playerRow);
	playerPos.push_back(0);
	skeletorPos.push_back(skeletorRow);
	skeletorPos.push_back(18);

	std::unordered_set<int> index;
	 
	// get indexs of other objects on the board
	// get 50 random integers and each of which corresponds to one position on the board
	while (index.size() < 50)
	{
		int tmp = rand() % 200 + 1;
		if ((tmp != 1 + playerRow * 20) && (tmp != (skeletorRow + 1) * 20) && (tmp != (skeletorRow + 1) * 20 - 1))
		{
			index.insert(tmp);
		}
	}

	auto i = index.begin();

	while (i != index.end()) // initialising other parts of the board
	{
		for (int j = 0; j < 10; j++)
		{
			setBoard(*i, "monsterFriend", "bugbear");
			i++;
		}
		for (int j = 10; j < 20; j++)
		{
			setBoard(*i, "monsterFriend", "platypie");
			i++;
		}
		for (int j = 20; j < 30; j++)
		{
			setBoard(*i, "monsterFriend", "emoo");
			i++;
		}
		for (int j = 30; j < 40; j++)
		{
			setBoard(*i, "monsterAttack", "octopod");
			i++;
		}
		for (int j = 40; j < 50; j++)
		{
			setBoard(*i, "item", "box");
			i++;
		}
	}
}

GameController::~GameController()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			delete board[i][j];
		}
	}
}

void GameController::setBoard(int index, std::string type, std::string name)
{
	/*
	type: friendly or attack. 
	Because these two types of monstes belong to the same class. We need some information to set the id number
	
	name: monster type
	*/
	
	if (index < 20)
	{
		int col = index - 1;
		int row = 0;
		if (type == "monsterFriend")
		{
			board[row][col] = new MonsterNorm(name, 1);
		}
		else if (type == "monsterAttack")
		{
			board[row][col] = new MonsterNorm(name, 2);
		}
		else
		{
			board[row][col] = new Box();
		}
	}
	else if (index % 20 == 0)  // index = 20 or 40 etc.
	{
		int col = 19;
		int row = (index / 20) - 1;
		if (type == "monsterFriend")
		{
			board[row][col] = new MonsterNorm(name, 1);
		}
		else if (type == "monsterAttack")
		{
			board[row][col] = new MonsterNorm(name, 2);
		}
		else
		{
			board[row][col] = new Box();
		}
	}
	else
	{
		int col = (index % 20) - 1;
		int row = index / 20;
		if (type == "monsterFriend")
		{
			board[row][col] = new MonsterNorm(name, 1);
		}
		else if (type == "monsterAttack")
		{
			board[row][col] = new MonsterNorm(name, 2);
		}
		else
		{
			board[row][col] = new Box();
		}
	}
}

void GameController::displayBoard(std::string mode)  // display board in a good format
{
	/*
	Because if I simply print the data member: board, the effect is not good, 
	I design such function to print a good-looking board onto screen.
	Basically, it uses a mathematical function to project each object on the original board to a new board.
	This function takes input of original position and outputs the corresponding position on the new board
	
	In test mode: each object is being printed
	
	In normal mode: only the position of player and positions where having been visited by him will be printed. 
	The visitied position is labeled a "*"
	*/
	
	if (mode == "test")
	{
		std::cout << "=====Game Board=====" << std::endl;
		for (int i = 0; i < 21; i++)
		{
			if (i % 2 != 0)
			{
				for (int j = 0; j < 41; j++)
				{
					if (j % 2 == 0)
					{
						std::cout << "|";
					}
					else
					{
						int col = 0.5 * j - 0.5;
						int row = 0.5 * i - 0.5;
						if (board[row][col]->getID() == 0)
						{
							std::cout << "P";  // player
						}
						else if (board[row][col]->getID() == 1)
						{
							std::cout << "M"; // friendly monster
						}
						else if (board[row][col]->getID() == 3)
						{
							std::cout << "B";  // skeletor monster
						}
						else if (board[row][col]->getID() == 5)
						{
							std::cout << "I";  // box
						}
						else if (board[row][col]->getID() == 2)
						{
							std::cout << "A";  // attack monster
						}
						else if (board[row][col]->getID() == -2)
						{
							std::cout << "E";  // exit
						}
						else
						{
							std::cout << " ";
						}
					}
					
				}
				std::cout << "\n";
			}
			else
			{
				for (int j = 0; j < 41; j++)
				{
					std::cout << "-";
				}
				std::cout << "\n";
			}
		}
	}
	else
	{
		std::cout << "=====Game Board=====" << std::endl;
		for (int i = 0; i < 21; i++)
		{
			if (i % 2 != 0)
			{
				for (int j = 0; j < 41; j++)
				{
					if (j % 2 == 0)
					{
						std::cout << "|";
					}
					else
					{
						int col = 0.5 * j - 0.5;
						int row = 0.5 * i - 0.5;
						if (board[row][col]->getID() == 0)
						{
							std::cout << "P"; // player
						}
						else if (board[row][col]->getID() == 4)
						{
							std::cout << "*"; // visited path
						}
						else
						{
							std::cout << " ";  // empty position
						}
					}

				}
				std::cout << "\n";
			}
			else
			{
				for (int j = 0; j < 41; j++)
				{
					std::cout << "-";
				}
				std::cout << "\n";
			}
		}
	}
}

std::vector<int> GameController::checkOp(std::string op)
{
	/*
	I designed this function beacuse we can use it to find the next position where player wants to move to.
	Also, by using this function, we can get the monster position and box position 
	because they are at the position where player wants to move
	*/
	std::vector<int> tmp;
	if (op == "w")
	{
		tmp.push_back(playerPos[0] - 1);
		tmp.push_back(playerPos[1]);
	}
	else if (op == "a")
	{
		tmp.push_back(playerPos[0]);
		tmp.push_back(playerPos[1] - 1);
	}
	else if (op == "s")
	{
		tmp.push_back(playerPos[0] + 1);
		tmp.push_back(playerPos[1]);
	}
	else
	{
		tmp.push_back(playerPos[0]);
		tmp.push_back(playerPos[1] + 1);
	}

	return tmp;
}

bool GameController::battle(std::string battleType, std::string op)
{
	/*
	This function handles the logic of battle.
	It contains three parts: with friendly monster, with attack monster and with sekeletor monster
	*/
	std::vector<int> tmp = checkOp(op);  // [row, col]

	if (battleType == "friendly")
	{
		std::cout << "\n===Battle Mode===" << "\nBattle Type: Capture this friendly monster" << std::endl;
		Player* tmp1 = static_cast<Player*> (board[playerPos[0]][playerPos[1]]);
		int pSkill = tmp1->getSkill("player") + rand() % 6 + 1;  // playe skill

		MonsterNorm* tmp2 = static_cast<MonsterNorm*> (board[tmp[0]][tmp[1]]);
		int mSkill = tmp2->getSkill();  // monster skill

		if (pSkill > mSkill)
		{
			std::cout << "You capture the monster\n" << tmp2->showMonster() << std::endl;
			tmp1->updateCollection(tmp2);
			move("player", op, tmp1);
			return false;
		}
		else
		{
			std::cout << "Capture failed: Monster escaped." << std::endl;
			std::string nextMove = moveable("monster", op);  // move escaped monster to a new position where it should be
			if (nextMove != "false")
			{
				move("monster", op, tmp1, tmp2, nextMove);
				move("player", op, tmp1);
			}
			else  // if monster has no where to goes, 
				  // then we keep everything the same, i.e. player doesn't move and monster doesn't move
			{
				return false;
			}			
			return false;
		}
	}
	else if (battleType == "attack")
	{
		std::cout << "\n===Battle Mode===" << "\nBattle Type: Fight with this unfriendly monster" << std::endl;

		Player* tmp1 = static_cast<Player*> (board[playerPos[0]][playerPos[1]]);
		MonsterNorm* tmp2 = static_cast<MonsterNorm*> (board[tmp[0]][tmp[1]]);

		while (tmp1->getHp("current", "player") != 0 && tmp2->getHp() != 0)  // while both of them are alive
		{
			int pSkill = tmp1->getSkill("player") + rand() % 6 + 1;
			int mSkill = tmp2->getSkill() + rand() % 6 + 1;

			if (pSkill < mSkill)
			{
				tmp1->addHp(-1, "player");
			}
			else
			{
				tmp2->addHp(-1);
			}
		}
		if (tmp1->getHp("current", "player") == 0)  // player died
		{
			return true;
		}
		else // monster died
		{
			std::cout << "Monster Died" << std::endl;
			delete board[tmp[0]][tmp[1]];  // delete attack monster
			move("player", op, tmp1);  // move player to new position
			return false;
		}

	}
	else  // fight with skeletor
	{
		std::cout << "=====Final Fight=====" << std::endl;
		Player* tmp1 = static_cast<Player*> (board[playerPos[0]][playerPos[1]]);
		MonsterAdv* tmp2 = static_cast<MonsterAdv*> (board[skeletorPos[0]][skeletorPos[1]]);

		while (tmp1->getHp("current", "evolved") != 0 && tmp2->getHp() != 0)
		{
			int pSkill = tmp1->getSkill("evolved") + rand() % 6 + 1;
			int mSkill = tmp2->getSkill() + rand() % 6 + 1;

			if (pSkill < mSkill)
			{
				tmp1->addHp(-1, "evolved");
			}
			else
			{
				tmp2->addHp(-1);
			}
		}
		if (tmp1->getHp("current", "player") == 0) // player died
		{
			return false;
		}
		else   // monster died
		{
			board[skeletorPos[0]][skeletorPos[1]] = new Unit();  // delete skeletor monster
			return true; 
		}
	}
}

std::string GameController::menuBar()
{
	std::stringstream ss;

	ss << "\n\n===Menu Bar==="
		<< "\n1. Move"
		<< "\n2. Display Player Info"
		<< "\n3. Display Bag Content"
		<< "\n4. Display Monster Collection"
		<< "\n5. Use item in bag"
		<< "\n6. Display Evolved Monster"
		<< "\n7. Exit current game";

	return ss.str();
}

bool GameController::move(std::string moveType, std::string op, Player* user, MonsterNorm* mon, std::string nextMove)
{
	/*
	This function moves objects on the board safely.
	Basically, it changes the original position's pointer pointing to Unit type oject, i.e. empty
	and makes Unit type pointer on the new position pointing to the moved object
	*/
	if (moveType == "player")
	{
		std::vector<int> tmp = checkOp(op);

		board[tmp[0]][tmp[1]] = user;
		board[playerPos[0]][playerPos[1]] = new Unit(4);  // marked as visited
		user = NULL;
		
		playerPos[0] = tmp[0];
		playerPos[1] = tmp[1];
		return true;
	}
	else  // move monster
	{
		std::vector<int> tmp = checkOp(op);  // monster original position
		if (nextMove == "w")
		{
			board[tmp[0] - 1][tmp[1]] = mon;
			board[tmp[0]][tmp[1]] = new Unit();
			mon = NULL;
			return true;
		}
		else if (nextMove == "a")
		{
			board[tmp[0]][tmp[1] - 1] = mon;
			board[tmp[0]][tmp[1]] = new Unit();
			mon = NULL;
			return true;
		}
		else if (nextMove == "s")
		{
			board[tmp[0] + 1][tmp[1]] = mon;
			board[tmp[0]][tmp[1]] = new Unit();
			mon = NULL;
			return true;
		}
		else  // op = d
		{
			board[tmp[0]][tmp[1] + 1] = mon;
			board[tmp[0]][tmp[1]] = new Unit();
			mon = NULL;
			return true;
		}
	}
}

std::string GameController::moveable(std::string moveObj, std::string op)
{
	/*
	This function 
	*/
	if (moveObj == "player")
	{
		std::vector<int> tmp = checkOp(op); // new position
		if (tmp[0] < 10 && tmp[0] > -1 && tmp[1] < 20 && tmp[1] > -1)
		{
			if (board[tmp[0]][tmp[1]]->getID() == -1 || board[tmp[0]][tmp[1]]->getID() == 4)  // empty
			{
				return "empty";
			}
			else if (board[tmp[0]][tmp[1]]->getID() == 5) // box
			{
				return "box";
			}
			else if (board[tmp[0]][tmp[1]]->getID() == 1)  // friendly monster
			{
				return "friendly";
			}
			else if (board[tmp[0]][tmp[1]]->getID() == 2)  // attack monster
			{
				return "attack";
			}
			else if (board[tmp[0]][tmp[1]]->getID() == 3 || board[tmp[0]][tmp[1]]->getID() == -2)  // id = 3, skeletor monster
			{           // found exit or skeletor. Even if user reaches the exit, because sekletor is not dead, they have to fight with it
				return "skeletor";
			}
		}
		else  // meet boundary of the board
		{
			return "false";
		}
	}
	else  // check if the escaped friendly monster can move to another position or not
	{
		std::vector<int> pos = checkOp(op);  // monster original position
		if (pos[0] + 1 < 10)
		{
			if (board[pos[0] + 1][pos[1]]->getID() == -1 || board[pos[0] + 1][pos[1]]->getID() == 4) // empty
			{
				return "s";
			}
		}
		
		if (pos[0] - 1 > -1)
		{
			if (board[pos[0] - 1][pos[1]]->getID() == -1 || board[pos[0] - 1][pos[1]]->getID() == 4)
			{
				return "w";
			}
		}
		
		if (pos[1] + 1 < 20)
		{
			if (board[pos[0]][pos[1] + 1]->getID() == -1 || board[pos[0]][pos[1] + 1]->getID() == 4)
			{
				return "d";
			}
		}
		
		if (pos[1] - 1 > -1)
		{
			if (board[pos[0]][pos[1] - 1]->getID() == -1 || board[pos[0]][pos[1] - 1]->getID() == 4)
			{
				return "a";
			}
		}
		else
		{
			return "false";
		}
	}
}

void GameController::playMode(std::string mode)
{
	if (mode == "test")
	{
		std::cout << "=====Test Mode=====" << std::endl;
	}
	else
	{
		std::cout << "=====Normal Mode=====" << std::endl;
	}

	bool userDie = false;
	bool skeletorDie = false; // two conditions used to check if we need to end the game. If userDie is true or if skeletorDie is true, we all need to end this game
	int comm = -1;
	while (userDie == false && skeletorDie == false && comm != 7)
	{
		displayBoard(mode);
		comm = -1;
		while (comm != 1 && comm != 7)
		{
			Player* user = static_cast<Player*>(board[playerPos[0]][playerPos[1]]);

			if (user->shouldEvolved() != "None")  // check if we need to join pu 5 monsters with the same type
			{
				std::cout << "You monster collection has five monsters which are the same type"
					<< "\nStarting to evolved" << std::endl;
				user->getEvolved(user->shouldEvolved());
			}
			
			std::cout << menuBar() << std::endl;
			comm = getNum("commend");
			if (comm == 1)
			{
				std::string op = getString("nextMove");
				std::string canMove = moveable("player", op);
				if (canMove != "false")  // if user meets the bound, then nothing happens
				{
					if (canMove == "empty")
					{
						move("player", op, user);
					}
					else if (canMove == "friendly" || canMove == "attack") // normal monster
					{
						std::cout << "\nYou encounter a monster  " << "Type: " << canMove << std::endl;
						userDie = battle(canMove, op);
					}
					else if (canMove == "box")  // get box
					{
						std::cout << "\nYou get a box" << std::endl;
						std::vector<int> tmp = checkOp(op);
						Box* item = static_cast<Box*> (board[tmp[0]][tmp[1]]);
						bool result = user->updateBag(item);

						if (result == false)
						{
							std::cout << "\nThe item in the box is a punishment, you lose one point of your hp" << std::endl;
							delete board[tmp[0]][tmp[1]];
						}

						board[tmp[0]][tmp[1]] = NULL;
						move("player", op, user);
					}
					else  // find skeltor
					{
						std::cout << "\nYou find the skeletor and exit is behind it" << std::endl;
						if (user->haveEvolved() == true)
						{
							skeletorDie = battle(canMove, op);
							if (skeletorDie == false)
							{
								userDie = true;
							}
						}
						else
						{
                            std::cout << "Because you don't have an evolved monster, you die" << std::endl;
							userDie = true;
						}
					}
				}
			}
			else if (comm == 2)  // display player info
			{
				std::cout << "===Display Player Info===" << std::endl;
				std::cout << user->showPlayer() << std::endl;
			}
			else if (comm == 3)  // display bag content
			{
				std::cout << "===Display Bag Content===" << std::endl;
				std::cout << user->showBag() << std::endl;
			}
			else if (comm == 4)  // display moster collection
			{
				std::cout << "===Display Monster Collections===" << std::endl;
				std::cout << user->showCollection() << std::endl;
			}
			else if (comm == 5)  // user wants to use item in bag
			{
				if (user->getBagSize() != 0)
				{
					std::cout << "---Which item in the bag do you want to use? ---" << std::endl;
					std::cout << user->showBag() << std::endl;
					int index = getNum("bagIndex", user->getBagSize());
					int itemType = user->getItemInfo(index);

					if (itemType == 1)   // item type: hp
					{
						std::cout << "Item Type: HP" << std::endl;
						if (user->haveEvolved() == true)
						{
							std::cout << "Do you want to use it on user or evolved monster? "
								<< "\n1. Player" << "\n2. Evolved Monster" << std::endl;
							int a = getNum("singleNum", -1, 1, 2);
							
							user->useBag(index, itemType, a);
						}
						else   // no evolved monster, player uses this hp
						{
							user->useBag(index, itemType, 1);
						}

						board[playerPos[0]][playerPos[1]] = user;
						user = NULL;
					}
					else  // item type: exp
					{
						std::cout << "Item Type: EXP" << std::endl;
						if (user->haveEvolved() == true)
						{
							std::cout << "Do you want to use it on user or evolved monster? "
								<< "\n1. Player" << "\n2. Monster" << std::endl;
							int a = getNum("singleNum", -1, 1, 2);

							std::cout << "Which attributes do you want to add skill points? "
								<< "\n1. Max Health" << "\n2. Skill" << std::endl;
							int b = getNum("singleNum", -1, 1, 2);

							user->useBag(index, itemType, a, b);
						}
						else  // user doesn't have evolved monster
						{
							std::cout << "Which attributes do you want to add skill points? "
								<< "\n1. Max Health" << "\n2. Skill" << std::endl;
							int b = getNum("singleNum", -1, 1, 2);

							user->useBag(index, itemType, 1, b);
						}

						board[playerPos[0]][playerPos[1]] = user;
					}
				}
				else
				{
					std::cout << "Empty Bag" << std::endl;
				}
			}
			else if (comm == 6)
			{
				std::cout << user->displayEvoleved() << std::endl;
			}
		}
	}

	std::cout << "\n===Final Result===" << std::endl;
	if (comm == 7)
	{
		std::cout << "User exit the current game" << std::endl;
	}
	else
	{
		if (skeletorDie == false && userDie == true)
		{
			std::cout << "Player failed to escape." << std::endl;
		}
		else
		{
			std::cout << "Player successfully escape the dungeon" << std::endl;
		}
	}
}


