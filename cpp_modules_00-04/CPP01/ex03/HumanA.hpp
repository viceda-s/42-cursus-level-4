#ifndef HUMANA_HPP
#define HUMANA_HPP

#define RESET	"\033[0m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define CYAN	"\033[1;36m"

#include "Weapon.hpp"
#include <string>

class HumanA {
private:
	std::string name;
	Weapon& weapon;

public:
	HumanA(const std::string& name, Weapon& weapon);
	void attack() const;
};

#endif