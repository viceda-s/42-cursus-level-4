//
// Created by viceda-s on 02/11/2025.
//

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap " << this->_name << " has been constructed!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    std::cout << "ScavTrap Copy constructor called" << std::endl;
    *this = other;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    std::cout << "ScavTrap Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return *this;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << this->_name << " has been destructed!" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (this->_energyPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " has no energy points to attack!" << std::endl;
        return;
    }
    if (this->_hitPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " has no hit points to attack!" << std::endl;
        return;
    }
    this->_energyPoints--;
    std::cout << "ScavTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode." << std::endl;
}
