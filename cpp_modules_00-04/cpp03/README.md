# CPP Module 03

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 03 introduces inheritance in C++, one of the core principles of object-oriented programming. This module focuses on understanding class hierarchies, the protected access specifier, and how derived classes can extend base class functionality. The exercises progressively build a hierarchy of robot classes inspired by the Borderlands game series:

- **Exercise 00 - Aaaaand... OPEN!**: Creating the base ClapTrap class with basic robot functionality.
- **Exercise 01 - Serena, my love!**: Creating ScavTrap, a derived class that inherits from ClapTrap with additional features.
- **Exercise 02 - Repetitive work**: Creating FragTrap, another derived class with different specializations.
- **Exercise 03 - Now it's weird!**: Creating DiamondTrap, demonstrating multiple inheritance and the diamond problem.

The main goals of this module are:
- Understanding class inheritance
- Learning about protected members
- Mastering constructors and destructors in inheritance hierarchies
- Understanding virtual inheritance and the diamond problem
- Implementing method overriding

## Instructions

### Compilation

Each exercise has its own directory with a Makefile. To compile an exercise:

```bash
# Navigate to the exercise directory
cd ex00  # or ex01, ex02, ex03

# Compile the program
make

# Run the executable
./claptrap     # ex00
./scavtrap     # ex01
./fragtrap     # ex02
./diamondtrap  # ex03

# Clean object files
make clean

# Clean all generated files
make fclean

# Recompile from scratch
make re
```

### Requirements

- **Compiler**: C++ compiler with C++98 standard support (g++, clang++)
- **Compilation flags**: `-Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-shadow`
- **Operating System**: Linux, macOS, or WSL (Windows Subsystem for Linux)

### Project Structure

```
CPP03/
├── ex00/           # ClapTrap - base class
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   ├── main.cpp
│   └── Makefile
├── ex01/           # ScavTrap - first derived class
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   ├── ScavTrap.cpp
│   ├── ScavTrap.hpp
│   ├── main.cpp
│   └── Makefile
├── ex02/           # FragTrap - second derived class
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   ├── ScavTrap.cpp
│   ├── ScavTrap.hpp
│   ├── FragTrap.cpp
│   ├── FragTrap.hpp
│   ├── main.cpp
│   └── Makefile
├── ex03/           # DiamondTrap - multiple inheritance
│   ├── ClapTrap.cpp
│   ├── ClapTrap.hpp
│   ├── ScavTrap.cpp
│   ├── ScavTrap.hpp
│   ├── FragTrap.cpp
│   ├── FragTrap.hpp
│   ├── DiamondTrap.cpp
│   ├── DiamondTrap.hpp
│   ├── main.cpp
│   └── Makefile
└── README.md
```

## Usage Examples

### Exercise 00 - ClapTrap

```cpp
ClapTrap clap("CL4P-TP");
clap.attack("target");
clap.takeDamage(5);
clap.beRepaired(3);
```

### Exercise 01 - ScavTrap

```cpp
ScavTrap scav("SC4V-TP");
scav.attack("enemy");
scav.takeDamage(20);
scav.beRepaired(15);
scav.guardGate();  // Special ScavTrap ability
```

### Exercise 02 - FragTrap

```cpp
FragTrap frag("FR4G-TP");
frag.attack("target");
frag.takeDamage(30);
frag.beRepaired(20);
frag.highFivesGuys();  // Special FragTrap ability
```

### Exercise 03 - DiamondTrap

```cpp
DiamondTrap diamond("DI4M-TP");
diamond.attack("enemy");      // Uses ScavTrap's attack
diamond.whoAmI();             // Shows both names
diamond.guardGate();          // ScavTrap ability
diamond.highFivesGuys();      // FragTrap ability
```

## Technical Choices

- **C++98 Standard**: The project strictly adheres to the C++98 standard as required by the 42 curriculum.
- **Protected Members**: Using protected access for members that need to be accessible in derived classes.
- **Constructor/Destructor Chain**: Proper initialization and cleanup order in inheritance hierarchies.
- **Virtual Inheritance**: Used in ex03 to solve the diamond problem.
- **Method Overriding**: Derived classes can override base class methods.

## Resources

### Official Documentation
- [C++ Inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- [C++ Access Specifiers](https://en.cppreference.com/w/cpp/language/access)
- [C++ Virtual Inheritance](https://en.cppreference.com/w/cpp/language/derived_class#Virtual_base_classes)
- [Multiple Inheritance](https://en.cppreference.com/w/cpp/language/derived_class#Multiple_inheritance)

### Articles and Tutorials
- [Inheritance in C++](https://www.geeksforgeeks.org/inheritance-in-c/)
- [Protected Members Explained](https://www.learncpp.com/cpp-tutorial/protected-members/)
- [The Diamond Problem](https://www.geeksforgeeks.org/multiple-inheritance-in-c/)
- [Virtual Inheritance](https://www.learncpp.com/cpp-tutorial/virtual-base-classes/)

### Books
- "Effective C++" by Scott Meyers
- "C++ Primer" by Stanley Lippman
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used for the following purposes:

1. **Inheritance Syntax**: Understanding the correct syntax for class derivation.
2. **Diamond Problem**: Learning about virtual inheritance and how it solves the diamond problem.
3. **Constructor Chaining**: Understanding the order of constructor/destructor calls in hierarchies.
4. **Readme Creation**: Structuring and formatting this README file according to the requirements.

**Important Note**: All core logic, class hierarchies, method implementations, and design decisions were made independently. AI was used as a reference tool, similar to consulting documentation or textbooks, but the actual implementation and understanding of concepts are original work.

## Key Concepts Covered

- **Inheritance**: Creating derived classes from base classes
- **Protected Members**: Understanding protected access specifier
- **Constructor/Destructor Order**: Initialization and cleanup in inheritance
- **Method Overriding**: Redefining base class methods in derived classes
- **Multiple Inheritance**: Inheriting from multiple base classes
- **Virtual Inheritance**: Solving the diamond problem
- **IS-A Relationship**: Understanding when to use inheritance
- **Code Reuse**: Leveraging base class functionality

## Learning Outcomes

By completing this module, you will:
- Master class inheritance in C++
- Understand the three access specifiers (public, protected, private)
- Learn proper constructor/destructor chaining
- Understand method overriding and when to use it
- Learn about multiple inheritance and its pitfalls
- Understand virtual inheritance and the diamond problem
- Develop skills in designing class hierarchies
- Learn to choose between inheritance and composition

---

*For any questions or issues regarding this project, please refer to the 42 curriculum documentation or contact the project author.*

