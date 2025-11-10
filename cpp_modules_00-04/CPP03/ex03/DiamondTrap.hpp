//
// Created by Vicente Coelho on 02/11/2025.
//

#ifndef CPP03_DIAMONDTRAP_HPP
# define CPP03_DIAMONDTRAP_HPP


# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
private:
    std::string _name;

public:
    DiamondTrap();
    DiamondTrap(const std::string& _name);
    DiamondTrap(const DiamondTrap& other);
    DiamondTrap& operator=(const DiamondTrap& other);
    ~DiamondTrap();

    void attack(const std::string& target);
    void whoAmI();
};

#endif //CPP03_DIAMONDTRAP_HPP