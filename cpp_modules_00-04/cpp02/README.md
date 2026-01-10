# CPP Module 02

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 02 introduces ad-hoc polymorphism, operator overloading, and the Orthodox Canonical Form. This module focuses on understanding how to overload operators in C++ and how to implement fixed-point number representation. The module consists of four exercises:

- **Exercise 00 - My First Class in Orthodox Canonical Form**: Creating a basic Fixed-point number class following the Orthodox Canonical Form.
- **Exercise 01 - Towards a more useful fixed-point number class**: Extending the Fixed class with constructors, conversion operators, and stream insertion.
- **Exercise 02 - Now we're talking**: Implementing comparison and arithmetic operators for the Fixed class.
- **Exercise 03 - BSP**: Using the Fixed class to solve a geometric problem (Binary Space Partitioning - point in triangle).

The main goals of this module are:
- Understanding operator overloading in C++
- Mastering the Orthodox Canonical Form
- Learning about fixed-point number representation
- Understanding ad-hoc polymorphism
- Implementing mathematical operators for custom types

## Instructions

### Compilation

Each exercise has its own directory with a Makefile. To compile an exercise:

```bash
# Navigate to the exercise directory
cd ex00  # or ex01, ex02, ex03

# Compile the program
make

# Run the executable
./fixed_00    # ex00
./fixed_01    # ex01
./fixed_02    # ex02
./bsp         # ex03

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
CPP02/
├── ex00/           # Orthodox Canonical Form basics
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   ├── main.cpp
│   └── Makefile
├── ex01/           # Constructors and conversions
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   ├── main.cpp
│   └── Makefile
├── ex02/           # Operator overloading
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   ├── main.cpp
│   └── Makefile
├── ex03/           # BSP - Point in triangle
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   ├── Point.cpp
│   ├── Point.hpp
│   ├── bsp.cpp
│   ├── main.cpp
│   └── Makefile
└── README.md
```

## Usage Examples

### Exercise 00 - Basic Fixed-point

```cpp
Fixed a;
Fixed b(a);
Fixed c;
c = b;

std::cout << a.getRawBits() << std::endl;
std::cout << b.getRawBits() << std::endl;
std::cout << c.getRawBits() << std::endl;
```

### Exercise 01 - Conversions

```cpp
Fixed a;
Fixed const b(10);
Fixed const c(42.42f);
Fixed const d(b);

std::cout << "a is " << a << std::endl;
std::cout << "b is " << b << std::endl;
std::cout << "c is " << c << std::endl;
std::cout << "d is " << d << std::endl;
```

### Exercise 02 - Operators

```cpp
Fixed a;
Fixed const b(Fixed(5.05f) * Fixed(2));

std::cout << a << std::endl;
std::cout << ++a << std::endl;
std::cout << a << std::endl;
std::cout << a++ << std::endl;
std::cout << a << std::endl;
std::cout << b << std::endl;
std::cout << Fixed::max(a, b) << std::endl;
```

### Exercise 03 - BSP

```bash
./bsp
# Tests if a point is inside a triangle using fixed-point arithmetic
```

## Technical Choices

- **C++98 Standard**: The project strictly adheres to the C++98 standard as required by the 42 curriculum.
- **Orthodox Canonical Form**: All classes implement the four required methods (default constructor, copy constructor, assignment operator, destructor).
- **Fixed-point Arithmetic**: Using integer representation with fractional bits for precise calculations.
- **Operator Overloading**: Implementing intuitive operators for custom types.
- **Const Correctness**: Proper use of const keyword for methods and parameters.

## Resources

### Official Documentation
- [C++ Operator Overloading](https://en.cppreference.com/w/cpp/language/operators)
- [C++ Orthodox Canonical Form](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [Fixed-point Arithmetic](https://en.wikipedia.org/wiki/Fixed-point_arithmetic)
- [Stream Insertion Operator](https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt)

### Articles and Tutorials
- [Operator Overloading in C++](https://www.geeksforgeeks.org/operator-overloading-c/)
- [Understanding the Orthodox Canonical Form](https://www.francescmm.com/orthodox-canonical-class-form/)
- [Fixed-point Numbers Explained](https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html)
- [C++ Copy Constructor](https://www.learncpp.com/cpp-tutorial/copy-constructors/)

### Books
- "Effective C++" by Scott Meyers
- "C++ Primer" by Stanley Lippman
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used for the following purposes:

1. **Operator Overloading Syntax**: Understanding the correct syntax for different operators.
2. **Fixed-point Arithmetic**: Learning about bit shifting and fractional representation.
3. **Orthodox Canonical Form**: Clarifying the implementation of copy constructors and assignment operators.
4. **Readme Creation**: Structuring and formatting this README file according to the requirements.

**Important Note**: All core logic, operator implementations, fixed-point arithmetic calculations, and class design were made independently. AI was used as a reference tool, similar to consulting documentation or textbooks, but the actual implementation and understanding of concepts are original work.

## Key Concepts Covered

- **Orthodox Canonical Form**: Implementing the Rule of Three
- **Operator Overloading**: Overloading arithmetic, comparison, and stream operators
- **Fixed-point Numbers**: Representing fractional numbers using integers
- **Const Correctness**: Using const methods and parameters appropriately
- **Copy Constructor**: Deep understanding of copying objects
- **Assignment Operator**: Proper implementation of copy assignment
- **Ad-hoc Polymorphism**: Function overloading and operator overloading
- **Stream Insertion**: Overloading << operator for custom types

## Learning Outcomes

By completing this module, you will:
- Master operator overloading in C++
- Understand and implement the Orthodox Canonical Form
- Learn about fixed-point number representation
- Develop skills in implementing mathematical operators
- Understand const correctness in C++
- Gain experience with copy constructors and assignment operators
- Learn to create intuitive interfaces for custom types
- Understand the difference between prefix and postfix increment/decrement

---

*For any questions or issues regarding this project, please refer to the 42 curriculum documentation or contact the project author.*

