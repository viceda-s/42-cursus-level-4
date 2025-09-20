#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _currentIndex(0), _totalContacts(0) {
}

PhoneBook::~PhoneBook() {
}

std::string PhoneBook::_truncateText(const std::string& text) const {
	if (text.length() > 10)
		return text.substr(0, 9) + ".";
	return text;
}

void PhoneBook::_displayContactRow(int index, const Contact& contact) const {
	std::cout << "|" << std::setw(10) << index << "|";
	std::cout << std::setw(10) << _truncateText(contact.getFirstName()) << "|";
	std::cout << std::setw(10) << _truncateText(contact.getLastName()) << "|";
	std::cout << std::setw(10) << _truncateText(contact.getNickname()) << "|" << std::endl;
}

std::string PhoneBook::_getInput(const std::string& prompt) const {
	std::string input;

	while (true) {
		std::cout << prompt;
		std::getline(std::cin, input);

		if (std::cin.eof()) {
			std::cout << std::endl;;
			exit(0);
		}

		if (!input.empty())
			break;

		std::cout << "A saved contact can't have empty fields." << std::endl;
	}

	return input;
}

bool PhoneBook::_isValidIndex(const std::string& input, int& index) const {
	if (input.length() != 1 || !std::isdigit(input[0]))
		return false;

	index = input[0] - '0';
	return (index >= 0 && index < _totalContacts && index < 8);
}

void PhoneBook::addContact() {
	Contact newContact;

	std::cout << "\n=== Adding New Contact ===" << std::endl;

	newContact.setFirstName(_getInput("First name: "));
	newContact.setLastName(_getInput("Last name: "));
	newContact.setNickname(_getInput("Nickname: "));
	newContact.setPhoneNumber(_getInput("Phone number: "));
	newContact.setDarkestSecret(_getInput("Darkest secret: "));

	_contacts[_currentIndex] = newContact;
	_currentIndex = (_currentIndex + 1) % 8;

	if (_totalContacts < 8)
		_totalContacts++;

	std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const {
	if (_totalContacts == 0) {
		std::cout << "PhoneBook empty" << std::endl;
		return;
	}

	std::cout << "\n=== Contact List ===" << std::endl;
	displayHeader();

	for (int i = 0; i < _totalContacts; i++) {
		_displayContactRow(i, _contacts[i]);
	}

	std::string input;
	int index;

	std::cout << "\nEnter index to display: ";
	std::getline(std::cin, input);

	if (std::cin.eof()) {
		std::cout << std::endl;
		exit(0);
	}

	if (!_isValidIndex(input, index)) {
		std::cout << "Invalid index" << std::endl;
		return;
	}

	const Contact& contact = _contacts[index];

	std::cout << "\n=== Contact details ===" << std::endl;
	std::cout << "First name: " << contact.getFirstName() << std::endl;
	std::cout << "Last name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone nuumber: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << contact.getDarkestSecret() << std::endl;
}

void PhoneBook::displayHeader() const {
	std::cout << "|" << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
	std::cout << "|----------|----------|----------|----------" << std::endl;
}