#include "PhoneBook.hpp"

int main() {
	PhoneBook phoneBook;
	std::string command;

	std::cout << "=== Welcome to My Awesome PhoneBook ===" << std::endl;
	std::cout << "Available commands: ADD, SEARCH or EXIT" << std::endl;

	while (true) {
		std::cout << "\nEnter command: ";
		std::getline(std::cin, command);

		if (std::cin.eof()) {
			std::cout << std::endl;
			break;
		}

		if (command == "ADD") {
			phoneBook.addContact();
		} else if (command == "SEARCH"){
			phoneBook.searchContact();
		} else if (command == "EXIT") {
			std::cout << "Beijo na bunda... e até segunda!" << std::endl;
			break;
		} else if (!command.empty()) {
			std::cout << "invalid command!" << std::endl;
		}

	}

	return 0;
}
