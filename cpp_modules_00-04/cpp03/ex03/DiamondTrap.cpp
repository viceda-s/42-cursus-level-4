//
// Created by Vicente Coelho on 02/11/2025.
//

#include "DiamondTrap.hpp"
#include <iostream>

// Default constructor
// Initializes the DiamondTrap with default values.
// It calls the constructors of the base classes.
DiamondTrap::DiamondTrap() : ClapTrap("Default_clap_name"), ScavTrap(), FragTrap() {
	this->_name = "Default";
	this->_hitPoints = FragTrap::_hitPoints;
	this->_energyPoints = ScavTrap::_energyPoints;
	this->_attackDamage = FragTrap::_attackDamage;
	std::cout << "DiamondTrap Default constructor called" << std::endl;
}

// Parameterized constructor
// Initializes the DiamondTrap with a specific name.
// The ClapTrap subobject is named `name + "_clap_name"`.
// Attributes are set based on FragTrap and ScavTrap specifications.
DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name) {
	this->_name = name;
	this->_hitPoints = FragTrap::_hitPoints;
	this->_energyPoints = ScavTrap::_energyPoints;
	this->_attackDamage = FragTrap::_attackDamage;
	std::cout << "DiamondTrap " << this->_name << " constructor called" << std::endl;
}

// Copy constructor
// Creates a copy of another DiamondTrap object.
DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), ScavTrap(other), FragTrap(other) {
	*this = other;
	std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

// Destructor
// Cleans up the object when it's destroyed.
DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap " << this->_name << " destructor called" << std::endl;
}

// Assignment operator overload
// Assigns the values of one DiamondTrap object to another.
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
	std::cout << "DiamondTrap Assignation operator called" << std::endl;
	if (this != &other) {
		this->_name = other._name;
		this->ClapTrap::_name = other.ClapTrap::_name;
		this->_hitPoints = other._hitPoints;
		this->_energyPoints = other._energyPoints;
		this->_attackDamage = other._attackDamage;
	}
	return *this;
}

// whoAmI function
// Displays the DiamondTrap's name and its ClapTrap subobject's name.
void DiamondTrap::whoAmI() {
	std::cout << "I am a DiamondTrap named " << this->_name
			  << " and my ClapTrap name is " << ClapTrap::_name << std::endl;
}

// attack function
// Overrides the base attack and uses ScavTrap's version.
void DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}