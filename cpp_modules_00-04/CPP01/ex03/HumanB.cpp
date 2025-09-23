#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string& name) : name(name), weapon(NULL) {
}

void HumanB::setWeapon(Weapon& weapon) {
	this->weapon = &weapon;
}

void HumanB::attack() const {
	if (weapon) {
		std::cout << CYAN << name << RESET << " attacks with their " << GREEN << weapon->getType() << RESET << std::endl;
	} else {
		std::cout << CYAN << name << RESET << " attacks with " << RED << "no weapon" << RESET << std::endl;
	}
}