#include "Zombie.hpp"
#include <iostream>

int main() {
	int hordeSize = 5;
	std::string zombieName = "Walker";


	std::cout << YELLOW << "Creating the horde..." << RESET << std::endl;
	Zombie* horde = zombieHorde(hordeSize, zombieName);
	std::cout << GREEN << "A horde of " << hordeSize << " zombies named " << zombieName << " has been created!" << RESET << std::endl;

	if (horde == NULL) {
		std::cout << YELLOW << "Failed to create a zombie horde!" << RESET << std::endl;
		return 1;
	}

	std::cout << std::endl;
	std::cout << YELLOW << "=== Testing horde of zombies ===" << RESET << std::endl;
	for (int i = 0; i < hordeSize; i++) {
		std::cout << "Zombie " << i << ": ";
		horde[i].announce();
	}

	std::cout << std::endl;
	std::cout << YELLOW << "Destroying the horde..." << RESET << std::endl;
	delete[] horde;
	std::cout << RED << "The horde has been destroyed!" << RESET << std::endl;

	return 0;
}
