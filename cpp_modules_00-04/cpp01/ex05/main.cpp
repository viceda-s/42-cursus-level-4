#include "Harl.hpp"
#include <iostream>

int main() {
	Harl harl;

	std::cout << YELLOW << "Harl's complaints 🤬:" << RESET << std::endl;

	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");

	std::cout << YELLOW << "\nTesting invalid level:" << RESET << std::endl;
	harl.complain("INVALID");

	return 0;
}