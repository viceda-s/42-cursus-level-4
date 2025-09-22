#include "Zombie.hpp"
#include <iostream>

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main() {
	std::cout << std::endl;
	std::cout << YELLOW << "=== Testing heap allocation ===" << RESET << std::endl;
	Zombie* heapZombie = newZombie("HeapZombie");
	heapZombie->announce();
	delete heapZombie;

	std::cout << std::endl;
	std::cout << YELLOW << "=== Testing stack allocation ===" << RESET << std::endl;
	randomChump("StackZombie");
	std::cout << std::endl;

	return 0;
}
