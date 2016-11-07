#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include "UtilityFunctions.h"
#include "Unit.h"
#include "Player.h"

class GameController
{
	/*
	This function is an interface of main control of this game
	It has a board which visualizing this game and two vectors for recording player's position
	and skeletor's position for the sake of convenience
	*/
private:
	std::vector<std::vector<Unit*>> board;
	std::vector<int> playerPos;
	std::vector<int> skeletorPos;

public:
	GameController::GameController();
	~GameController();
	void displayBoard(std::string mode);
	void setBoard(int index, std::string type, std::string name);  // used in constructor to set the board data member
	bool battle(std::string battleType, std::string op);
	std::vector<int> checkOp(std::string op);  // returns player's next position
	std::string menuBar();
	bool move(std::string moveType, std::string op, Player* user = NULL, MonsterNorm* mon = NULL, std::string nextMove = "");  // move player and monster on the board
	std::string moveable(std::string moveObj, std::string op = "");  // check if there is empty position around object, i.e. friendly monster or player
	void playMode(std::string mode);  // main function of playing this game
	void useBagItem();  // use item in player's bag
};

#endif