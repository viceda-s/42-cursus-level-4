//
// Created by Vicente Coelho on 02/11/2025.
//

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>
# include <iostream>

class ClapTrap {

private:
    std::string     _name;
    int             _hitPoints;
    int             _energyPoints;
    int             _attackDamage;

public:
    // Orthodox Canonical Form
    ClapTrap();
    ClapTrap(std::string name);
    ClapTrap(const ClapTrap& other);
    ClapTrap& operator=(const ClapTrap& other);
    ~ClapTrap();

    // Member functions
    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

};

#endif