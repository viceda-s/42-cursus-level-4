# CPP Module 04

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 04 focuses on **subtype polymorphism, abstract classes, and interfaces**. This module deepens understanding of runtime polymorphism through virtual functions and explores how to design flexible, extensible class hierarchies. The project demonstrates inheritance, virtual functions, abstract base classes, and the critical importance of deep copying for derived classes. The module consists of three exercises (plus an optional fourth):

- **Exercise 00 (Polymorphism)**: Creating an animal hierarchy with virtual functions to demonstrate runtime polymorphism
- **Exercise 01 (I don't want to set the world on fire)**: Adding a Brain class and implementing deep copy for derived classes
- **Exercise 02 (Abstract class)**: Converting Animal to an abstract class to prevent direct instantiation
- **Exercise 03 (Interface & recap)** *(optional)*: Creating and implementing pure interfaces

### Learning Objectives

- Understanding runtime polymorphism through virtual functions
- Mastering virtual destructors for polymorphic hierarchies
- Learning about abstract classes and pure virtual functions
- Understanding deep copy vs shallow copy in inheritance hierarchies
- Implementing proper copy constructors and assignment operators for derived classes
- Working with interfaces (pure abstract classes)
- Understanding the virtual function table (vtable) mechanism
- Learning when and why to use polymorphism
- Avoiding the object slicing problem
- Understanding dynamic dispatch and binding

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

#### Exercise 00 - Polymorphism
```bash
cd ex00
make
./polymorphism
```

#### Exercise 01 - Brain and Deep Copy
```bash
cd ex01
make
./brain
```

#### Exercise 02 - Abstract Class
```bash
cd ex02
make
./abstract
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
cpp04/
├── ex00/                    # Basic polymorphism
│   ├── AAnimal.cpp         # Base Animal class (or Animal.cpp)
│   ├── AAnimal.hpp         # Animal interface
│   ├── Dog.cpp             # Dog derived class
│   ├── Dog.hpp
│   ├── Cat.cpp             # Cat derived class
│   ├── Cat.hpp
│   ├── WrongAnimal.cpp     # Demonstration of non-virtual
│   ├── WrongAnimal.hpp
│   ├── WrongCat.cpp        # Shows why virtual is needed
│   ├── WrongCat.hpp
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex01/                    # Brain class and deep copy
│   ├── AAnimal.cpp         # Animal base class
│   ├── AAnimal.hpp
│   ├── Dog.cpp             # Dog with Brain
│   ├── Dog.hpp
│   ├── Cat.cpp             # Cat with Brain
│   ├── Cat.hpp
│   ├── Brain.cpp           # Brain class (100 ideas)
│   ├── Brain.hpp
│   ├── main.cpp            # Test deep copy
│   └── Makefile
└── ex02/                    # Abstract class
    ├── AAnimal.cpp         # Abstract Animal class
    ├── AAnimal.hpp
    ├── Dog.cpp             # Concrete Dog implementation
    ├── Dog.hpp
    ├── Cat.cpp             # Concrete Cat implementation
    ├── Cat.hpp
    ├── Brain.cpp           # Brain class
    ├── Brain.hpp
    ├── main.cpp            # Cannot instantiate Animal
    └── Makefile
```

## Features

### Exercise 00: Polymorphism

Creates an animal hierarchy demonstrating runtime polymorphism:

**Animal Base Class**:
- **Protected Attribute**: `std::string type`
- **Public Methods**:
  - `Animal()`: Default constructor
  - `Animal(const Animal& copy)`: Copy constructor
  - `Animal& operator=(const Animal& rhs)`: Assignment operator
  - `virtual ~Animal()`: **Virtual destructor** (critical!)
  - `virtual void makeSound() const`: Virtual function for polymorphism
  - `std::string getType() const`: Returns animal type

**Dog Derived Class**:
- Inherits from Animal
- Sets `type = "Dog"` in constructor
- Overrides `makeSound()` to return "Woof! Woof!"

**Cat Derived Class**:
- Inherits from Animal
- Sets `type = "Cat"` in constructor
- Overrides `makeSound()` to return "Meow! Meow!"

**WrongAnimal / WrongCat** (Demonstration):
- Same structure but **without `virtual`** keyword
- Shows why virtual functions are necessary for polymorphism

**Key Concepts**:

**Virtual Functions**:
```cpp
class Animal {
protected:
    std::string type;
public:
    Animal() : type("Animal") {}
    virtual ~Animal() {}  // Virtual destructor!
    
    virtual void makeSound() const {
        std::cout << "Generic animal sound" << std::endl;
    }
    
    std::string getType() const { return type; }
};

class Dog : public Animal {
public:
    Dog() { type = "Dog"; }
    
    void makeSound() const {  // Override (virtual is inherited)
        std::cout << "Woof! Woof!" << std::endl;
    }
};
```

**Runtime Polymorphism**:
```cpp
Animal* animal = new Animal();
Animal* dog = new Dog();
Animal* cat = new Cat();

animal->makeSound();  // "Generic animal sound"
dog->makeSound();     // "Woof! Woof!" - calls Dog::makeSound()
cat->makeSound();     // "Meow! Meow!" - calls Cat::makeSound()

// Type determined at runtime based on actual object
```

**Why Virtual Destructor?**
```cpp
// Without virtual destructor
class Base {
public:
    ~Base() { /* cleanup */ }  // NOT virtual
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() : data(new int[100]) {}
    ~Derived() { delete[] data; }  // Never called!
};

Base* ptr = new Derived();
delete ptr;  // Only Base::~Base() called → Memory leak!

// With virtual destructor
class Base {
public:
    virtual ~Base() { /* cleanup */ }  // Virtual!
};

delete ptr;  // Calls Derived::~Derived(), then Base::~Base() ✓
```

**Virtual Function Table (vtable)**:

When a class has virtual functions, the compiler creates a **vtable** (virtual function table):
```
Animal vtable:
  [0] → Animal::makeSound()
  [1] → Animal::~Animal()

Dog vtable:
  [0] → Dog::makeSound()     // Overridden
  [1] → Dog::~Dog()          // Overridden

Each object has hidden pointer to its vtable:
  Animal object → Animal vtable
  Dog object    → Dog vtable
```

At runtime:
```cpp
Animal* ptr = new Dog();
ptr->makeSound();  // 1. Follow vptr to Dog vtable
                   // 2. Look up makeSound in vtable
                   // 3. Call Dog::makeSound()
```

**WrongAnimal Example** (No Virtual):
```cpp
class WrongAnimal {
public:
    void makeSound() const {  // NOT virtual
        std::cout << "Wrong animal sound" << std::endl;
    }
};

class WrongCat : public WrongAnimal {
public:
    void makeSound() const {  // Hides base function
        std::cout << "Wrong meow" << std::endl;
    }
};

WrongAnimal* wrong = new WrongCat();
wrong->makeSound();  // "Wrong animal sound" - calls WrongAnimal version!
                     // No polymorphism without virtual
```

**Usage Example**:
```cpp
const Animal* meta = new Animal();
const Animal* dog = new Dog();
const Animal* cat = new Cat();

std::cout << dog->getType() << std::endl;  // "Dog"
std::cout << cat->getType() << std::endl;  // "Cat"

cat->makeSound();   // "Meow! Meow!" (polymorphism)
dog->makeSound();   // "Woof! Woof!"
meta->makeSound();  // "Generic animal sound"

delete meta;  // Virtual destructor ensures proper cleanup
delete dog;
delete cat;
```

### Exercise 01: I don't want to set the world on fire

Adds complexity by giving animals a Brain and requiring deep copy:

**Brain Class**:
- **Attribute**: `std::string ideas[100]` - array of 100 idea strings
- **Orthodox Canonical Form**:
  - Default constructor
  - Copy constructor (deep copy all ideas)
  - Assignment operator (deep copy all ideas)
  - Destructor

**Dog Class** (Modified):
- **Private Attribute**: `Brain* _brain` - pointer to Brain
- **Constructor**: Allocates new Brain on heap
- **Copy Constructor**: Creates new Brain and copies ideas (deep copy)
- **Assignment Operator**: Deletes old Brain, creates new, copies ideas
- **Destructor**: Deletes Brain

**Cat Class** (Modified):
- Same structure as Dog with Brain

**Key Concepts**:

**Deep Copy vs Shallow Copy**:

**Shallow Copy** (default behavior, BAD for pointers):
```cpp
class Dog {
    Brain* _brain;
public:
    Dog() : _brain(new Brain()) {}
    // Using default copy constructor (shallow copy)
};

Dog dog1;
Dog dog2 = dog1;  // dog2._brain = dog1._brain (same pointer!)

dog1._brain->ideas[0] = "Chase cats";
// dog2 sees the same change! They share the brain!

delete dog1._brain;
// dog2._brain now points to freed memory! (dangling pointer)
```

**Deep Copy** (correct for pointers):
```cpp
class Dog {
    Brain* _brain;
public:
    Dog() : _brain(new Brain()) {}
    
    // Deep copy constructor
    Dog(const Dog& copy) {
        _brain = new Brain(*copy._brain);  // New Brain, copy content
    }
    
    // Deep copy assignment
    Dog& operator=(const Dog& rhs) {
        if (this != &rhs) {
            delete _brain;              // Delete old brain
            _brain = new Brain(*rhs._brain);  // New brain, copy content
        }
        return *this;
    }
    
    ~Dog() {
        delete _brain;  // Clean up
    }
};

Dog dog1;
Dog dog2 = dog1;  // dog2._brain is different object with same content

dog1._brain->ideas[0] = "Chase cats";
// dog2 is unaffected (separate brain)
```

**Implementation**:
```cpp
// Brain.cpp
Brain::Brain() {
    std::cout << "Brain constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
        ideas[i] = "";
}

Brain::Brain(const Brain& copy) {
    std::cout << "Brain copy constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
        ideas[i] = copy.ideas[i];  // Copy each idea
}

Brain& Brain::operator=(const Brain& rhs) {
    std::cout << "Brain assignment operator called" << std::endl;
    if (this != &rhs) {
        for (int i = 0; i < 100; i++)
            ideas[i] = rhs.ideas[i];  // Copy each idea
    }
    return *this;
}

// Dog.cpp
Dog::Dog() : Animal() {
    type = "Dog";
    _brain = new Brain();  // Allocate brain
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog& copy) : Animal(copy) {
    _brain = new Brain(*copy._brain);  // Deep copy brain
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& rhs) {
    if (this != &rhs) {
        Animal::operator=(rhs);  // Call base assignment
        delete _brain;            // Delete old brain
        _brain = new Brain(*rhs._brain);  // Deep copy new brain
    }
    return *this;
}

Dog::~Dog() {
    delete _brain;  // Free brain
    std::cout << "Dog destructor called" << std::endl;
}
```

**Testing Deep Copy**:
```cpp
Dog basic;
{
    Dog tmp = basic;  // Deep copy should occur
    tmp._brain->ideas[0] = "Different idea";
}
// tmp is destroyed (brain deleted), but basic's brain is intact

// Verify basic still has its own separate brain
```

**Why Deep Copy Matters**:
1. **Memory Safety**: Prevents double-free errors
2. **Data Integrity**: Each object has independent data
3. **Resource Management**: Proper cleanup without side effects
4. **Polymorphic Copying**: Base pointer can copy derived objects correctly

### Exercise 02: Abstract class

Converts Animal into an abstract class:

**Abstract Animal Class**:
```cpp
class AAnimal {  // or Animal with pure virtual
protected:
    std::string type;
public:
    AAnimal();
    AAnimal(const AAnimal& copy);
    AAnimal& operator=(const AAnimal& rhs);
    virtual ~AAnimal();
    
    virtual void makeSound() const = 0;  // Pure virtual function
    std::string getType() const;
};
```

**Pure Virtual Function**:
```cpp
virtual void makeSound() const = 0;  // = 0 makes it pure virtual
```

**Key Concepts**:

**Abstract Class**:
- A class with at least one pure virtual function
- **Cannot be instantiated** directly
- Must be derived from to create concrete classes
- Derived classes must implement all pure virtual functions

**Why Use Abstract Classes?**
1. **Interface Definition**: Defines contract that derived classes must fulfill
2. **Prevent Instantiation**: No "generic animal" should exist
3. **Force Implementation**: Ensures derived classes provide specific behavior
4. **Design Intent**: Makes abstraction explicit

**Example**:
```cpp
// This will NOT compile:
AAnimal* animal = new AAnimal();  // Error! Abstract class

// This is OK:
AAnimal* dog = new Dog();  // Dog implements makeSound()
AAnimal* cat = new Cat();  // Cat implements makeSound()

dog->makeSound();  // "Woof! Woof!"
cat->makeSound();  // "Meow! Meow!"
```

**Concrete Derived Classes**:
```cpp
class Dog : public AAnimal {
public:
    Dog();
    Dog(const Dog& copy);
    Dog& operator=(const Dog& rhs);
    ~Dog();
    
    void makeSound() const;  // Must implement pure virtual function
private:
    Brain* _brain;
};

void Dog::makeSound() const {
    std::cout << "Woof! Woof!" << std::endl;
}
```

**Testing Abstract Class**:
```cpp
// AAnimal* animal = new AAnimal();  // Should not compile!
AAnimal* dog = new Dog();
AAnimal* cat = new Cat();

dog->makeSound();  // Works through polymorphism
cat->makeSound();

delete dog;  // Virtual destructor ensures proper cleanup
delete cat;
```

**Abstract vs Concrete**:
```
Abstract Class:
  - At least one pure virtual function
  - Cannot instantiate
  - Defines interface
  - Forces derived implementation

Concrete Class:
  - All virtual functions implemented
  - Can instantiate
  - Provides implementation
  - Ready to use
```

### Exercise 03: Interface & recap (Optional)

Creates pure interfaces (classes with only pure virtual functions):

**Interface Pattern**:
```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const& getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

**Key Concepts**:

**Interface** (C++ style):
- All member functions are pure virtual
- No member variables (or only static const)
- Provides contract only, no implementation
- Name often starts with 'I' (IInterface)

**Why Interfaces?**
1. **Multiple Inheritance**: C++ allows multiple interface inheritance
2. **Flexibility**: Change implementation without changing interface
3. **Testability**: Easy to create mock implementations
4. **Decoupling**: Depend on abstractions, not concrete classes

**Example Usage**:
```cpp
class Character : public ICharacter {
private:
    std::string _name;
    AMateria* _inventory[4];
public:
    Character(std::string const& name);
    ~Character();
    
    // Implement all interface methods
    std::string const& getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};
```

## Algorithm and Data Structure Explanation

### Polymorphism and Virtual Functions

**What is Polymorphism?**

The ability of different classes to respond to the same function call in different ways.

**Types of Polymorphism**:

**1. Compile-time (Static) Polymorphism**:
- Function overloading
- Operator overloading
- Templates
- Resolved at compile time

**2. Runtime (Dynamic) Polymorphism**:
- Virtual functions
- Inheritance
- Resolved at runtime via vtable

**How Virtual Functions Work**:

**Virtual Function Table (vtable)**:

Each class with virtual functions has a static table:
```
Class Animal {
    virtual makeSound();
    virtual ~Animal();
}

Animal vtable:
  [0] → Animal::makeSound
  [1] → Animal::~Animal

Dog vtable:
  [0] → Dog::makeSound      (overridden)
  [1] → Dog::~Dog           (overridden)

Cat vtable:
  [0] → Cat::makeSound      (overridden)
  [1] → Cat::~Cat           (overridden)
```

**Each object has a hidden vptr**:
```cpp
class Animal {
    void** __vptr;  // Hidden pointer to vtable (added by compiler)
    std::string type;
};

Animal a;   // a.__vptr → Animal vtable
Dog d;      // d.__vptr → Dog vtable
Cat c;      // c.__vptr → Cat vtable
```

**Function Call Resolution**:
```cpp
Animal* ptr = new Dog();
ptr->makeSound();

// Compiled as:
// 1. Load ptr->__vptr (pointer to Dog vtable)
// 2. Load vtable[0] (address of Dog::makeSound)
// 3. Call Dog::makeSound through function pointer

// Pseudocode:
(*ptr->__vptr[0])(ptr);  // Call Dog::makeSound(this)
```

**Performance**:
- Virtual function call: 1 extra indirection (vptr → vtable → function)
- Non-virtual call: Direct function address
- Typically negligible overhead

### Deep Copy vs Shallow Copy

**Memory Layout**:

**Shallow Copy** (default):
```
Before copy:
  dog1:  [type] [_brain*] ───┐
                             ├──→ [Brain object]
  dog2:  [type] [_brain*] ───┘

After dog1 destroyed:
  dog2:  [type] [_brain*] ───→ [FREED MEMORY] ← Dangling pointer!
```

**Deep Copy** (correct):
```
After deep copy:
  dog1:  [type] [_brain*] ───→ [Brain object 1]
  
  dog2:  [type] [_brain*] ───→ [Brain object 2]
                                (copy of Brain 1)

After dog1 destroyed:
  dog2:  [type] [_brain*] ───→ [Brain object 2] ← Still valid!
```

**Implementation Pattern**:
```cpp
class Container {
    Resource* _resource;
public:
    // Constructor
    Container() : _resource(new Resource()) {}
    
    // Deep copy constructor
    Container(const Container& copy) {
        _resource = new Resource(*copy._resource);
    }
    
    // Deep copy assignment
    Container& operator=(const Container& rhs) {
        if (this != &rhs) {
            delete _resource;                    // Free old
            _resource = new Resource(*rhs._resource);  // Copy new
        }
        return *this;
    }
    
    // Destructor
    ~Container() {
        delete _resource;
    }
};
```

**Copy-and-Swap Idiom** (advanced):
```cpp
Container& operator=(const Container& rhs) {
    Container temp(rhs);     // Copy using copy constructor
    swap(_resource, temp._resource);  // Swap pointers
    return *this;            // temp destructor cleans up old resource
}
```

### Abstract Classes and Interfaces

**Abstract Class Hierarchy**:
```
        [AAnimal] (abstract)
        /        \
    [Dog]      [Cat]  (concrete)
```

**Can't instantiate abstract**:
```cpp
AAnimal* a = new AAnimal();  // Compile error
AAnimal* d = new Dog();       // OK - Dog is concrete
```

**Pure Virtual Functions**:
```cpp
// Pure virtual - no implementation required in base class
virtual void makeSound() const = 0;

// Virtual - has default implementation, can be overridden
virtual void move() { std::cout << "Moving..." << std::endl; }
```

**Interface vs Abstract Class**:

**Interface** (pure abstract):
```cpp
class IAnimal {
public:
    virtual ~IAnimal() {}
    virtual void makeSound() const = 0;
    virtual void eat() const = 0;
    virtual void sleep() const = 0;
    // No member variables
    // No implementation
};
```

**Abstract Class**:
```cpp
class Animal {
protected:
    std::string type;  // Member variable
public:
    virtual ~Animal() {}
    virtual void makeSound() const = 0;  // Pure virtual
    virtual void move() const {          // Implemented
        std::cout << "Moving..." << std::endl;
    }
    std::string getType() const { return type; }  // Concrete method
};
```

### Object Slicing

**The Problem**:
```cpp
Dog dog;
Animal animal = dog;  // Object slicing!

animal.makeSound();  // Calls Animal::makeSound, not Dog::makeSound
// The "Dog-ness" is sliced off, only Animal part remains
```

**Why?**
```
Dog object in memory:
  [Animal part: vptr, type]
  [Dog part: _brain]

When assigned to Animal:
  Animal animal = dog;
  
Only Animal part is copied:
  [Animal part: vptr→Animal, type]
  
Dog part is lost (sliced off):
  [Dog part: _brain] ← Lost!
```

**Solution**: Use pointers or references
```cpp
Animal* animal = new Dog();  // No slicing - pointer to whole Dog
animal->makeSound();          // Calls Dog::makeSound (polymorphism)

Animal& animalRef = dog;      // No slicing - reference to whole Dog
animalRef.makeSound();        // Calls Dog::makeSound
```

**Copy Through Base Class Pointer**:
```cpp
Animal* a1 = new Dog();
Animal* a2 = new Animal(*a1);  // Slicing! Only copies Animal part

// Solution: Virtual clone method
class Animal {
    virtual Animal* clone() const = 0;
};

class Dog : public Animal {
    Animal* clone() const {
        return new Dog(*this);  // Correct Dog copy
    }
};

Animal* a2 = a1->clone();  // Proper Dog copy
```

### Virtual Destructor Necessity

**Without Virtual Destructor**:
```cpp
class Base {
public:
    ~Base() { std::cout << "Base destroyed" << std::endl; }
};

class Derived : public Base {
    int* data;
public:
    Derived() : data(new int[100]) {}
    ~Derived() {
        delete[] data;
        std::cout << "Derived destroyed" << std::endl;
    }
};

Base* ptr = new Derived();
delete ptr;  // Only calls Base::~Base()!
             // Derived::~Derived() never called
             // Memory leak! (data not freed)

Output:
  "Base destroyed"  ← Only base destructor!
```

**With Virtual Destructor**:
```cpp
class Base {
public:
    virtual ~Base() { std::cout << "Base destroyed" << std::endl; }
};

// ... same Derived class ...

Base* ptr = new Derived();
delete ptr;  // Calls Derived::~Derived(), then Base::~Base()

Output:
  "Derived destroyed"
  "Base destroyed"  ← Both destructors called!
```

**Rule**: If a class has any virtual functions, it should have a virtual destructor.

## Resources

### Documentation
- [cppreference.com - Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [cppreference.com - Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)
- [cppreference.com - Polymorphism](https://en.cppreference.com/w/cpp/language/object#Polymorphic_objects)
- [cppreference.com - Virtual Destructors](https://en.cppreference.com/w/cpp/language/destructor#Virtual_destructors)
- [cppreference.com - Rule of Three](https://en.cppreference.com/w/cpp/language/rule_of_three)

### Articles and Tutorials
- [LearnCPP.com - Virtual Functions](https://www.learncpp.com/cpp-tutorial/virtual-functions/)
- [LearnCPP.com - Pure Virtual Functions](https://www.learncpp.com/cpp-tutorial/pure-virtual-functions-abstract-base-classes-and-interface-classes/)
- [GeeksforGeeks - Polymorphism](https://www.geeksforgeeks.org/polymorphism-in-c/)
- [GeeksforGeeks - Abstract Classes](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)
- [GeeksforGeeks - Deep Copy vs Shallow Copy](https://www.geeksforgeeks.org/shallow-copy-and-deep-copy-in-c/)

### Books
- "Effective C++" by Scott Meyers (Item 7: Declare destructors virtual in polymorphic base classes)
- "More Effective C++" by Scott Meyers (Item 33: Make non-leaf classes abstract)
- "C++ Primer" by Stanley Lippman (Inheritance and Polymorphism chapters)
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI was **not** used in the development of this project. All code was written manually to ensure full understanding of:
- Virtual functions and polymorphism mechanisms
- Virtual destructors and their importance
- Deep copy implementation for derived classes
- Abstract classes and pure virtual functions
- Object slicing and how to avoid it

The README documentation was also written without AI assistance, based on understanding gained through:
- Reading official C++ documentation
- Studying polymorphism and inheritance patterns
- Implementing and testing virtual functions
- Debugging memory issues with improper copying
- Understanding vtable mechanics

This hands-on approach ensured deep comprehension of polymorphism, inheritance, and proper resource management in class hierarchies.

## Testing

### Exercise 00 Tests

Test polymorphism:
```cpp
const Animal* meta = new Animal();
const Animal* dog = new Dog();
const Animal* cat = new Cat();

std::cout << dog->getType() << std::endl;  // "Dog"
std::cout << cat->getType() << std::endl;  // "Cat"

cat->makeSound();   // "Meow! Meow!" (polymorphic call)
dog->makeSound();   // "Woof! Woof!"
meta->makeSound();  // "Generic animal sound"

delete meta;  // Verify virtual destructor works
delete dog;
delete cat;
```

Test WrongAnimal (no polymorphism):
```cpp
const WrongAnimal* wrong = new WrongCat();
wrong->makeSound();  // Calls WrongAnimal::makeSound (no polymorphism!)
```

**Verify**:
- Correct sound for each animal type
- Virtual destructor calls (derived then base)
- WrongAnimal demonstrates lack of polymorphism

### Exercise 01 Tests

Test deep copy:
```cpp
Dog basic;
{
    Dog tmp = basic;  // Deep copy constructor
    // Modify tmp's brain
    // Verify basic unaffected
}
// tmp destroyed - verify basic's brain still intact
```

Test assignment:
```cpp
Dog dog1;
Dog dog2;
dog2 = dog1;  // Deep copy assignment
// Verify independent brains
```

Test array of animals:
```cpp
const Animal* animals[10];
for (int i = 0; i < 5; i++)
    animals[i] = new Dog();
for (int i = 5; i < 10; i++)
    animals[i] = new Cat();
    
// Use animals...
for (int i = 0; i < 10; i++)
    animals[i]->makeSound();
    
// Clean up
for (int i = 0; i < 10; i++)
    delete animals[i];  // Virtual destructor ensures proper cleanup
```

### Exercise 02 Tests

Test abstract class:
```cpp
// This should NOT compile:
// AAnimal* animal = new AAnimal();

// This should compile:
AAnimal* dog = new Dog();
AAnimal* cat = new Cat();

dog->makeSound();  // Polymorphic call
cat->makeSound();

delete dog;
delete cat;
```

**Verify**:
- Cannot instantiate AAnimal
- Can instantiate Dog and Cat
- Polymorphism still works
- Virtual destructor works

### Memory Testing

Run all exercises with Valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./executable
```

**Check for**:
- Memory leaks (especially Brain objects)
- Invalid reads/writes
- Double frees (from shallow copy)
- Use of freed memory (dangling pointers)

**Common Issues**:
```bash
# Shallow copy → double free:
==12345== Invalid free() / delete / delete[] / realloc()
==12345== Address 0x... is ... bytes inside a block of size ... free'd

# Forgot to delete Brain → memory leak:
==12345== 100 bytes in 1 blocks are definitely lost in loss record
==12345== at malloc/new

# No virtual destructor → derived destructor not called:
==12345== 400 bytes in 1 blocks are definitely lost
==12345== (Brain not freed because Dog destructor not called)
```

### Deep Copy Verification

```cpp
void testDeepCopy() {
    Dog dog1;
    dog1.getBrain()->ideas[0] = "Original idea";
    
    Dog dog2(dog1);  // Copy constructor
    dog2.getBrain()->ideas[0] = "Modified idea";
    
    // Verify dog1's idea is still "Original idea"
    assert(dog1.getBrain()->ideas[0] == "Original idea");
    assert(dog2.getBrain()->ideas[0] == "Modified idea");
    
    Dog dog3;
    dog3 = dog1;  // Assignment operator
    dog3.getBrain()->ideas[0] = "Another idea";
    
    // Verify dog1 unaffected
    assert(dog1.getBrain()->ideas[0] == "Original idea");
}
```

## Notes

- All code follows the **C++98 standard** (no C++11 or later features)
- **Virtual destructors** are mandatory for polymorphic base classes
- **Deep copy** is required for classes with pointer members in inheritance hierarchies
- Abstract classes cannot be instantiated
- Pure virtual functions must be implemented in concrete derived classes
- Object slicing occurs when copying derived objects to base class by value
- Use pointers or references for polymorphic behavior
- Virtual function calls have minimal overhead (one indirection)
- Protected members are accessible in derived classes but not outside
- Call base class constructors/destructors explicitly in derived classes

## Author

**viceda-s**  
*42 Luxembourg*

---

*For questions, issues, or suggestions, please refer to the 42 project evaluation guidelines.*
