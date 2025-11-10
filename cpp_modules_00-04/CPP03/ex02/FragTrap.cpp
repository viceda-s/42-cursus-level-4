//
// Created by viceda-s on 02/11/2025.
//

#include "FragTrap.hpp"

// Default constructor
FragTrap::FragTrap() : ClapTrap() {
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap Default constructor called" << std::endl;
}

// Parameterized constructor
FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap " << this->_name << " has been created!" << std::endl;
}

// Copy constructor
FragTrap::FragTrap(const FragTrap& other) {
    std::cout << "FragTrap copy constructor called" << std::endl;
    *this = other;
}

// Copy assignment operator
FragTrap& FragTrap::operator=(const FragTrap& other) {
    std::cout << "FragTrap copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return *this;
}

// Destructor
FragTrap::~FragTrap() {
    std::cout << "FragTrap " << this->_name << " has been destructed!" << std::endl;
}

// Special habilities
void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << this->_name << " high fives guys!" << std::endl;
}