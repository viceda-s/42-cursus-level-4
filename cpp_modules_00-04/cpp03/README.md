# CPP Module 03

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 03 focuses on **inheritance** in C++, one of the fundamental pillars of object-oriented programming. This module explores class hierarchies, derived classes, and how C++ handles inheritance mechanics. The project uses a game-like scenario with robot characters (ClapTrap, ScavTrap, FragTrap, and DiamondTrap) to demonstrate inheritance concepts.

The project is divided into four exercises:

- **Exercise 00 (ClapTrap)**: Implementation of a base ClapTrap class with basic combat mechanics
- **Exercise 01 (ScavTrap)**: Creating a derived class that inherits from ClapTrap with modified behavior
- **Exercise 02 (FragTrap)**: Another derived class with different characteristics
- **Exercise 03 (DiamondTrap)**: Exploring multiple inheritance and the diamond problem

### Learning Objectives

- Understanding inheritance and derived classes
- Learning about protected members and access control
- Mastering the base class constructor initialization
- Exploring multiple inheritance and virtual inheritance
- Understanding the diamond problem and its resolution
- Implementing derived class behavior modifications

## Instructions

### Compilation Requirements

- **Compiler**: `c++` (or `g++`, `clang++`)
- **Standard**: C++98
- **Flags**: `-Wall -Wextra -Werror -std=c++98`

### Compilation

Each exercise has its own Makefile. Navigate to the desired exercise directory and run:

```bash
make
```

This will compile the exercise and create an executable.

#### Exercise 00 - ClapTrap
```bash
cd ex00
make
./ClapTrap
```

#### Exercise 01 - ScavTrap
```bash
cd ex01
make
./ScavTrap
```

#### Exercise 02 - FragTrap
```bash
cd ex02
make
./FragTrap
```

#### Exercise 03 - DiamondTrap
```bash
cd ex03
make
./DiamondTrap
```

### Cleaning

To remove object files:
```bash
make clean
```

To remove object files and executable:
```bash
make fclean
```

To recompile everything:
```bash
make re
```

## Project Structure

```
CPP03/
├── ex00/                    # Base class implementation
│   ├── ClapTrap.hpp        # ClapTrap class declaration
│   ├── ClapTrap.cpp        # ClapTrap class implementation
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex01/                    # Single inheritance
│   ├── ClapTrap.hpp        # Base class
│   ├── ClapTrap.cpp
│   ├── ScavTrap.hpp        # Derived class
│   ├── ScavTrap.cpp
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex02/                    # Another derived class
│   ├── ClapTrap.hpp        # Base class
│   ├── ClapTrap.cpp
│   ├── ScavTrap.hpp        # First derived class
│   ├── ScavTrap.cpp
│   ├── FragTrap.hpp        # Second derived class
│   ├── FragTrap.cpp
│   ├── main.cpp            # Test program
│   └── Makefile
└── ex03/                    # Multiple inheritance
    ├── ClapTrap.hpp        # Base class
    ├── ClapTrap.cpp
    ├── ScavTrap.hpp        # First derived class
    ├── ScavTrap.cpp
    ├── FragTrap.hpp        # Second derived class
    ├── FragTrap.cpp
    ├── DiamondTrap.hpp     # Multiple inheritance class
    ├── DiamondTrap.cpp
    ├── main.cpp            # Test program
    └── Makefile
```

## Features

### Exercise 00: ClapTrap Base Class

Implements a basic robot class with:
- **Attributes**: Name, Hit Points, Energy Points, Attack Damage
- **Member Functions**:
  - `attack(const std::string& target)`: Attacks a target (costs energy)
  - `takeDamage(unsigned int amount)`: Reduces hit points
  - `beRepaired(unsigned int amount)`: Restores hit points (costs energy)
- **Orthodox Canonical Form**: Default constructor, copy constructor, assignment operator, destructor
- **Initial Values**: 10 hit points, 10 energy points, 0 attack damage

### Exercise 01: ScavTrap (Single Inheritance)

ScavTrap inherits from ClapTrap with:
- **Modified Attributes**: 100 hit points, 50 energy points, 20 attack damage
- **Special Ability**: `guardGate()` - Announces Gate keeper mode
- **Constructor/Destructor Messages**: Custom messages for ScavTrap
- **Inherited Behavior**: Uses ClapTrap's basic functions with ScavTrap's attributes

**Key Concepts**:
- Derived class initialization using base class constructor
- Protected members for derived class access
- Overriding behavior while maintaining the interface

### Exercise 02: FragTrap (Another Derived Class)

FragTrap also inherits from ClapTrap with:
- **Modified Attributes**: 100 hit points, 100 energy points, 30 attack damage
- **Special Ability**: `highFivesGuys()` - Requests high fives
- **Constructor/Destructor Messages**: Custom messages for FragTrap
- **Demonstrates**: Multiple different classes can inherit from the same base

### Exercise 03: DiamondTrap (Multiple Inheritance)

DiamondTrap inherits from both ScavTrap and FragTrap:
- **The Diamond Problem**: Both parents inherit from ClapTrap, creating a diamond-shaped hierarchy
- **Virtual Inheritance**: Uses virtual inheritance to solve the diamond problem
- **Attribute Mix**: Combines attributes from both parents
  - Hit points from FragTrap (100)
  - Energy points from ScavTrap (50)
  - Attack damage from FragTrap (30)
- **Special Ability**: `whoAmI()` - Displays both DiamondTrap and ClapTrap names
- **Name Handling**: DiamondTrap has its own name, while ClapTrap name is derived (name + "_clap_name")

## Algorithm and Data Structure Explanation

### Inheritance in C++

Inheritance allows creating new classes based on existing classes, promoting code reuse and establishing hierarchical relationships.

#### Single Inheritance

```cpp
class ScavTrap : public ClapTrap {
    // ScavTrap inherits all members from ClapTrap
};
```

**How it works**:
- ScavTrap has access to ClapTrap's public and protected members
- ScavTrap can override ClapTrap's member functions
- ScavTrap objects contain all data members of both ScavTrap and ClapTrap
- Constructor chain: ScavTrap constructor calls ClapTrap constructor first

#### Multiple Inheritance

```cpp
class DiamondTrap : public ScavTrap, public FragTrap {
    // Inherits from both ScavTrap and FragTrap
};
```

**Challenges**:
- If both parents have the same member, which one does DiamondTrap use?
- If both parents inherit from ClapTrap, DiamondTrap would have two copies of ClapTrap's data

#### The Diamond Problem

```
     ClapTrap
      /    \
ScavTrap  FragTrap
      \    /
    DiamondTrap
```

Without virtual inheritance:
- DiamondTrap would contain two separate ClapTrap subobjects
- Ambiguity in accessing ClapTrap members
- Memory waste and logical issues

**Solution: Virtual Inheritance**

```cpp
class ScavTrap : virtual public ClapTrap { };
class FragTrap : virtual public ClapTrap { };
class DiamondTrap : public ScavTrap, public FragTrap { };
```

With virtual inheritance:
- Only one ClapTrap subobject exists in DiamondTrap
- Most derived class (DiamondTrap) is responsible for initializing the virtual base (ClapTrap)
- Resolves ambiguity and memory duplication

### Access Control in Inheritance

| Inheritance Type | Base Public | Base Protected | Base Private |
|------------------|-------------|----------------|--------------|
| **public**       | public      | protected      | inaccessible |
| **protected**    | protected   | protected      | inaccessible |
| **private**      | private     | private        | inaccessible |

**In this project**: We use `public` inheritance, meaning:
- Base class public members remain public in derived class
- Base class protected members remain protected in derived class
- Base class private members are inaccessible

### Protected Members

Protected members are accessible by:
- The class itself
- Derived classes
- NOT accessible by external code

This allows derived classes to access base class internals while maintaining encapsulation from outside users.

### Constructor and Destructor Order

**Construction Order** (from base to derived):
1. Virtual base classes (if any)
2. Direct base classes (left to right)
3. Member objects (in declaration order)
4. Derived class constructor body

**Destruction Order** (reverse of construction):
1. Derived class destructor body
2. Member objects (reverse order)
3. Direct base classes (right to left)
4. Virtual base classes (if any)

### Memory Layout

For `DiamondTrap` with virtual inheritance:
```
[ClapTrap data]        // Single shared base
[ScavTrap data]        // First parent's additional data
[FragTrap data]        // Second parent's additional data
[DiamondTrap data]     // Derived class's own data
[Virtual table pointers] // For managing virtual inheritance
```

### Advantages and Trade-offs

**Advantages of Inheritance**:
- Code reuse (don't repeat ClapTrap's implementation)
- Logical hierarchy (ScavTrap "is-a" ClapTrap)
- Polymorphism support (if using virtual functions)
- Extensibility (easy to add new robot types)

**Trade-offs**:
- Tight coupling between base and derived classes
- Multiple inheritance increases complexity
- Virtual inheritance has runtime overhead
- Can lead to fragile base class problem

## Resources

### Documentation
- [cppreference.com - Derived Classes](https://en.cppreference.com/w/cpp/language/derived_class)
- [cppreference.com - Virtual Base Classes](https://en.cppreference.com/w/cpp/language/derived_class#Virtual_base_classes)
- [cppreference.com - Multiple Inheritance](https://en.cppreference.com/w/cpp/language/multiple_inheritance)
- [cppreference.com - Access Specifiers](https://en.cppreference.com/w/cpp/language/access)

### Articles and Tutorials
- [LearnCPP.com - Inheritance](https://www.learncpp.com/cpp-tutorial/introduction-to-inheritance/)
- [LearnCPP.com - Virtual Inheritance](https://www.learncpp.com/cpp-tutorial/virtual-base-classes/)
- [GeeksforGeeks - Inheritance in C++](https://www.geeksforgeeks.org/inheritance-in-c/)
- [The Diamond Problem](https://www.makeuseof.com/what-is-diamond-problem-in-cpp/)

### Books
- "Effective C++" by Scott Meyers (Items on inheritance)
- "The C++ Programming Language" by Bjarne Stroustrup (Chapter on Class Hierarchies)
- "C++ Primer" by Stanley Lippman (Inheritance chapters)

### AI Usage

AI was **not** used in the development of this project. All code was written manually to ensure full understanding of:
- Inheritance mechanics and syntax
- Constructor initialization lists for base classes
- Protected member access
- Multiple and virtual inheritance
- The diamond problem and its resolution

The README documentation was also written without AI assistance, based on understanding gained through:
- Reading official C++ documentation
- Studying inheritance patterns
- Testing different inheritance scenarios
- Debugging multiple inheritance issues

This hands-on approach ensured deep comprehension of C++ inheritance concepts and best practices in object-oriented design.

## Testing

### General Testing Approach

Each exercise should test:
1. **Construction**: Verify correct initialization of attributes
2. **Member Functions**: Test attack, takeDamage, beRepaired
3. **Energy Management**: Ensure actions cost energy and can't be performed without it
4. **Hit Points**: Verify damage and repair affect hit points correctly
5. **Special Abilities**: Test unique functions (guardGate, highFivesGuys, whoAmI)
6. **Constructor/Destructor Messages**: Verify proper construction and destruction order

### Exercise 03 Specific Tests

For DiamondTrap, verify:
- Only one ClapTrap subobject exists (check memory with debugger)
- Correct attribute values from mixed inheritance
- Both names (DiamondTrap name and ClapTrap name) work correctly
- Construction order: ClapTrap → ScavTrap → FragTrap → DiamondTrap
- Destruction order: DiamondTrap → FragTrap → ScavTrap → ClapTrap

### Memory Testing

Run with memory leak detection:
```bash
valgrind --leak-check=full ./DiamondTrap
```

## Notes

- All code follows the **C++98 standard** (no C++11 or later features)
- Virtual inheritance is essential for ex03 to work correctly
- Watch constructor initialization order in derived classes
- Protected members allow derived classes to access base class internals
- Multiple inheritance should be used sparingly in real projects

## Author

**viceda-s**  
*42 Luxembourg*

---

*For questions, issues, or suggestions, please refer to the 42 project evaluation guidelines.*

