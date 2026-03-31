#include "Harl.hpp"
#include <iostream>

void Harl::debug(void) {
	std::cout << ITALIC << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << RESET << std::endl;
	return;
}

void Harl::info(void) {
	std::cout << ITALIC << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn't be asking for more!" << RESET << std::endl;
	return;
}

void Harl::warning(void) {
	std::cout << ITALIC << "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month." << RESET << std::endl;
	return;
}

void Harl::error(void){
	std::cout << ITALIC << "This is unacceptable! I want to speak to the manager now." << RESET << std::endl;
	return;
}

void Harl::complain(std::string level) {
	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void (Harl::*functions[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

	for (int i = 0; i < 4; i++) {
		if (levels[i] == level) {
			(this->*functions[i])();
			return;
		}
	}
	std::cout << RED << "Invalid level: " << RESET << ITALIC << level << RESET << std::endl;
}