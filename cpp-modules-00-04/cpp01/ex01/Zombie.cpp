#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() {
}

Zombie::~Zombie() {
	std::cout << name << " has been destroyed!" << std::endl;
}

void Zombie::announce( void ) {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." <<std::endl;
}

void Zombie::setName(std::string name) {
	this->name = name;
	std::cout << this->name << " has been created!" << std::endl;
}
