# CPP Module 00

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 00 is the introduction to C++ programming, focusing on fundamental concepts and the transition from C to C++. This module covers the basics of C++ syntax, namespaces, classes, member functions, stdio streams, initialization lists, static, const, and other fundamental concepts. The module consists of three exercises:

- **Exercise 00 - Megaphone**: A simple program that converts command-line arguments to uppercase, introducing basic C++ I/O and string manipulation.
- **Exercise 01 - My Awesome PhoneBook**: Implementation of a simple phonebook application using classes, demonstrating object-oriented programming basics.
- **Exercise 02 - The Job Of Your Dreams**: Recreating missing code for an Account class by analyzing logs and test files.

The main goals of this module are:
- Understanding the basics of C++ syntax and structure
- Learning about classes and encapsulation
- Working with input/output streams
- Understanding member functions and attributes
- Introduction to the Orthodox Canonical Form

## Instructions

### Compilation

Each exercise has its own directory with a Makefile. To compile an exercise:

```bash
# Navigate to the exercise directory
cd ex00  # or ex01, ex02

# Compile the program
make

# Run the executable
./megaphone [arguments]     # ex00
./phonebook                 # ex01
./account                   # ex02

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
CPP00/
├── ex00/           # Megaphone - uppercase conversion
│   ├── megaphone.cpp
│   └── Makefile
├── ex01/           # PhoneBook - contact management system
│   ├── Contact.cpp
│   ├── Contact.hpp
│   ├── PhoneBook.cpp
│   ├── PhoneBook.hpp
│   ├── main.cpp
│   └── Makefile
├── ex02/           # Account class implementation
│   ├── Account.cpp
│   ├── Account.hpp
│   ├── tests.cpp
│   ├── 19920104_091532.log
│   └── Makefile
└── README.md
```

## Usage Examples

### Exercise 00 - Megaphone

```bash
./megaphone "shhhhh... I think the students are asleep..."
# Output: SHHHHH... I THINK THE STUDENTS ARE ASLEEP...

./megaphone
# Output: * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### Exercise 01 - PhoneBook

```bash
./phonebook
# Commands available:
# ADD    - Add a new contact
# SEARCH - Display all contacts and search for one
# EXIT   - Quit the program
```

### Exercise 02 - Account

```bash
./account
# Outputs account operations matching the log format
```

## Technical Choices

- **C++98 Standard**: The project strictly adheres to the C++98 standard as required by the 42 curriculum.
- **No STL**: Standard Template Library is not allowed in this module to focus on fundamentals.
- **Namespaces**: Introduction to the `std` namespace and custom namespaces.
- **Class Design**: Focus on proper encapsulation with private/public members.
- **Input Validation**: Proper handling of user input and edge cases.

## Resources

### Official Documentation
- [C++ Reference](https://en.cppreference.com/)
- [C++ Documentation](https://cplusplus.com/doc/)
- [C++ Basics Tutorial](https://www.learncpp.com/)

### Articles and Tutorials
- [C++ Classes and Objects](https://www.geeksforgeeks.org/c-classes-and-objects/)
- [Input/Output with iostream](https://www.cplusplus.com/reference/iostream/)
- [Understanding Namespaces in C++](https://www.geeksforgeeks.org/namespace-in-c/)
- [Member Functions in C++](https://www.learncpp.com/cpp-tutorial/member-functions/)

### Books
- "C++ Primer" by Stanley Lippman
- "A Tour of C++" by Bjarne Stroustrup
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used for the following purposes:

1. **Syntax Clarification**: Understanding differences between C and C++ syntax.
2. **Documentation Research**: Finding relevant documentation for iostream and string operations.
3. **Code Review**: Checking proper class structure and member function implementation.
4. **Readme Creation**: Structuring and formatting this README file according to the requirements.

**Important Note**: All core logic, class design, and algorithm implementations were made independently. AI was used as a reference tool, similar to consulting documentation or textbooks, but the actual implementation and understanding of concepts are original work.

## Key Concepts Covered

- **Basic C++ Syntax**: Understanding the structure of C++ programs
- **Namespaces**: Using and declaring namespaces
- **Classes**: Creating and using classes with member functions and attributes
- **Encapsulation**: Public and private access specifiers
- **Constructors/Destructors**: Object initialization and cleanup
- **I/O Streams**: Using std::cout, std::cin, and stream formatting
- **String Manipulation**: Working with std::string class
- **Static Members**: Understanding static member functions and variables

## Learning Outcomes

By completing this module, you will:
- Understand the fundamental differences between C and C++
- Learn to create and use classes effectively
- Master basic input/output operations in C++
- Develop skills in object-oriented programming
- Understand encapsulation and data hiding principles
- Gain experience with C++ compilation and linking

---

*For any questions or issues regarding this project, please refer to the 42 curriculum documentation or contact the project author.*

