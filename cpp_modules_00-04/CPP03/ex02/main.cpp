//
// Created by Vicente Coelho on 02/11/2025.
//

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "--- ClapTrap Test ---" << std::endl;
    ClapTrap claptrap("CL4P-TP");
    claptrap.attack("Bandit");
    claptrap.takeDamage(5);
    claptrap.beRepaired(3);
    std::cout << std::endl;

    std::cout << "--- ScavTrap Test ---" << std::endl;
    ScavTrap scavtrap("SC4V-TP");
    scavtrap.attack("Another Bandit");
    scavtrap.takeDamage(30);
    scavtrap.beRepaired(20);
    scavtrap.guardGate();
    std::cout << std::endl;

    std::cout << "--- FragTrap Test ---" << std::endl;
    FragTrap fragtrap("FR4G-TP");
    fragtrap.attack("Boss");
    fragtrap.takeDamage(50);
    fragtrap.beRepaired(40);
    fragtrap.highFivesGuys();
    std::cout << std::endl;

    std::cout << "--- Destruction ---" << std::endl;
    return 0;
}