# CPP Module 00

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

CPP Module 00 is the **introduction to C++ programming**, serving as the gateway from C to C++. This module covers fundamental C++ concepts including namespaces, classes, member functions, stdio streams, initialization lists, static members, const correctness, and other essential building blocks of C++ programming. The project consists of three progressively complex exercises:

- **Exercise 00 (Megaphone)**: A simple command-line program that converts arguments to uppercase, introducing basic C++ I/O and string manipulation
- **Exercise 01 (PhoneBook)**: A contact management system using classes, demonstrating object-oriented programming fundamentals
- **Exercise 02 (Account)**: Reverse-engineering an Account class by analyzing logs and test output, introducing static members and formatted output

### Learning Objectives

- Understanding the transition from C to C++ programming paradigms
- Learning basic C++ syntax, namespaces, and the std namespace
- Mastering classes, encapsulation, and member functions
- Working with I/O streams (std::cout, std::cin, std::getline)
- Understanding static class members and methods
- Learning about const correctness
- Implementing proper class design with private/public access
- Handling user input validation and edge cases

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

#### Exercise 00 - Megaphone
```bash
cd ex00
make
./megaphone "shhhhh... I think the students are asleep..."
./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
./megaphone
```

#### Exercise 01 - PhoneBook
```bash
cd ex01
make
./phonebook
# Available commands:
# ADD    - Add a new contact (max 8)
# SEARCH - Display all contacts and search by index
# EXIT   - Quit the program
```

#### Exercise 02 - Account
```bash
cd ex02
make
./account
# Compare output with 19920104_091532.log
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
cpp00/
├── ex00/                    # Megaphone - uppercase conversion
│   ├── megaphone.cpp       # Main program with toupper logic
│   └── Makefile
├── ex01/                    # PhoneBook - contact management
│   ├── Contact.cpp         # Contact class implementation
│   ├── Contact.hpp         # Contact class declaration
│   ├── PhoneBook.cpp       # PhoneBook class implementation
│   ├── PhoneBook.hpp       # PhoneBook class declaration
│   ├── main.cpp            # Main program loop
│   └── Makefile
├── ex02/                    # Account class implementation
│   ├── Account.cpp         # Account implementation (to complete)
│   ├── Account.hpp         # Account header (provided)
│   ├── tests.cpp           # Test file (provided)
│   ├── 19920104_091532.log # Expected output log
│   └── Makefile
└── README.md
```

## Features

### Exercise 00: Megaphone

A simple program that demonstrates C++ basics:
- **Input**: Command-line arguments
- **Output**: Uppercased text
- **Special Case**: No arguments → displays "* LOUD AND UNBEARABLE FEEDBACK NOISE *"

**Implementation Details**:
- Uses `std::cout` and `std::endl` for output
- String manipulation with `std::string`
- Character conversion with `std::toupper()`
- Demonstrates basic C++ I/O and string handling

**Example**:
```bash
$ ./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...

$ ./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.

$ ./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### Exercise 01: PhoneBook

A contact management system demonstrating OOP principles:

**Contact Class**:
- **Private Attributes**: firstName, lastName, nickname, phoneNumber, darkestSecret
- **Public Methods**: Getters and setters for each field
- **Encapsulation**: Private data with public accessors

**PhoneBook Class**:
- **Storage**: Array of 8 Contact objects
- **Features**:
  - Add contacts (replaces oldest when full)
  - Search and display contacts in formatted table
  - Input validation
- **Commands**:
  - `ADD`: Add a new contact (prompts for 5 fields)
  - `SEARCH`: Display all contacts + detailed view by index
  - `EXIT`: Quit the program

**Display Format**:
```
|     Index|First Name| Last Name|  Nickname|
|----------|----------|----------|----------|
|         0|      John|       Doe|     JDoe |
|         1|      Jane|     Smith|     Janie|
```

**Implementation Details**:
- Text truncation to 10 characters with right alignment
- Index-based contact retrieval
- Input validation for index selection
- Private helper methods for formatting and validation

### Exercise 02: Account Class

Reverse-engineering exercise focused on static members:

**Challenge**: Implement Account.cpp to match the provided log output exactly

**Account Class Features**:
- **Instance Attributes**: accountIndex, amount, nb_deposits, nb_withdrawals
- **Static Attributes**: nb_accounts, total_amount, total_nb_deposits, total_nb_withdrawals
- **Static Methods**: 
  - `getNbAccounts()`, `getTotalAmount()`, `getNbDeposits()`, `getNbWithdrawals()`
  - `displayAccountsInfos()` - displays aggregate information
- **Instance Methods**:
  - `makeDeposit(int deposit)` - add funds
  - `makeWithdrawal(int withdrawal)` - remove funds (check sufficient balance)
  - `checkAmount()` - return current amount
  - `displayStatus()` - display account details

**Key Concepts**:
- **Static Members**: Shared across all instances
- **Static Methods**: Operate on static data, no instance required
- **Timestamp Formatting**: `[19920104_091532]` format (year, month, day, time)
- **Constructor/Destructor Messages**: Track account creation and destruction

**Log Format**:
```
[19920104_091532] index:0;amount:42;created
[19920104_091532] index:1;amount:54;created
[19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
[19920104_091532] index:0;amount:42;deposits:0;withdrawals:0
...
[19920104_091532] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
...
[19920104_091532] index:0;amount:47;closed
```

## Algorithm and Data Structure Explanation

### C vs C++: Key Differences

This module introduces fundamental differences between C and C++:

| Aspect | C | C++ |
|--------|---|-----|
| **I/O** | `printf()`, `scanf()` | `std::cout`, `std::cin` with `<<`, `>>` |
| **Strings** | `char*`, manual management | `std::string` with automatic memory |
| **Organization** | Functions, structs | Classes with methods and attributes |
| **Memory** | `malloc()`, `free()` | `new`, `delete` (introduced in module 01) |
| **Namespaces** | None | `std::`, custom namespaces |
| **Type Safety** | Weaker | Stronger with references and const |

### Classes and Objects

**Class**: Blueprint for creating objects (user-defined type)
**Object**: Instance of a class

```cpp
class Contact {
private:
    std::string firstName;  // Private attribute
public:
    void setFirstName(const std::string& name);  // Public method
    std::string getFirstName() const;            // Const method
};

Contact john;  // Object (instance of Contact)
```

**Encapsulation**:
- **Private**: Accessible only within the class
- **Public**: Accessible from outside the class
- **Purpose**: Hide implementation details, control access

### Static Members (Exercise 02)

**Static Class Members** are shared across all instances:

```cpp
class Account {
private:
    static int _nbAccounts;     // Shared by all Account objects
    int _accountIndex;          // Unique per instance

public:
    static int getNbAccounts(); // Static method, no 'this' pointer
    void displayStatus();       // Instance method, has 'this' pointer
};

// Definition (outside class)
int Account::_nbAccounts = 0;
```

**Memory Layout**:
```
Static Memory:
[_nbAccounts] [_totalAmount] [_totalNbDeposits] [_totalNbWithdrawals]
       ↑             ↑                ↑                    ↑
    Shared by all instances

Heap/Stack Memory (per instance):
Account object 1: [_accountIndex] [_amount] [_nbDeposits] [_nbWithdrawals]
Account object 2: [_accountIndex] [_amount] [_nbDeposits] [_nbWithdrawals]
```

**When to use static**:
- Counting instances (e.g., number of accounts)
- Shared configuration or constants
- Utility functions that don't need instance data

### PhoneBook Data Structure (Exercise 01)

**Array-based Circular Buffer**:
```
contacts[8]:  [0] [1] [2] [3] [4] [5] [6] [7]
               ↑
         currentIndex (wraps around when reaching 8)
```

**Algorithm for ADD**:
1. Get contact information from user
2. Store at `contacts[currentIndex]`
3. Increment `currentIndex`
4. If `currentIndex == 8`, wrap to 0
5. Track `totalContacts` (max 8)

**Circular Buffer Logic**:
```cpp
void PhoneBook::addContact() {
    // ... get contact data ...
    _contacts[_currentIndex] = newContact;
    _currentIndex = (_currentIndex + 1) % 8;  // Wrap around
    if (_totalContacts < 8)
        _totalContacts++;
}
```

**Benefits**:
- Fixed memory usage (no dynamic allocation)
- Automatic oldest contact replacement
- Simple index-based access

### String Formatting (Exercise 01)

**Text Truncation and Alignment**:
```cpp
std::string PhoneBook::_truncateText(const std::string& text) const {
    if (text.length() > 10)
        return text.substr(0, 9) + ".";
    return text;
}
```

**Table Formatting with iomanip**:
```cpp
#include <iomanip>

std::cout << "|" << std::setw(10) << std::right << truncatedText << "|";
```
- `std::setw(10)`: Sets field width to 10 characters
- `std::right`: Right-aligns the text
- Pads with spaces automatically

### I/O Streams

**Stream Operators**:
- `<<` (insertion): Sends data to output stream
- `>>` (extraction): Gets data from input stream

**Stream Hierarchy**:
```
                    ios_base
                       ↓
                      ios
                   /   |   \
              istream ostream iostream
                ↓       ↓       ↓
              cin     cout    fstream
```

**std::cin issues**:
```cpp
int number;
std::cin >> number;  // Problem: leaves newline in buffer

std::string line;
std::getline(std::cin, line);  // Gets the leftover newline!
```

**Solution**: Use `std::getline()` consistently or clear buffer after `>>`

### Input Validation (Exercise 01)

**Empty Input Check**:
```cpp
std::string input;
std::getline(std::cin, input);
if (input.empty()) {
    std::cout << "Error: Field cannot be empty" << std::endl;
    // Re-prompt user
}
```

**Index Validation**:
```cpp
bool PhoneBook::_isValidIndex(const std::string& input, int& index) const {
    // Check if string contains only digits
    for (size_t i = 0; i < input.length(); i++) {
        if (!isdigit(input[i]))
            return false;
    }
    
    // Convert to int
    index = atoi(input.c_str());
    
    // Check range
    return (index >= 0 && index < _totalContacts);
}
```

### Time Formatting (Exercise 02)

**Timestamp Format**: `[YYYYMMDD_HHMMSS]`

```cpp
#include <ctime>

void Account::_displayTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::cout << "[" 
              << (1900 + ltm->tm_year)
              << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon)
              << std::setfill('0') << std::setw(2) << ltm->tm_mday
              << "_"
              << std::setfill('0') << std::setw(2) << ltm->tm_hour
              << std::setfill('0') << std::setw(2) << ltm->tm_min
              << std::setfill('0') << std::setw(2) << ltm->tm_sec
              << "] ";
}
```

**std::setfill('0')**: Pads with zeros instead of spaces
**std::setw(2)**: Ensures 2-digit fields (e.g., 09 instead of 9)

### Constructor and Destructor (Exercise 02)

**Constructor**: Called when object is created
**Destructor**: Called when object is destroyed

```cpp
Account::Account(int initial_deposit) : _amount(initial_deposit) {
    _accountIndex = _nbAccounts++;  // Use static counter
    _totalAmount += _amount;        // Update static total
    _displayTimestamp();
    std::cout << "index:" << _accountIndex 
              << ";amount:" << _amount 
              << ";created" << std::endl;
}

Account::~Account() {
    _totalAmount -= _amount;        // Update static total
    _displayTimestamp();
    std::cout << "index:" << _accountIndex 
              << ";amount:" << _amount 
              << ";closed" << std::endl;
}
```

**Initialization List**: `: _amount(initial_deposit)`
- More efficient than assignment in constructor body
- Required for const members and references
- Required for base class initialization

### Const Correctness

**Const Methods**: Promise not to modify object state
```cpp
int Account::checkAmount() const {
    return _amount;  // OK: reading member
    // _amount = 100;  // ERROR: would modify member
}
```

**Const Parameters**: Promise not to modify parameter
```cpp
void Contact::setFirstName(const std::string& name) {
    _firstName = name;  // OK: modifying our own member
    // name[0] = 'X';    // ERROR: would modify parameter
}
```

**Benefits**:
- Prevents accidental modifications
- Enables compiler optimizations
- Self-documenting code (indicates intent)
- Allows calling methods on const objects

## Resources

### Documentation
- [cppreference.com - iostream](https://en.cppreference.com/w/cpp/io)
- [cppreference.com - string](https://en.cppreference.com/w/cpp/string/basic_string)
- [cppreference.com - iomanip](https://en.cppreference.com/w/cpp/io/manip)
- [cppreference.com - Classes](https://en.cppreference.com/w/cpp/language/classes)
- [cppreference.com - Static Members](https://en.cppreference.com/w/cpp/language/static)

### Articles and Tutorials
- [LearnCPP.com - Introduction to C++](https://www.learncpp.com/cpp-tutorial/introduction-to-cplusplus/)
- [LearnCPP.com - Classes](https://www.learncpp.com/cpp-tutorial/classes-and-class-members/)
- [GeeksforGeeks - Classes and Objects](https://www.geeksforgeeks.org/c-classes-and-objects/)
- [GeeksforGeeks - Static Members](https://www.geeksforgeeks.org/static-data-members-c/)

### Books
- "C++ Primer" by Stanley Lippman (Comprehensive introduction)
- "A Tour of C++" by Bjarne Stroustrup (Quick overview by creator)
- "The C++ Programming Language" by Bjarne Stroustrup (Definitive reference)
- "Effective C++" by Scott Meyers (Best practices)

### AI Usage

AI was **not** used in the development of this project. All code was written manually to ensure full understanding of:
- C++ basic syntax and I/O streams
- Class design and encapsulation
- Static members and methods
- String manipulation and formatting
- Input validation and error handling

The README documentation was also written without AI assistance, based on understanding gained through:
- Reading official C++ documentation
- Studying class design principles
- Implementing and testing the exercises
- Comparing output with provided logs

This hands-on approach ensured deep comprehension of C++ fundamentals and object-oriented programming basics.

## Testing

### Exercise 00 Tests

Test with various inputs:

**Normal cases**:
```bash
./megaphone "hello world"
./megaphone "Hello" "World" "!"
./megaphone "42"
```

**Edge cases**:
```bash
./megaphone                    # No arguments
./megaphone ""                 # Empty string
./megaphone "MiXeD CaSe"      # Mixed case
./megaphone "123!@#"          # Numbers and symbols
```

### Exercise 01 Tests

Test PhoneBook functionality:

1. **ADD Command**:
   - Add valid contacts
   - Add more than 8 contacts (test replacement)
   - Try empty fields (should reject)

2. **SEARCH Command**:
   - Search with no contacts
   - Search with valid index
   - Search with invalid index (negative, out of range, non-numeric)
   - Display with truncated text (>10 characters)

3. **Edge Cases**:
   - Very long input strings
   - Special characters in names
   - EOF (Ctrl+D) handling

**Example Session**:
```
$> ./phonebook
ADD
First name: John
Last name: Doe
Nickname: JD
Phone number: 1234567890
Darkest secret: Loves pineapple on pizza
SEARCH
|     Index|First Name| Last Name|  Nickname|
|----------|----------|----------|----------|
|         0|      John|       Doe|        JD|
Enter index: 0
First name: John
Last name: Doe
Nickname: JD
Phone number: 1234567890
Darkest secret: Loves pineapple on pizza
EXIT
```

### Exercise 02 Tests

**Verification**:
1. Compile and run: `./account`
2. Compare output with `19920104_091532.log`
3. Check timestamp format (ignore actual time values)
4. Verify:
   - Account creation messages
   - Deposit operations
   - Withdrawal operations (including failed ones)
   - Account closure messages
   - Static method outputs

**Output Format Checks**:
- Timestamp format: `[YYYYMMDD_HHMMSS]`
- Creation: `index:X;amount:Y;created`
- Deposit: `index:X;p_amount:Y;deposit:Z;amount:W;nb_deposits:N`
- Withdrawal: `index:X;p_amount:Y;withdrawal:Z;amount:W;nb_withdrawals:N`
- Failed withdrawal: `index:X;p_amount:Y;withdrawal:refused`
- Closure: `index:X;amount:Y;closed`

## Notes

- All code follows the **C++98 standard** (no C++11 or later features)
- No STL containers allowed in this module (std::string is permitted)
- Header guards should be used in all header files
- PhoneBook uses fixed array (no dynamic allocation)
- Account.cpp must match log output exactly (including formatting)
- Static member initialization must be outside the class definition
- Const correctness is important (mark read-only methods as const)

## Author

**viceda-s**  
*42 Luxembourg*

---

*For questions, issues, or suggestions, please refer to the 42 project evaluation guidelines.*

