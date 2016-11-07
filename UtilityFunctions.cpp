#include "UtilityFunctions.h"

std::string getString(std::string strType)
{
	if (strType == "nextMove")
	{
		std::string move;

		while (std::cout << "\nInput w/ a/ s/ d Only"
			<< "\nYour Choice: " &&
			(!(std::cin >> move) || !(move == "w" || move == "a" || move == "s" || move == "d")))
		{
			std::cout << "\nInvalid Input"
				<< "\nEnter w/ a/ s/ d Only" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return move;
	}

	else if (strType == "name")
	{
		std::string pName;

		while (std::cout << "\nEnter user name: "
			&& !(std::cin >> pName))
		{
			std::cout << "\nInvalid Input" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		return pName;
	}

	else if (strType == "mode")
	{
		std::string mode;

		while (std::cout << "\nMode Selection: Input normal/ test/ exit Only"
			<< "\nYour Choice: " &&
			(!(std::cin >> mode) || !(mode == "normal" || mode == "test" || mode == "exit")))
		{
			std::cout << "\nInvalid Input"
				<< "\nInput normal/ test/ exit Only" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return mode;
	}
}

int getNum(std::string numType, int len, int min, int max)
{
	if (numType == "commend")
	{
		int comm;

		while (std::cout << "Enter commend: " && (!(std::cin >> comm) || comm > 7 || comm < 1))
		{
			std::cout << "\nInvalid Input"
				<< "\nInteger ranged from 1 to 6 only" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	    
		return comm;
	}
	else if (numType == "bagIndex")
	{
		int index;
		while (std::cout << "Enter the index of the item you want to use: " 
			&& (!(std::cin >> index) || index < 0 || index >= len))
		{
			std::cout << "\nInvalid Input"
				<< "\nIndex out of range" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return index;
	}
	else if (numType == "singleNum")
	{
		int option;
		while (std::cout << "Enter the index of the option you want to choose: "
			&& (!(std::cin >> option) || option < min || option > max))
		{
			std::cout << "\nInvalid Input" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return option;
	
	}


}
