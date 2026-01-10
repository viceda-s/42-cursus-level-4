#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

#define RESET	"\033[0m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define CYAN	"\033[1;36m"

class HumanB {
private:
	std::string name;
	Weapon* weapon;

public:
	HumanB(const std::string& name);
	void setWeapon(Weapon& weapon);
	void attack() const;
};

#endif