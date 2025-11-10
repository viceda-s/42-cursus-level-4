//
// Created by viceda-s on 02/11/2025.
//

#include "ClapTrap.hpp"

// Default constructor
ClapTrap::ClapTrap() : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap " << this->_name << " has been created by default constructor!" << std::endl;
}

// Parameterized constructor
ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap " << this->_name << " has been created!" << std::endl;
}

// Copy constructor
ClapTrap::ClapTrap(const ClapTrap& other) {
    *this = other;
    std::cout << "ClapTrap " << this->_name << " has been created by copy!" << std::endl;
}

// Copy assignment operator
ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    std::cout << "ClapTrap " << this->_name << " copy assignment operator called!" << std::endl;
    return *this;
}

// Destructor
ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << this->_name << " has been destructed!" << std::endl;
}

// Member functions
void ClapTrap::attack(const std::string& target) {
    if (this->_energyPoints > 0 && this->_hitPoints > 0) {
        this->_energyPoints--;
        std::cout << "ClapTrap " << this->_name << " attacks " << target
                  << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
    } else {
        std::cout << "ClapTrap " << this->_name << " has no energy or hit points left to attack!" << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (this->_hitPoints > 0) {
        this->_hitPoints -= amount;
        if (this->_hitPoints < 0) {
            this->_hitPoints = 0;
        }
        std::cout << "ClapTrap " << this->_name << " takes " << amount
                  << " points of damage! Current hit points: " << this->_hitPoints << std::endl;
    } else {
        std::cout << "ClapTrap " << this->_name << " is already out of hit points!" << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->_energyPoints > 0 && this->_hitPoints > 0) {
        this->_energyPoints--;
        this->_hitPoints += amount;
        std::cout << "ClapTrap " << this->_name << " repairs itself for " << amount
                  << " hit points! Current hit points: " << this->_hitPoints << std::endl;
    } else {
        std::cout << "ClapTrap " << this->_name << " has no energy or hit points left to be repaired!" << std::endl;
    }
}