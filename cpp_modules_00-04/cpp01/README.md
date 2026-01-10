# CPP Module 01

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 01 focuses on **memory allocation, pointers, references, and the switch statement**. This module deepens understanding of memory management in C++ and introduces important concepts that distinguish C++ from C. The project explores the differences between stack and heap allocation, mastering pointers vs references, and understanding when to use each. The module consists of six exercises:

- **Exercise 00 (BraiiiiiiinnnzzzZ)**: Creating and destroying zombies on stack and heap, understanding memory allocation differences
- **Exercise 01 (Moar brainz!)**: Creating a horde of zombies using dynamic array allocation
- **Exercise 02 (HI THIS IS BRAIN)**: Understanding differences between pointers and references
- **Exercise 03 (Unnecessary violence)**: Implementing different weapon types, understanding references vs pointers in practical scenarios
- **Exercise 04 (Sed is for losers)**: String manipulation and file operations, creating a text replacement tool
- **Exercise 05 (Harl 2.0)**: Implementing a logging system with different severity levels
- **Exercise 06 (Harl filter)**: Extending the logging system with filtering capabilities using switch

### Learning Objectives

- Understanding stack vs heap memory allocation
- Mastering pointers and references in C++
- Learning when to use `new`/`delete` operators
- Understanding the differences between references and pointers
- Working with file streams (`std::ifstream`, `std::ofstream`)
- String manipulation and replacement algorithms
- Implementing member function pointers
- Using switch statements effectively

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

#### Exercise 00 - BraiiiiiiinnnzzzZ
```bash
cd ex00
make
./zombie
```

#### Exercise 01 - Zombie Horde
```bash
cd ex01
make
./zombie_horde
```

#### Exercise 02 - HI THIS IS BRAIN
```bash
cd ex02
make
./brain
```

#### Exercise 03 - Unnecessary Violence
```bash
cd ex03
make
./violence
```

#### Exercise 04 - Sed is for losers
```bash
cd ex04
make
./sed <filename> <s1> <s2>
# Creates <filename>.replace with s1 replaced by s2
```

#### Exercise 05 - Harl 2.0
```bash
cd ex05
make
./harl
```

#### Exercise 06 - Harl filter
```bash
cd ex06
make
./harlFilter <level>
# Levels: DEBUG, INFO, WARNING, ERROR
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
cpp01/
├── ex00/                    # Zombie - stack vs heap
│   ├── Zombie.cpp          # Zombie class implementation
│   ├── Zombie.hpp          # Zombie class declaration
│   ├── newZombie.cpp       # Creates zombie on heap
│   ├── randomChump.cpp     # Creates zombie on stack
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex01/                    # Zombie Horde - array allocation
│   ├── Zombie.cpp          # Zombie class implementation
│   ├── Zombie.hpp          # Zombie class declaration
│   ├── zombieHorde.cpp     # Creates zombie array
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex02/                    # Brain - pointers vs references
│   ├── main.cpp            # Demonstration program
│   └── Makefile
├── ex03/                    # Violence - weapon system
│   ├── Weapon.cpp          # Weapon class
│   ├── Weapon.hpp
│   ├── HumanA.cpp          # Human with weapon reference
│   ├── HumanA.hpp
│   ├── HumanB.cpp          # Human with weapon pointer
│   ├── HumanB.hpp
│   ├── main.cpp            # Test program
│   └── Makefile
├── ex04/                    # Sed replacement tool
│   ├── main.cpp            # File processing logic
│   └── Makefile
├── ex05/                    # Harl logging system
│   ├── Harl.cpp            # Harl class with logging methods
│   ├── Harl.hpp
│   ├── main.cpp            # Test different log levels
│   └── Makefile
└── ex06/                    # Harl filter
    ├── Harl.cpp            # Harl class implementation
    ├── Harl.hpp
    ├── main.cpp            # Filter by log level
    └── Makefile
```

## Features

### Exercise 00: BraiiiiiiinnnzzzZ (Stack vs Heap)

Demonstrates the difference between stack and heap allocation:

**Zombie Class**:
- **Constructor**: Takes zombie name
- **Destructor**: Announces zombie destruction
- **Method**: `announce()` - zombie announces itself

**Functions**:
- `Zombie* newZombie(std::string name)`: Creates zombie on **heap** (returns pointer)
- `void randomChump(std::string name)`: Creates zombie on **stack** (local scope)

**Key Concepts**:
```cpp
// Heap allocation - survives function scope
Zombie* heapZombie = newZombie("Heap");
// Must be manually deleted
delete heapZombie;

// Stack allocation - destroyed when out of scope
randomChump("Stack");  // Zombie destroyed automatically at end of function
```

**Memory Behavior**:
- **Stack zombie**: Automatic destruction when function returns
- **Heap zombie**: Persists until explicitly deleted
- **Memory leak**: Forgetting to delete heap zombies

### Exercise 01: Moar brainz! (Dynamic Arrays)

Creates a horde of zombies using dynamic array allocation:

**Function**:
```cpp
Zombie* zombieHorde(int N, std::string name);
```
- Allocates array of N zombies on heap
- All zombies have the same name
- Returns pointer to first zombie

**Key Concepts**:
- Array allocation: `new Zombie[N]`
- Array deallocation: `delete[] zombies` (note the `[]`)
- Default constructor needed (zombies initialized without parameters)
- Placement construction or setter methods to name zombies

**Memory Management**:
```cpp
Zombie* horde = zombieHorde(10, "Horde");
// Use the horde...
for (int i = 0; i < 10; i++)
    horde[i].announce();
// Clean up
delete[] horde;  // Must use delete[] for arrays!
```

### Exercise 02: HI THIS IS BRAIN (Pointers vs References)

Demonstrates pointers and references with a simple string:

**Program Flow**:
1. Create a string: `std::string str = "HI THIS IS BRAIN"`
2. Create a pointer to the string: `std::string* stringPTR = &str`
3. Create a reference to the string: `std::string& stringREF = str`
4. Print memory addresses (string, pointer, reference)
5. Print values (string, through pointer, through reference)

**Key Learning**:
```cpp
std::string str = "HI THIS IS BRAIN";
std::string* ptr = &str;  // Pointer: stores address
std::string& ref = str;   // Reference: alias to str

// Access
std::cout << *ptr;  // Dereference pointer
std::cout << ref;   // Reference used directly

// Addresses
&str == ptr        // Pointer stores address
&ref == &str       // Reference has same address as original
```

### Exercise 03: Unnecessary Violence (References vs Pointers in Practice)

Implements a weapon system with two human types:

**Weapon Class**:
- **Attribute**: `std::string type`
- **Methods**: `getType()`, `setType()`

**HumanA Class**:
- **Has**: Weapon **reference** (`Weapon& _weapon`)
- **Constructor**: `HumanA(std::string name, Weapon& weapon)`
- **Behavior**: Always armed (weapon must exist at construction)
- **Cannot**: Change which weapon they're holding

**HumanB Class**:
- **Has**: Weapon **pointer** (`Weapon* _weapon`)
- **Constructor**: `HumanB(std::string name)` (no weapon required)
- **Method**: `setWeapon(Weapon& weapon)` (can arm later)
- **Behavior**: May be unarmed initially

**Key Insight**:
```cpp
// HumanA: Reference - must be initialized
Weapon club = Weapon("crude spiked club");
HumanA bob("Bob", club);  // Bob MUST have a weapon
bob.attack();

// HumanB: Pointer - can be null
HumanB jim("Jim");        // Jim starts unarmed
// jim.attack();          // Should handle null weapon
jim.setWeapon(club);      // Now Jim is armed
jim.attack();
```

**When to use**:
- **Reference**: Object always exists, never changes
- **Pointer**: Object might not exist, or might change

### Exercise 04: Sed is for losers (File I/O and String Replacement)

Creates a custom string replacement tool:

**Usage**:
```bash
./sed filename s1 s2
```
- Reads `filename`
- Replaces all occurrences of `s1` with `s2`
- Writes result to `filename.replace`

**Implementation Requirements**:
- Use `std::ifstream` for reading
- Use `std::ofstream` for writing
- No C file functions (fopen, etc.)
- Handle edge cases (file doesn't exist, empty strings, etc.)

**Algorithm**:
```cpp
1. Open input file
2. Read entire file into string (or line by line)
3. For each occurrence of s1:
   a. Find position of s1
   b. Replace with s2
   c. Continue from after replacement
4. Write result to output file
5. Close both files
```

**String Replacement Logic**:
```cpp
std::string result;
size_t pos = 0;
size_t found;

while ((found = content.find(s1, pos)) != std::string::npos) {
    result += content.substr(pos, found - pos);  // Before s1
    result += s2;                                 // Replacement
    pos = found + s1.length();                    // After s1
}
result += content.substr(pos);  // Remaining content
```

### Exercise 05: Harl 2.0 (Member Function Pointers)

Implements a complaint system with different severity levels:

**Harl Class**:
- **Private Methods** (complaint functions):
  - `void debug()` - Debug level messages
  - `void info()` - Info level messages
  - `void warning()` - Warning level messages
  - `void error()` - Error level messages

- **Public Method**:
  - `void complain(std::string level)` - Calls appropriate complaint function

**Implementation Technique**: Member function pointers
```cpp
void Harl::complain(std::string level) {
    void (Harl::*functions[])() = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };
    
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    
    for (int i = 0; i < 4; i++) {
        if (level == levels[i]) {
            (this->*functions[i])();  // Call member function through pointer
            return;
        }
    }
}
```

**Key Concept**: Avoids long if-else chains or switch on strings

### Exercise 06: Harl filter (Switch Statement)

Extends Harl with filtering and fall-through behavior:

**Usage**:
```bash
./harlFilter DEBUG    # Shows all levels (DEBUG, INFO, WARNING, ERROR)
./harlFilter INFO     # Shows INFO, WARNING, ERROR
./harlFilter WARNING  # Shows WARNING, ERROR
./harlFilter ERROR    # Shows only ERROR
```

**Switch Implementation**:
```cpp
switch (level) {
    case DEBUG:
        harl.complain("DEBUG");
        // Fall through
    case INFO:
        harl.complain("INFO");
        // Fall through
    case WARNING:
        harl.complain("WARNING");
        // Fall through
    case ERROR:
        harl.complain("ERROR");
        break;
    default:
        std::cout << "[ Probably complaining about insignificant problems ]";
}
```

**Key Learning**: Switch fall-through behavior (intentionally no `break` between cases)

## Algorithm and Data Structure Explanation

### Stack vs Heap Memory

**Stack Memory**:
- Automatic storage duration
- LIFO (Last In, First Out)
- Limited size (typically 1-8 MB)
- Very fast allocation/deallocation
- Automatic cleanup (destructor called)

**Heap Memory**:
- Dynamic storage duration
- Larger (limited by RAM)
- Slower allocation (system calls)
- Manual management (new/delete)
- Risk of leaks if not deleted

**Memory Layout**:
```
High Address
│
├─ Stack ──────┐  (grows down)
│              │
│   [Local variables, function parameters]
│              │
│              ↓
│
│              ↑
│              │
│   [Dynamically allocated memory]
│              │
├─ Heap ───────┘  (grows up)
│
├─ Data Segment   (global/static variables)
├─ Code Segment   (program instructions)
│
Low Address
```

### new vs delete

**Single Object**:
```cpp
Zombie* z = new Zombie("Name");  // Allocation
delete z;                         // Deallocation
```

**Array**:
```cpp
Zombie* horde = new Zombie[10];  // Array allocation
delete[] horde;                   // Array deallocation (note [])
```

**What happens**:
1. `new`: Allocates memory + calls constructor
2. `delete`: Calls destructor + frees memory
3. `delete[]`: Calls destructor for each element + frees memory

**Common Mistakes**:
```cpp
Zombie* horde = new Zombie[10];
delete horde;     // WRONG: only deletes first, leaks rest
delete[] horde;   // CORRECT: deletes entire array
```

### Pointers vs References

| Aspect | Pointer | Reference |
|--------|---------|-----------|
| **Syntax** | `Type* ptr` | `Type& ref` |
| **Initialization** | Can be uninitialized (null) | Must be initialized |
| **Reassignment** | Can point to different objects | Cannot be rebound |
| **Null** | Can be null | Cannot be null |
| **Dereferencing** | Requires `*ptr` | Automatic (use like variable) |
| **Address** | Use `&` to get address | Use `&` on reference to get address |
| **Use case** | Optional parameter, can change target | Required parameter, alias |

**Example**:
```cpp
int x = 42;
int y = 99;

// Pointer
int* ptr = &x;   // Points to x
*ptr = 50;       // x is now 50
ptr = &y;        // Now points to y
*ptr = 100;      // y is now 100

// Reference
int& ref = x;    // Alias for x
ref = 60;        // x is now 60
ref = y;         // x = y (assignment, not rebinding!)
```

### Member Function Pointers (Exercise 05)

**Syntax**:
```cpp
// Declaration
void (ClassName::*pointerName)();

// Array of member function pointers
void (Harl::*functions[])() = {
    &Harl::debug,
    &Harl::info,
    &Harl::warning,
    &Harl::error
};

// Calling through pointer
(this->*functions[i])();  // this-> is required
```

**Why useful**:
- Avoid long if-else chains
- Dispatch based on index/string
- Implement command patterns
- More maintainable than switch on strings

### File I/O Streams

**Stream Classes**:
```cpp
std::ifstream  // Input file stream (reading)
std::ofstream  // Output file stream (writing)
std::fstream   // Both input and output
```

**Basic Usage**:
```cpp
// Reading
std::ifstream infile("input.txt");
if (!infile.is_open()) {
    // Handle error
}
std::string line;
while (std::getline(infile, line)) {
    // Process line
}
infile.close();

// Writing
std::ofstream outfile("output.txt");
if (!outfile.is_open()) {
    // Handle error
}
outfile << "Hello, World!" << std::endl;
outfile.close();
```

**RAII**: File streams automatically close in destructor (exception-safe)

### String Find and Replace Algorithm

**std::string::find**:
```cpp
size_t pos = str.find("pattern");      // Find first occurrence
size_t pos = str.find("pattern", 10);  // Find starting from position 10

if (pos != std::string::npos) {
    // Found at position pos
}
```

**std::string::substr**:
```cpp
std::string sub = str.substr(pos, length);  // Substring starting at pos
std::string sub = str.substr(pos);          // From pos to end
```

**Replacement Strategy** (Exercise 04):
```
Original: "Hello World Hello"
Find: "Hello"
Replace: "Hi"

Step 1: Find "Hello" at 0
        Result: "" + "Hi" + " World Hello"
        
Step 2: Find "Hello" at 12 (in " World Hello")
        Result: "Hi World " + "Hi"
        
Final: "Hi World Hi"
```

**Edge Cases**:
- Empty search string (replace nothing)
- Search string not found
- Overlapping matches
- Search string contains replacement string

### Switch Statement (Exercise 06)

**Basic Syntax**:
```cpp
switch (expression) {
    case CONSTANT1:
        // Code
        break;
    case CONSTANT2:
        // Code
        break;
    default:
        // Default code
}
```

**Fall-through** (intentional):
```cpp
switch (level) {
    case DEBUG:
        debug();
        // No break - falls through to INFO
    case INFO:
        info();
        // No break - falls through to WARNING
    case WARNING:
        warning();
        // No break - falls through to ERROR
    case ERROR:
        error();
        break;
}
```

**String to Enum** (for switch):
```cpp
enum Level { DEBUG, INFO, WARNING, ERROR, NONE };

Level stringToLevel(const std::string& str) {
    if (str == "DEBUG") return DEBUG;
    if (str == "INFO") return INFO;
    if (str == "WARNING") return WARNING;
    if (str == "ERROR") return ERROR;
    return NONE;
}

switch (stringToLevel(input)) {
    // ...
}
```

## Resources

### Documentation
- [cppreference.com - Memory Management](https://en.cppreference.com/w/cpp/memory)
- [cppreference.com - new/delete](https://en.cppreference.com/w/cpp/language/new)
- [cppreference.com - References](https://en.cppreference.com/w/cpp/language/reference)
- [cppreference.com - Pointers](https://en.cppreference.com/w/cpp/language/pointer)
- [cppreference.com - File I/O](https://en.cppreference.com/w/cpp/io)
- [cppreference.com - std::string](https://en.cppreference.com/w/cpp/string/basic_string)

### Articles and Tutorials
- [LearnCPP.com - Dynamic Memory](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)
- [LearnCPP.com - Pointers vs References](https://www.learncpp.com/cpp-tutorial/pointers-and-references/)
- [GeeksforGeeks - new and delete](https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory/)
- [GeeksforGeeks - File Handling](https://www.geeksforgeeks.org/file-handling-c-classes/)

### Books
- "C++ Primer" by Stanley Lippman (Memory and Pointers chapters)
- "Effective C++" by Scott Meyers (Items on memory management)
- "The C++ Programming Language" by Bjarne Stroustrup

### AI Usage

AI was **not** used in the development of this project. All code was written manually to ensure full understanding of:
- Stack vs heap memory allocation
- Pointer and reference mechanics
- Dynamic memory management with new/delete
- File I/O operations
- String manipulation algorithms
- Member function pointers

The README documentation was also written without AI assistance, based on understanding gained through:
- Reading official C++ documentation
- Studying memory management concepts
- Implementing and testing various scenarios
- Debugging memory leaks and pointer issues

This hands-on approach ensured deep comprehension of C++ memory management and the differences between pointers and references.

## Testing

### Exercise 00 Tests

Test zombie creation and destruction:
```cpp
// Heap zombie
Zombie* heapZombie = newZombie("Heap");
heapZombie->announce();
delete heapZombie;  // Manual cleanup

// Stack zombie
randomChump("Stack");  // Automatic cleanup
```

**Verify**:
- Constructor messages
- Destructor messages
- Proper cleanup order

### Exercise 01 Tests

Test zombie horde:
```cpp
int N = 10;
Zombie* horde = zombieHorde(N, "Horde");
for (int i = 0; i < N; i++)
    horde[i].announce();
delete[] horde;  // Must use delete[]
```

**Memory Test**:
```bash
valgrind --leak-check=full ./zombie_horde
```

### Exercise 02 Tests

Verify addresses and values:
- String address
- Pointer value (should equal string address)
- Reference address (should equal string address)
- All three should display same string content

### Exercise 03 Tests

Test weapon scenarios:
```cpp
// HumanA - always armed
Weapon club = Weapon("crude spiked club");
HumanA bob("Bob", club);
bob.attack();
club.setType("some other type of club");
bob.attack();  // Should show new weapon

// HumanB - optional weapon
HumanB jim("Jim");
jim.setWeapon(club);
jim.attack();
```

### Exercise 04 Tests

Test file replacement:
```bash
echo "Hello World Hello" > test.txt
./sed test.txt "Hello" "Hi"
cat test.txt.replace  # Should show "Hi World Hi"
```

**Edge Cases**:
- Non-existent file
- Empty strings
- String not found
- Overlapping patterns

### Exercise 05 Tests

Test all log levels:
```cpp
Harl harl;
harl.complain("DEBUG");
harl.complain("INFO");
harl.complain("WARNING");
harl.complain("ERROR");
```

### Exercise 06 Tests

Test filtering:
```bash
./harlFilter DEBUG    # Shows all
./harlFilter INFO     # Shows INFO, WARNING, ERROR
./harlFilter WARNING  # Shows WARNING, ERROR
./harlFilter ERROR    # Shows ERROR only
./harlFilter INVALID  # Default message
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
- Always match `new` with `delete` and `new[]` with `delete[]`
- References must be initialized and cannot be null
- Use references for required parameters, pointers for optional
- File streams close automatically (RAII) but explicit close is good practice
- Zombie announces should show both creation and destruction
- Member function pointers require `(this->*pointer)()` syntax
- Switch fall-through is intentional in ex06

## Author

**viceda-s**  
*42 Luxembourg*

---

*For questions, issues, or suggestions, please refer to the 42 project evaluation guidelines.*

