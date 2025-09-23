#include "Harl.hpp"
#include <iostream>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << YELLOW << "⚠️  Usage: ./harlFilter <level>" << RESET << std::endl;
		return 1;
	}

	Harl harl;
	std::string level = av[1];
	int lvlIndex = -1;

	if (level == "DEBUG") lvlIndex = 0;
	else if (level == "INFO") lvlIndex = 1;
	else if (level == "WARNING") lvlIndex = 2;
	else if (level == "ERROR") lvlIndex = 3;

	switch (lvlIndex) {
		case 0:
			std::cout << GREEN << "[ DEBUG ]" << RESET << std::endl;
			harl.complain("DEBUG");
			std::cout << std::endl;
			// fall through
		case 1:
			std::cout << BLUE << "[ INFO ]" << RESET << std::endl;
			harl.complain("INFO");
			std::cout << std::endl;
			// fall through
		case 2:
			std::cout << YELLOW << "[ WARNING ]" << RESET << std::endl;
			harl.complain("WARNING");
			std::cout << std::endl;
			// fall through
		case 3:
			std::cout << RED << "[ ERROR ]" << RESET << std::endl;
			harl.complain("ERROR");
			std::cout << std::endl;
			break;
		default:
			std::cout << ITALIC << "[ Probably complaining about insignificant problems ]" << RESET << std::endl;
			break;
	}

	return 0;
}