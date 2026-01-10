# CPP Module 01

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 01 focuses on memory allocation, pointers to members, references, and the switch statement. This module deepens the understanding of memory management in C++ and introduces important concepts that distinguish C++ from C. The module consists of six exercises:

- **Exercise 00 - BraiiiiiiinnnzzzZ**: Creating and destroying zombies on the stack and heap, understanding memory allocation differences.
- **Exercise 01 - Moar brainz!**: Creating a horde of zombies using dynamic array allocation.
- **Exercise 02 - HI THIS IS BRAIN**: Understanding the differences between pointers and references.
- **Exercise 03 - Unnecessary violence**: Implementing different weapon types and understanding references vs pointers in practical scenarios.
- **Exercise 04 - Sed is for losers**: String manipulation and file operations, creating a simple text replacement tool.
- **Exercise 05 - Harl 2.0**: Implementing a logging system with different severity levels.
- **Exercise 06 - Harl filter**: Extending the logging system with filtering capabilities.

The main goals of this module are:
- Understanding stack vs heap memory allocation
- Mastering pointers and references
- Learning when to use new/delete operators
- Understanding the differences between references and pointers
- Working with file streams

## Instructions

### Compilation

Each exercise has its own directory with a Makefile. To compile an exercise:

```bash
# Navigate to the exercise directory
cd ex00  # or ex01, ex02, ex03, ex04, ex05, ex06

# Compile the program
make

# Run the executable
./zombie          # ex00
./zombie_horde    # ex01
./brain           # ex02
./violence        # ex03
./sed             # ex04
./harl            # ex05
./harlFilter      # ex06

# Clean object files
make clean

# Clean all generated files
make fclean

# Recompile from scratch
make re
```

### Requirements

- **Compiler**: C++ compiler with C++98 standard support (g++, clang++)
- **Compilation flags**: `-Wall -Wextra -Werror -std=c++98`
- **Operating System**: Linux, macOS, or WSL (Windows Subsystem for Linux)

### Project Structure

```
CPP01/
├── ex00/           # Zombie - stack vs heap allocation
│   ├── Zombie.cpp
│   ├── Zombie.hpp
│   ├── newZombie.cpp
│   ├── randomChump.cpp
│   ├── main.cpp
│   └── Makefile
├── ex01/           # Zombie Horde - array allocation
│   ├── Zombie.cpp
│   ├── Zombie.hpp
│   ├── zombieHorde.cpp
│   ├── main.cpp
│   └── Makefile
├── ex02/           # Brain - pointers vs references
│   ├── main.cpp
│   └── Makefile
├── ex03/           # Violence - weapon system
│   ├── HumanA.cpp
│   ├── HumanA.hpp
│   ├── HumanB.cpp
│   ├── HumanB.hpp
│   ├── Weapon.cpp
│   ├── Weapon.hpp
│   ├── main.cpp
│   └── Makefile
├── ex04/           # Sed replacement tool
│   ├── main.cpp
│   └── Makefile
├── ex05/           # Harl logging system
│   ├── Harl.cpp
│   ├── Harl.hpp
│   ├── main.cpp
│   └── Makefile
├── ex06/           # Harl filter
│   ├── Harl.cpp
│   ├── Harl.hpp
│   ├── main.cpp
│   └── Makefile
└── README.md
```

## Usage Examples

### Exercise 00 - Zombie

```bash
./zombie
# Creates zombies on stack and heap, demonstrating different lifetimes
```

### Exercise 01 - Zombie Horde

```bash
./zombie_horde
# Creates a horde of N zombies using dynamic allocation
```

### Exercise 02 - Brain

```bash
./brain
# Demonstrates the differences between pointers and references
```

### Exercise 03 - Violence

```bash
./violence
# Shows HumanA and HumanB with different weapon handling
```

### Exercise 04 - Sed

```bash
./sed filename s1 s2
# Replaces all occurrences of s1 with s2 in filename
# Creates filename.replace with the result
```

### Exercise 05 - Harl

```bash
./harl
# Displays different log levels (DEBUG, INFO, WARNING, ERROR)
```

### Exercise 06 - Harl Filter

```bash
./harlFilter DEBUG
# Filters and displays logs from DEBUG level and above
```

## Technical Choices

- **C++98 Standard**: The project strictly adheres to the C++98 standard as required by the 42 curriculum.
- **Memory Management**: Proper use of new/delete operators with no memory leaks.
- **References vs Pointers**: Understanding when to use each based on the use case.
- **RAII Principle**: Resource Acquisition Is Initialization - objects manage their own resources.
- **File Streams**: Using ifstream and ofstream for file operations.

## Resources

### Official Documentation
- [C++ Memory Management](https://en.cppreference.com/w/cpp/memory)
- [C++ References](https://en.cppreference.com/w/cpp/language/reference)
- [C++ Pointers](https://en.cppreference.com/w/cpp/language/pointer)
- [C++ File I/O](https://en.cppreference.com/w/cpp/io)

### Articles and Tutorials
- [Stack vs Heap Memory](https://www.geeksforgeeks.org/stack-vs-heap-memory-allocation/)
- [Understanding References in C++](https://www.learncpp.com/cpp-tutorial/lvalue-references/)
- [When to use References vs Pointers](https://stackoverflow.com/questions/7058339/when-to-use-references-vs-pointers)
- [File I/O in C++](https://www.cplusplus.com/doc/tutorial/files/)

### Books
- "Effective C++" by Scott Meyers
- "C++ Primer" by Stanley Lippman
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used for the following purposes:

1. **Memory Management**: Understanding best practices for new/delete usage.
2. **Reference Semantics**: Clarifying when to use references vs pointers.
3. **File Stream Operations**: Learning proper file handling techniques.
4. **Readme Creation**: Structuring and formatting this README file according to the requirements.

**Important Note**: All core logic, class design, memory management strategies, and algorithm implementations were made independently. AI was used as a reference tool, similar to consulting documentation or textbooks, but the actual implementation and understanding of concepts are original work.

## Key Concepts Covered

- **Dynamic Memory Allocation**: Using new and delete operators
- **Stack vs Heap**: Understanding where objects are allocated
- **Pointers**: Working with memory addresses
- **References**: Using references as aliases to objects
- **Pointer to Members**: Understanding member pointers
- **File Streams**: Reading from and writing to files
- **Switch Statements**: Using switch for control flow
- **Memory Leaks**: Preventing and detecting memory leaks

## Learning Outcomes

By completing this module, you will:
- Master dynamic memory allocation in C++
- Understand the critical differences between stack and heap allocation
- Learn when to use pointers vs references
- Develop proper memory management habits
- Gain experience with file I/O operations
- Understand object lifetime and scope
- Learn to prevent memory leaks and dangling pointers

---

*For any questions or issues regarding this project, please refer to the 42 curriculum documentation or contact the project author.*

