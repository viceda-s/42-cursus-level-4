# CPP Module 04

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 04 introduces subtype polymorphism, abstract classes, and interfaces in C++. This module focuses on understanding virtual functions, pure virtual functions, and how to create flexible, extensible class hierarchies using polymorphism. The exercises explore the concept of polymorphism through an animal hierarchy:

- **Exercise 00 - Polymorphism**: Creating a basic animal hierarchy with virtual functions to demonstrate runtime polymorphism.
- **Exercise 01 - I don't want to set the world on fire**: Adding Brain class and implementing deep copy for derived classes.
- **Exercise 02 - Abstract class**: Converting Animal to an abstract class to prevent instantiation of the base class.
- **Exercise 03 - Interface & recap**: Creating and implementing interfaces (pure abstract classes) for demonstration purposes.

The main goals of this module are:
- Understanding polymorphism and virtual functions
- Learning about abstract classes and pure virtual functions
- Mastering deep copy vs shallow copy
- Understanding interfaces in C++
- Learning about virtual destructors

## Instructions

### Compilation

Each exercise has its own directory with a Makefile. To compile an exercise:

```bash
# Navigate to the exercise directory
cd ex00  # or ex01, ex02, ex03

# Compile the program
make

# Run the executable
./polymorphism  # ex00
./brain         # ex01
./abstract      # ex02
./interface     # ex03

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
CPP04/
├── ex00/           # Basic polymorphism
│   ├── AAnimal.cpp
│   ├── AAnimal.hpp
│   ├── Cat.cpp
│   ├── Cat.hpp
│   ├── Dog.cpp
│   ├── Dog.hpp
│   ├── WrongAnimal.cpp
│   ├── WrongAnimal.hpp
│   ├── WrongCat.cpp
│   ├── WrongCat.hpp
│   ├── main.cpp
│   └── Makefile
├── ex01/           # Brain class and deep copy
│   ├── AAnimal.cpp
│   ├── AAnimal.hpp
│   ├── Brain.cpp
│   ├── Brain.hpp
│   ├── Cat.cpp
│   ├── Cat.hpp
│   ├── Dog.cpp
│   ├── Dog.hpp
│   ├── main.cpp
│   └── Makefile
├── ex02/           # Abstract class
│   ├── AAnimal.cpp
│   ├── AAnimal.hpp
│   ├── Brain.cpp
│   ├── Brain.hpp
│   ├── Cat.cpp
│   ├── Cat.hpp
│   ├── Dog.cpp
│   ├── Dog.hpp
│   ├── main.cpp
│   └── Makefile
├── ex03/           # Interfaces
│   ├── [Interface implementations]
│   ├── main.cpp
│   └── Makefile
└── README.md
```

## Usage Examples

### Exercise 00 - Polymorphism

```cpp
const Animal* meta = new Animal();
const Animal* dog = new Dog();
const Animal* cat = new Cat();

std::cout << dog->getType() << std::endl;
std::cout << cat->getType() << std::endl;
cat->makeSound();  // Will output cat sound (polymorphism)
dog->makeSound();  // Will output dog sound
meta->makeSound(); // Generic animal sound

delete meta;
delete dog;
delete cat;
```

### Exercise 01 - Deep Copy

```cpp
Dog basic;
{
    Dog tmp = basic;  // Deep copy should occur
}
// tmp is destroyed, but basic's brain should still be intact
```

### Exercise 02 - Abstract Class

```cpp
// Animal* meta = new Animal(); // This should not compile
const Animal* dog = new Dog();
const Animal* cat = new Cat();

dog->makeSound();
cat->makeSound();

delete dog;
delete cat;
```

### Exercise 03 - Interfaces

```cpp
// Using interfaces to define contracts
// Implementation depends on the specific exercise requirements
```

## Technical Choices

- **C++98 Standard**: The project strictly adheres to the C++98 standard as required by the 42 curriculum.
- **Virtual Functions**: Using virtual keyword for runtime polymorphism.
- **Virtual Destructors**: Essential for proper cleanup in polymorphic hierarchies.
- **Pure Virtual Functions**: Creating abstract classes and interfaces.
- **Deep Copy**: Implementing proper copy constructors for classes with dynamic memory.
- **Orthodox Canonical Form**: All classes follow the Rule of Three.

## Resources

### Official Documentation
- [C++ Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [C++ Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)
- [C++ Polymorphism](https://en.cppreference.com/w/cpp/language/object#Polymorphic_objects)
- [C++ Virtual Destructors](https://en.cppreference.com/w/cpp/language/destructor#Virtual_destructors)

### Articles and Tutorials
- [Polymorphism in C++](https://www.geeksforgeeks.org/polymorphism-in-c/)
- [Virtual Functions Explained](https://www.learncpp.com/cpp-tutorial/virtual-functions/)
- [Abstract Classes and Interfaces](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)
- [Deep Copy vs Shallow Copy](https://www.geeksforgeeks.org/shallow-copy-and-deep-copy-in-c/)

### Books
- "Effective C++" by Scott Meyers (Item 7: Declare destructors virtual in polymorphic base classes)
- "C++ Primer" by Stanley Lippman
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used for the following purposes:

1. **Virtual Function Syntax**: Understanding the correct usage of virtual keyword.
2. **Deep Copy Implementation**: Learning proper techniques for deep copying objects with dynamic memory.
3. **Abstract Classes**: Understanding pure virtual functions and their implications.
4. **Readme Creation**: Structuring and formatting this README file according to the requirements.

**Important Note**: All core logic, class hierarchies, polymorphic behavior, deep copy implementations, and design decisions were made independently. AI was used as a reference tool, similar to consulting documentation or textbooks, but the actual implementation and understanding of concepts are original work.

## Key Concepts Covered

- **Polymorphism**: Runtime polymorphism through virtual functions
- **Virtual Functions**: Dynamic dispatch and method overriding
- **Virtual Destructors**: Proper cleanup in polymorphic hierarchies
- **Abstract Classes**: Classes with at least one pure virtual function
- **Pure Virtual Functions**: Functions declared with `= 0`
- **Interfaces**: Pure abstract classes with only pure virtual functions
- **Deep Copy**: Proper copying of objects with dynamic memory
- **Shallow Copy**: Understanding the default copy behavior
- **Slicing Problem**: Understanding object slicing and how to avoid it

## Learning Outcomes

By completing this module, you will:
- Master polymorphism in C++
- Understand virtual functions and their mechanism
- Learn to create abstract classes and interfaces
- Understand the importance of virtual destructors
- Master deep copy implementation for complex objects
- Learn about the virtual function table (vtable)
- Understand when and why to use polymorphism
- Develop skills in designing flexible, extensible systems

---

*For any questions or issues regarding this project, please refer to the 42 curriculum documentation or contact the project author.*

