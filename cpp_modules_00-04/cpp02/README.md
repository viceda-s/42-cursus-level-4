# CPP Module 02

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 02 focuses on **ad-hoc polymorphism, operator overloading, and the Orthodox Canonical Form (Rule of Three)**. This module deepens understanding of how to create robust classes in C++ and introduces fixed-point arithmetic as a practical application. The project explores operator overloading to create intuitive interfaces for custom types, understanding copy semantics, and implementing the Orthodox Canonical Form correctly. The module consists of four exercises:

- **Exercise 00 (My First Class in Orthodox Canonical Form)**: Creating a basic fixed-point number class implementing the Rule of Three
- **Exercise 01 (Towards a more useful fixed-point number class)**: Adding conversions between int, float, and fixed-point, plus stream insertion
- **Exercise 02 (Now we're talking)**: Implementing comparison operators, arithmetic operators, and increment/decrement
- **Exercise 03 (BSP)**: Practical application - Binary Space Partitioning to determine if a point is inside a triangle

### Learning Objectives

- Understanding and implementing the Orthodox Canonical Form (Rule of Three)
- Mastering operator overloading for custom types
- Learning fixed-point number representation and arithmetic
- Understanding ad-hoc polymorphism through function/operator overloading
- Working with bit shifting for fractional representation
- Implementing conversion operators and constructors
- Overloading stream insertion and extraction operators
- Understanding const correctness in operator overloading
- Differentiating prefix and postfix increment/decrement operators

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

#### Exercise 00 - Orthodox Canonical Form
```bash
cd ex00
make
./fixed
```

#### Exercise 01 - Constructors and Conversions
```bash
cd ex01
make
./fixed
```

#### Exercise 02 - Operator Overloading
```bash
cd ex02
make
./fixed
```

#### Exercise 03 - BSP (Point in Triangle)
```bash
cd ex03
make
./bsp
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
cpp02/
├── ex00/                    # Orthodox Canonical Form basics
│   ├── Fixed.cpp           # Fixed class implementation
│   ├── Fixed.hpp           # Fixed class declaration
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex01/                    # Conversions and stream insertion
│   ├── Fixed.cpp           # Extended Fixed implementation
│   ├── Fixed.hpp           # Extended Fixed declaration
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex02/                    # Full operator overloading
│   ├── Fixed.cpp           # Complete Fixed implementation
│   ├── Fixed.hpp           # Complete Fixed declaration
│   ├── main.cpp            # Test program
│   └── Makefile
└── ex03/                    # BSP application
    ├── Fixed.cpp           # Fixed class
    ├── Fixed.hpp
    ├── Point.cpp           # Point class using Fixed
    ├── Point.hpp
    ├── bsp.cpp             # Binary Space Partitioning algorithm
    ├── main.cpp            # Test program
    └── Makefile
```

## Features

### Exercise 00: My First Class in Orthodox Canonical Form

Creates a basic Fixed-point number class following the Orthodox Canonical Form:

**Fixed Class**:
- **Private Attributes**:
  - `int _value`: Raw integer value storing the fixed-point number
  - `static const int _fractionalBits`: Number of fractional bits (8)

- **Orthodox Canonical Form (Rule of Three)**:
  - `Fixed()`: Default constructor (initializes to 0)
  - `~Fixed()`: Destructor
  - `Fixed(const Fixed& copy)`: Copy constructor
  - `Fixed& operator=(const Fixed& rhs)`: Copy assignment operator

- **Member Functions**:
  - `int getRawBits() const`: Returns the raw value
  - `void setRawBits(int const raw)`: Sets the raw value

**Key Concepts**:
```cpp
Fixed a;              // Default constructor
Fixed b(a);           // Copy constructor
Fixed c;
c = b;                // Copy assignment operator
// Destructor called automatically for a, b, c
```

**Orthodox Canonical Form Explained**:
The **Rule of Three** states that if you need to define one of these three, you probably need all three:
1. Destructor
2. Copy constructor
3. Copy assignment operator

**Why?** If your class manages resources (memory, file handles, etc.), you need to control what happens when objects are copied or destroyed.

**Implementation Pattern**:
```cpp
class Fixed {
public:
    // Default constructor
    Fixed() : _value(0) {
        std::cout << "Default constructor called" << std::endl;
    }
    
    // Destructor
    ~Fixed() {
        std::cout << "Destructor called" << std::endl;
    }
    
    // Copy constructor
    Fixed(const Fixed& copy) : _value(copy._value) {
        std::cout << "Copy constructor called" << std::endl;
    }
    
    // Copy assignment operator
    Fixed& operator=(const Fixed& rhs) {
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &rhs)  // Self-assignment check
            this->_value = rhs._value;
        return *this;
    }
};
```

### Exercise 01: Towards a more useful fixed-point number class

Extends the Fixed class with conversions and output:

**New Constructors**:
- `Fixed(const int n)`: Converts integer to fixed-point
- `Fixed(const float f)`: Converts float to fixed-point

**Conversion Functions**:
- `float toFloat() const`: Converts fixed-point to float
- `int toInt() const`: Converts fixed-point to int

**Stream Insertion**:
- `std::ostream& operator<<(std::ostream& out, const Fixed& fixed)`: Overload for printing

**Fixed-Point Arithmetic Explained**:

Fixed-point numbers represent fractional values using integers. The number is split into:
- **Integer part**: High bits
- **Fractional part**: Low bits

With 8 fractional bits:
```
Value = raw_value / 2^8 = raw_value / 256

Example:
42.42 in fixed-point (8 fractional bits):
- Multiply by 256: 42.42 * 256 = 10859.52 ≈ 10860
- Store 10860 as raw value
- To get back: 10860 / 256 = 42.421875 ≈ 42.42
```

**Bit Representation**:
```
32-bit int with 8 fractional bits:
[24 integer bits | 8 fractional bits]

Example: 42.5
Integer part: 42 << 8 = 10752
Fractional part: 0.5 * 256 = 128
Total raw value: 10752 + 128 = 10880

Verification: 10880 / 256 = 42.5 ✓
```

**Implementation**:
```cpp
// Int to fixed-point
Fixed::Fixed(const int n) : _value(n << _fractionalBits) {
    // Shift left by 8 bits (multiply by 256)
}

// Float to fixed-point
Fixed::Fixed(const float f) : _value(roundf(f * (1 << _fractionalBits))) {
    // Multiply by 256 and round
}

// Fixed-point to float
float Fixed::toFloat() const {
    return (float)_value / (1 << _fractionalBits);
    // Divide by 256
}

// Fixed-point to int
int Fixed::toInt() const {
    return _value >> _fractionalBits;
    // Shift right by 8 bits (divide by 256, truncate)
}

// Stream insertion
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
```

**Usage Example**:
```cpp
Fixed a;                    // 0
Fixed const b(10);          // 10.0
Fixed const c(42.42f);      // 42.42
Fixed const d(b);           // Copy of b (10.0)

std::cout << "a is " << a << std::endl;  // 0
std::cout << "b is " << b << std::endl;  // 10
std::cout << "c is " << c << std::endl;  // 42.4219
std::cout << "d is " << d << std::endl;  // 10
```

### Exercise 02: Now we're talking

Implements full operator overloading for the Fixed class:

**Comparison Operators**:
- `bool operator>(const Fixed& rhs) const`
- `bool operator<(const Fixed& rhs) const`
- `bool operator>=(const Fixed& rhs) const`
- `bool operator<=(const Fixed& rhs) const`
- `bool operator==(const Fixed& rhs) const`
- `bool operator!=(const Fixed& rhs) const`

**Arithmetic Operators**:
- `Fixed operator+(const Fixed& rhs) const`
- `Fixed operator-(const Fixed& rhs) const`
- `Fixed operator*(const Fixed& rhs) const`
- `Fixed operator/(const Fixed& rhs) const`

**Increment/Decrement Operators**:
- `Fixed& operator++()`: Prefix increment (++a)
- `Fixed operator++(int)`: Postfix increment (a++)
- `Fixed& operator--()`: Prefix decrement (--a)
- `Fixed operator--(int)`: Postfix decrement (a--)

**Static Member Functions**:
- `static Fixed& min(Fixed& a, Fixed& b)`: Returns the smaller
- `static const Fixed& min(const Fixed& a, const Fixed& b)`
- `static Fixed& max(Fixed& a, Fixed& b)`: Returns the greater
- `static const Fixed& max(const Fixed& a, const Fixed& b)`

**Operator Overloading Explained**:

**Comparison Operators** (member functions):
```cpp
bool Fixed::operator>(const Fixed& rhs) const {
    return this->_value > rhs._value;
    // Compare raw values directly
}

bool Fixed::operator==(const Fixed& rhs) const {
    return this->_value == rhs._value;
}
```

**Arithmetic Operators** (member functions):
```cpp
Fixed Fixed::operator+(const Fixed& rhs) const {
    Fixed result;
    result.setRawBits(this->_value + rhs._value);
    return result;
}

Fixed Fixed::operator*(const Fixed& rhs) const {
    Fixed result;
    // Multiply raw values, then divide by scale factor
    // (a/256) * (b/256) = (a*b) / 65536 = (a*b/256) / 256
    result.setRawBits((this->_value * rhs._value) >> _fractionalBits);
    return result;
}

Fixed Fixed::operator/(const Fixed& rhs) const {
    Fixed result;
    // Divide: (a/256) / (b/256) = a/b
    // But we need result in fixed-point: (a/b) * 256 = (a*256) / b
    result.setRawBits((this->_value << _fractionalBits) / rhs._value);
    return result;
}
```

**Increment/Decrement** (prefix vs postfix):
```cpp
// Prefix increment (++a) - returns reference
Fixed& Fixed::operator++() {
    this->_value++;  // Increment by smallest value (1/256)
    return *this;     // Return reference to this
}

// Postfix increment (a++) - returns copy
Fixed Fixed::operator++(int) {
    Fixed temp(*this);  // Save current value
    ++(*this);          // Increment using prefix
    return temp;        // Return old value
}

// Usage:
Fixed a(5.5f);
Fixed b = ++a;  // a = 5.50390625, b = 5.50390625 (same reference)
Fixed c = a++;  // c = 5.50390625, a = 5.5078125 (c is old value)
```

**Why postfix takes int?**
The `int` parameter distinguishes postfix from prefix (it's not used, just for overload resolution).

**Static min/max functions**:
```cpp
static Fixed& min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;  // Return reference to smaller
}

static const Fixed& min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;  // Const version for const objects
}
```

**Usage Example**:
```cpp
Fixed a;
Fixed const b(Fixed(5.05f) * Fixed(2));  // 10.1

std::cout << a << std::endl;        // 0
std::cout << ++a << std::endl;      // 0.00390625 (1/256)
std::cout << a << std::endl;        // 0.00390625
std::cout << a++ << std::endl;      // 0.00390625
std::cout << a << std::endl;        // 0.0078125 (2/256)

std::cout << b << std::endl;        // 10.1016
std::cout << Fixed::max(a, b) << std::endl;  // 10.1016
```

### Exercise 03: BSP (Binary Space Partitioning)

Applies the Fixed class to solve a geometric problem:

**Problem**: Determine if a point P is inside a triangle ABC.

**Classes**:

**Point Class**:
- **Attributes**: 
  - `Fixed const x`: X-coordinate (const, cannot change after construction)
  - `Fixed const y`: Y-coordinate (const, cannot change after construction)
- **Constructors**:
  - `Point()`: Default (0, 0)
  - `Point(const float x, const float y)`: Initialize with floats
  - `Point(const Point& copy)`: Copy constructor
- **Methods**:
  - `Fixed getX() const`: Returns x-coordinate
  - `Fixed getY() const`: Returns y-coordinate

**BSP Function**:
```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point);
```
Returns `true` if point is inside triangle ABC, `false` otherwise.

**Algorithm Explanation**:

**Method 1: Barycentric Coordinates**

A point P is inside triangle ABC if it can be expressed as:
```
P = u*A + v*B + w*C
where u + v + w = 1 and u, v, w >= 0
```

**Method 2: Cross Product (Area-based)**

Calculate signed areas using cross product:
```
For triangle ABC and point P:

1. Calculate area of triangle ABC
2. Calculate area of triangle PAB
3. Calculate area of triangle PBC
4. Calculate area of triangle PCA

If: area(PAB) + area(PBC) + area(PCA) == area(ABC)
Then: P is inside (or on edge) of triangle ABC
```

**Cross Product for Area**:
```cpp
// Signed area of triangle formed by 3 points
// Area = 0.5 * |cross product of vectors|
Fixed triangleArea(Point const &a, Point const &b, Point const &c) {
    // Vectors: AB and AC
    // Cross product: (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)
    Fixed area = ((b.getX() - a.getX()) * (c.getY() - a.getY()) - 
                  (c.getX() - a.getX()) * (b.getY() - a.getY())) / Fixed(2);
    return (area < Fixed(0)) ? area * Fixed(-1) : area;  // Absolute value
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed areaABC = triangleArea(a, b, c);
    Fixed areaPAB = triangleArea(point, a, b);
    Fixed areaPBC = triangleArea(point, b, c);
    Fixed areaPCA = triangleArea(point, c, a);
    
    // Check if on edge (any sub-area is 0)
    if (areaPAB == Fixed(0) || areaPBC == Fixed(0) || areaPCA == Fixed(0))
        return false;
    
    // Check if inside (sum of sub-areas equals total area)
    return (areaPAB + areaPBC + areaPCA) == areaABC;
}
```

**Method 3: Same Side Test**

For point P to be inside triangle ABC:
- P and C must be on the same side of line AB
- P and A must be on the same side of line BC
- P and B must be on the same side of line CA

**Visual Representation**:
```
        A
        /\
       /  \
      / P? \
     /______\
    B        C

Sub-triangles when P is inside:
- PAB (area 1)
- PBC (area 2)
- PCA (area 3)

If area1 + area2 + area3 == total_area → P is inside
```

**Edge Cases**:
- Point on edge (area of one sub-triangle is 0)
- Point on vertex (two sub-triangles have 0 area)
- Degenerate triangle (area is 0)
- Point outside triangle

**Implementation Considerations**:
- Handle const Point members (need to initialize in constructor initializer list)
- Use Fixed arithmetic for precision
- Handle edge and vertex cases appropriately
- Consider using epsilon for floating-point comparison tolerance

## Algorithm and Data Structure Explanation

### Orthodox Canonical Form (Rule of Three)

**Why do we need it?**

When a class manages resources (memory, file handles, etc.), the default copy operations provided by the compiler perform **shallow copies**, which can lead to:
1. Double deletion (same resource freed twice)
2. Memory leaks (resource not freed)
3. Dangling pointers (accessing freed memory)

**The Rule of Three** states: If you define any of these, define all three:
1. Destructor
2. Copy constructor  
3. Copy assignment operator

**Example Problem** (without Rule of Three):
```cpp
class Dynamic {
    int* data;
public:
    Dynamic(int val) : data(new int(val)) {}
    ~Dynamic() { delete data; }
    // No copy constructor or assignment operator!
};

Dynamic a(42);
Dynamic b = a;  // Shallow copy! Both a.data and b.data point to same memory
// When b is destroyed: delete data
// When a is destroyed: delete data  → DOUBLE FREE! Crash!
```

**Solution** (with Rule of Three):
```cpp
class Dynamic {
    int* data;
public:
    Dynamic(int val) : data(new int(val)) {}
    
    ~Dynamic() {
        delete data;
    }
    
    // Copy constructor - deep copy
    Dynamic(const Dynamic& other) : data(new int(*other.data)) {
        // Allocate new memory and copy value
    }
    
    // Copy assignment operator - deep copy
    Dynamic& operator=(const Dynamic& other) {
        if (this != &other) {  // Self-assignment check
            delete data;        // Free old resource
            data = new int(*other.data);  // Allocate and copy
        }
        return *this;
    }
};
```

**For Fixed class** (no dynamic memory):
Since Fixed doesn't allocate dynamic memory, the default operations work fine. However, we implement them explicitly to:
1. Add debug messages
2. Practice the pattern
3. Ensure correct behavior even if class changes later

### Fixed-Point Arithmetic

**What is Fixed-Point?**

A way to represent fractional numbers using integers. Unlike floating-point, the decimal point position is "fixed".

**Format**: Q notation
- Q8.8: 8 integer bits, 8 fractional bits (total 16 bits)
- Q24.8: 24 integer bits, 8 fractional bits (total 32 bits) ← We use this

**Representation**:
```
32-bit integer with 8 fractional bits:
[bit 31-8: integer part | bit 7-0: fractional part]

Example: 42.5
Binary:     00000000000000000000001010.10000000
            |--------integer--------|--frac--|
            =     42 (integer)      + 128/256 (frac)
Raw value:  (42 << 8) + 128 = 10880

Conversion: 10880 / 256 = 42.5
```

**Operations**:

**Addition/Subtraction**: Direct operation on raw values
```
(a/256) + (b/256) = (a + b)/256
Therefore: result.raw = a.raw + b.raw
```

**Multiplication**: Need to adjust scale
```
(a/256) * (b/256) = (a * b) / 65536 = (a * b) / 256 / 256
Therefore: result.raw = (a.raw * b.raw) >> 8
```

**Division**: Need to adjust scale
```
(a/256) / (b/256) = a / b
But result needs to be in fixed-point: (a/b) * 256
Therefore: result.raw = (a.raw << 8) / b.raw
```

**Advantages of Fixed-Point**:
- Faster than floating-point (integer operations)
- Deterministic (no rounding errors)
- Predictable precision
- Good for embedded systems, game engines, financial calculations

**Disadvantages**:
- Limited range (compared to floating-point)
- Fixed precision (can't dynamically adjust)
- More complex to implement
- Overflow possible with multiplication

**Range with Q24.8**:
- Minimum: -2^23 = -8,388,608
- Maximum: 2^23 - 1/256 ≈ 8,388,607.996
- Precision: 1/256 ≈ 0.00390625

### Operator Overloading

**What is Operator Overloading?**

Defining custom behavior for operators (`+`, `-`, `*`, `/`, `<<`, etc.) when used with user-defined types.

**Why?**
To make custom types behave like built-in types:
```cpp
// Built-in types:
int a = 5, b = 10;
int c = a + b;  // Natural syntax

// With operator overloading:
Fixed a(5), b(10);
Fixed c = a + b;  // Same natural syntax!
```

**Types of Operators**:

**1. Member Functions** (most operators):
```cpp
class Fixed {
    Fixed operator+(const Fixed& rhs) const;  // this + rhs
    bool operator<(const Fixed& rhs) const;   // this < rhs
};

// Usage: a + b  →  a.operator+(b)
```

**2. Non-member Functions** (stream operators, symmetry):
```cpp
// Stream insertion
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
// Usage: std::cout << fixed  →  operator<<(std::cout, fixed)

// Symmetry example:
Fixed operator*(int lhs, const Fixed& rhs);  // int * Fixed
// Complements: Fixed operator*(const Fixed& rhs) const;  // Fixed * int
```

**3. Prefix vs Postfix**:
```cpp
Fixed& operator++();      // Prefix: ++a (returns reference, no copy)
Fixed operator++(int);    // Postfix: a++ (returns copy, has dummy int param)
```

**Return Types**:
- **Arithmetic operators**: Return new object (by value)
- **Comparison operators**: Return `bool`
- **Assignment operators**: Return reference to `*this`
- **Prefix increment**: Return reference to `*this`
- **Postfix increment**: Return copy (old value)
- **Stream operators**: Return reference to stream

**Const Correctness**:
```cpp
Fixed operator+(const Fixed& rhs) const;
//                     ^1         ^2

// ^1: Parameter is const (doesn't modify argument)
// ^2: Method is const (doesn't modify *this)
```

**Implementation Guidelines**:
1. Prefer member functions for operators that modify the object
2. Use non-member functions for symmetric operations
3. Return by const reference when possible (avoid copies)
4. Use const correctness
5. Implement compound assignments first, then use them:
```cpp
Fixed& operator+=(const Fixed& rhs) {
    this->_value += rhs._value;
    return *this;
}

Fixed operator+(const Fixed& rhs) const {
    Fixed result(*this);
    result += rhs;  // Reuse +=
    return result;
}
```

### Stream Insertion Operator

**Why non-member function?**

```cpp
// If it were a member function:
class Fixed {
    std::ostream& operator<<(std::ostream& out) const;
};

// Usage would be:
fixed.operator<<(std::cout);  // fixed << std::cout  → backwards!

// As non-member function:
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

// Usage:
std::cout << fixed;  // operator<<(std::cout, fixed)  → natural!
```

**Implementation**:
```cpp
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();  // Convert to float for output
    return out;              // Return stream for chaining
}

// Enables chaining:
std::cout << "Value: " << fixed << " done" << std::endl;
```

### Binary Space Partitioning (BSP)

**What is BSP?**

A method of recursively subdividing space by hyperplanes (in 2D, lines). Used in computer graphics, collision detection, and spatial queries.

**For Point-in-Triangle**:

Not true BSP, but uses similar geometric principles (half-plane tests).

**Mathematical Foundation**:

**Cross Product in 2D**:
```
Given vectors:
  u = (ux, uy)
  v = (vx, vy)

Cross product (z-component of 3D cross product):
  u × v = ux * vy - uy * vx

Interpretation:
  > 0: v is counterclockwise from u
  < 0: v is clockwise from u
  = 0: v is collinear with u
```

**Triangle Area from Cross Product**:
```
Triangle ABC area = |AB × AC| / 2

Where:
  AB = B - A = (Bx - Ax, By - Ay)
  AC = C - A = (Cx - Ax, Cy - Ay)

Area = |(Bx - Ax)(Cy - Ay) - (Cx - Ax)(By - Ay)| / 2
```

**Point-in-Triangle Test** (Area Method):
```
Point P is inside triangle ABC if:
  area(PAB) + area(PBC) + area(PCA) = area(ABC)

Intuition:
  If P is inside, the three sub-triangles perfectly partition ABC.
  If P is outside, the sum will be greater than the total area.
```

**Edge Cases**:
```
P on edge:    One sub-area is 0
P on vertex:  Two sub-areas are 0
P outside:    Sum of sub-areas > total area
Degenerate:   Triangle area is 0 (colinear points)
```

**Alternative Method** (Barycentric Coordinates):
```
Express P as weighted average of vertices:
  P = u*A + v*B + w*C
  where u + v + w = 1

P is inside if u, v, w are all >= 0

Calculation:
  denominator = (B.y - C.y)(A.x - C.x) + (C.x - B.x)(A.y - C.y)
  u = [(B.y - C.y)(P.x - C.x) + (C.x - B.x)(P.y - C.y)] / denominator
  v = [(C.y - A.y)(P.x - C.x) + (A.x - C.x)(P.y - C.y)] / denominator
  w = 1 - u - v
```

**Time Complexity**: O(1) - constant time operations

## Resources

### Documentation
- [cppreference.com - Operator Overloading](https://en.cppreference.com/w/cpp/language/operators)
- [cppreference.com - Rule of Three](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [cppreference.com - Copy Constructor](https://en.cppreference.com/w/cpp/language/copy_constructor)
- [cppreference.com - Copy Assignment](https://en.cppreference.com/w/cpp/language/copy_assignment)
- [cppreference.com - Stream Operators](https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt)

### Articles and Tutorials
- [LearnCPP.com - Operator Overloading](https://www.learncpp.com/cpp-tutorial/introduction-to-operator-overloading/)
- [LearnCPP.com - Rule of Three](https://www.learncpp.com/cpp-tutorial/the-rule-of-three/)
- [GeeksforGeeks - Operator Overloading](https://www.geeksforgeeks.org/operator-overloading-c/)
- [Fixed-Point Arithmetic](https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html)
- [Point in Triangle Test](https://blackpawn.com/texts/pointinpoly/)

### Books
- "Effective C++" by Scott Meyers (Items on operator overloading and Rule of Three)
- "C++ Primer" by Stanley Lippman (Operator Overloading chapter)
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI was **not** used in the development of this project. All code was written manually to ensure full understanding of:
- Orthodox Canonical Form implementation
- Operator overloading mechanisms
- Fixed-point arithmetic operations
- Binary space partitioning algorithms
- Copy semantics and const correctness

The README documentation was also written without AI assistance, based on understanding gained through:
- Reading official C++ documentation
- Studying operator overloading patterns
- Implementing and testing fixed-point arithmetic
- Understanding geometric algorithms
- Debugging operator precedence and const issues

This hands-on approach ensured deep comprehension of operator overloading and the Orthodox Canonical Form.

## Testing

### Exercise 00 Tests

Test Orthodox Canonical Form:
```cpp
Fixed a;
Fixed b(a);
Fixed c;
c = b;

std::cout << a.getRawBits() << std::endl;  // 0
std::cout << b.getRawBits() << std::endl;  // 0
std::cout << c.getRawBits() << std::endl;  // 0
```

**Verify**:
- Constructor messages
- Copy constructor message
- Assignment operator message
- Destructor messages

### Exercise 01 Tests

Test conversions:
```cpp
Fixed a;
Fixed const b(10);
Fixed const c(42.42f);
Fixed const d(b);

std::cout << "a is " << a << std::endl;  // 0
std::cout << "b is " << b << std::endl;  // 10
std::cout << "c is " << c << std::endl;  // 42.4219
std::cout << "d is " << d << std::endl;  // 10

std::cout << "a is " << a.toInt() << " as integer" << std::endl;
std::cout << "b is " << b.toInt() << " as integer" << std::endl;
std::cout << "c is " << c.toInt() << " as integer" << std::endl;
std::cout << "d is " << d.toInt() << " as integer" << std::endl;
```

**Verify precision**:
```cpp
Fixed test(0.5f);
std::cout << test << std::endl;  // Should be close to 0.5

Fixed test2(0.00390625f);  // 1/256 - smallest representable
std::cout << test2 << std::endl;  // Exactly 0.00390625
```

### Exercise 02 Tests

Test operators:
```cpp
Fixed a;
Fixed const b(Fixed(5.05f) * Fixed(2));

std::cout << a << std::endl;                      // 0
std::cout << ++a << std::endl;                    // 0.00390625
std::cout << a << std::endl;                      // 0.00390625
std::cout << a++ << std::endl;                    // 0.00390625
std::cout << a << std::endl;                      // 0.0078125
std::cout << b << std::endl;                      // 10.1016
std::cout << Fixed::max(a, b) << std::endl;       // 10.1016

// Comparison tests
Fixed x(10);
Fixed y(20);
std::cout << (x < y) << std::endl;   // 1 (true)
std::cout << (x > y) << std::endl;   // 0 (false)
std::cout << (x == y) << std::endl;  // 0 (false)
```

**Arithmetic tests**:
```cpp
Fixed a(10);
Fixed b(3);

std::cout << a + b << std::endl;  // 13
std::cout << a - b << std::endl;  // 7
std::cout << a * b << std::endl;  // 30
std::cout << a / b << std::endl;  // 3.33203
```

### Exercise 03 Tests

Test point-in-triangle:
```cpp
// Triangle vertices
Point a(0, 0);
Point b(10, 0);
Point c(5, 10);

// Test points
Point inside(5, 5);
Point outside(15, 5);
Point onEdge(5, 0);
Point onVertex(0, 0);

std::cout << "Inside: " << bsp(a, b, c, inside) << std::endl;     // true
std::cout << "Outside: " << bsp(a, b, c, outside) << std::endl;   // false
std::cout << "On edge: " << bsp(a, b, c, onEdge) << std::endl;    // false
std::cout << "On vertex: " << bsp(a, b, c, onVertex) << std::endl; // false
```

**Visual test cases**:
```
Test 1: Equilateral triangle
     (0,10)
       /\
      /  \
     /    \
    /______\
(0,0)      (10,0)

Points to test:
- (5, 3.33)  → inside
- (5, 10)    → outside (above)
- (-1, 5)    → outside (left)

Test 2: Right triangle
(0,10) |\
       | \
       |  \
       |___\
    (0,0) (10,0)

Points to test:
- (2, 2)     → inside
- (8, 8)     → outside
- (5, 5)     → on edge/inside (depends on implementation)
```

### Precision Tests

Test fixed-point precision:
```cpp
// Smallest increment
Fixed small(1.0f / 256.0f);  // 0.00390625
std::cout << small << std::endl;

// Precision loss in multiplication
Fixed a(0.5f);
Fixed b(0.5f);
Fixed c = a * b;  // 0.25
std::cout << c << std::endl;

// Division precision
Fixed x(1);
Fixed y(3);
Fixed z = x / y;  // 0.333...
std::cout << z << std::endl;
```

### Memory Testing

Run all exercises with Valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./executable
```

**Check for**:
- Memory leaks
- Invalid reads/writes  
- Use of uninitialized values
- Double frees

## Notes

- All code follows the **C++98 standard** (no C++11 or later features)
- Orthodox Canonical Form must be implemented for all classes
- Fixed-point uses 8 fractional bits (Q24.8 format)
- Operator overloading should be intuitive and follow conventions
- const correctness is important for all member functions that don't modify state
- Postfix increment/decrement are less efficient than prefix (require copy)
- For BSP, points on edges are typically considered outside
- Stream insertion operator must be a non-member function
- Division by zero should be handled appropriately
- Watch for overflow in fixed-point multiplication

## Author

**viceda-s**  
*42 Luxembourg*

---

*For questions, issues, or suggestions, please refer to the 42 project evaluation guidelines.*
