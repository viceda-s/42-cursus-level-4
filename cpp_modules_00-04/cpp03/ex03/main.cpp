//
// Created by Vicente Coelho on 02/11/2025.
//

#include "DiamondTrap.hpp"

int main() {
    // Test construction and whoAmI call
    std::cout << "--- Creating DiamondTrap ---" << std::endl;
    DiamondTrap diamond("D14M-TP");
    std::cout << std::endl;
    diamond.whoAmI();
    std::cout << std::endl;

    // Test inherited functions
    std::cout << "--- Testing inherited functions ---" << std::endl;
    diamond.attack("some poor soul");
    diamond.takeDamage(25);
    diamond.beRepaired(10);
    std::cout << std::endl;

    // Test special abilities
    std::cout << "--- Testing special abilities ---" << std::endl;
    diamond.guardGate();
    diamond.highFivesGuys();
    std::cout << std::endl;

    // Test the object's state
    std::cout << "--- Final Stats ---" << std::endl;
    std::cout << "Name: " << diamond.getName() << std::endl;
    std::cout << "Hit Points: " << diamond.getHitPoints() << std::endl;
    std::cout << "Energy Points: " << diamond.getEnergyPoints() << std::endl;
    std::cout << "Attack Damage: " << diamond.getAttackDamage() << std::endl;
    std::cout << std::endl;

    // Test destruction
    std::cout << "--- Destroying DiamondTrap ---" << std::endl;
    return 0;
}