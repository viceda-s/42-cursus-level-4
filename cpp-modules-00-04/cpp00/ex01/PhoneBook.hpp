#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

class PhoneBook
{
private:
	Contact _contacts[8];
	int _currentIndex;
	int _totalContacts;

	std::string _truncateText(const std::string& text) const;
	void _displayContactRow(int index, const Contact& contact) const;
	std::string _getInput(const std::string& prompt) const;
	bool _isValidIndex(const std::string& input, int& index) const;

public:
	PhoneBook();
	~PhoneBook();

	void addContact();
	void searchContact() const;
	void displayHeader() const;
};

#endif