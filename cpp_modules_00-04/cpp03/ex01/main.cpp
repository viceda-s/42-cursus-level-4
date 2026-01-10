#include "ScavTrap.hpp"

int main() {
    ScavTrap st1("ST-One");
    ScavTrap st2(st1);

    st1.attack("ST-Two");
    st2.takeDamage(20);
    st2.beRepaired(10);
    st2.guardGate();

    return 0;
}
