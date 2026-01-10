#include <iostream>

#define BOLD	"\033[1m"
#define GREEN	"\033[1;32m"
#define RESET	"\033[0m"

int main() {
	std::string brain = "HI THIS IS BRAIN";
	std::string* brainPTR = &brain;
	std::string& brainREF = brain;

	std::cout << std::endl;
	std::cout << GREEN << "Memory addresses:" << RESET << std::endl;
	std::cout << GREEN << "Variable: " << RESET << BOLD << &brain << RESET << std::endl;
	std::cout << GREEN << "Pointer: " <<  RESET << BOLD  << brainPTR << RESET << std::endl;
	std::cout << GREEN << "Reference: " <<  RESET << BOLD  << &brainREF << RESET << std::endl;


	std::cout << std::endl;
	std::cout << GREEN << "Values:" << RESET << std::endl;
	std::cout << GREEN << "Variable: " << RESET << BOLD << brain << RESET << std::endl;
	std::cout << GREEN << "Pointer: " <<  RESET << BOLD  << *brainPTR << RESET << std::endl;
	std::cout << GREEN << "Reference: " <<  RESET << BOLD  << brainREF << RESET << std::endl;

	return 0;
}
