#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : name(name) {
	std::cout << GREEN << name << " has been created!" << RESET << std::endl;
}

Zombie::~Zombie() {
	std::cout << RED << name << " has been destroyed!" << RESET << std::endl;
}

void Zombie::announce( void ) {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." <<std::endl;
}
