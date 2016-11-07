#include <iostream>
#include <string>
#include "Box.h"
#include "Unit.h"
#include "MonsterNorm.h"
#include "MonsterAdv.h"
#include "Player.h"
#include "GameController.h"

using namespace std;
int main()
{
	srand(time(NULL));
	std::cout << "=====Game: Monster Evolution=====" << std::endl;

	std::string modeSelect = getString("mode");
	while (modeSelect != "exit")
	{
		GameController test;
		test.playMode(modeSelect);
		modeSelect = getString("mode");
	}

	std::cout << "\n=====Exit Game=====" << std::endl;


	system("pause");
	return 0;
}