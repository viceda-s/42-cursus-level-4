#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(const std::string& name, Weapon& weapon) : name(name), weapon(weapon) {
}

void HumanA::attack() const {
	std::cout << CYAN << name << RESET << " attacks with their " << GREEN << weapon.getType() << RESET << std::endl;
}