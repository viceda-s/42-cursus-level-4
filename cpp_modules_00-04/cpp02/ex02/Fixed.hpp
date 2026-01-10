#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

// Fixed-point number class
// Represents numbers with a fixed number of fractional bits
class Fixed
{
private:
	int value;						// Raw integer value storing the fixed-point number
	static const int fractBits;		// Number of fractional bits (always 8)

public:
	// Orthodox Canonical Form
	Fixed();								// Default constructor
	Fixed(const int value);					// Integer constructor
	Fixed(const float value);				// Float constructor
	~Fixed();								// Destructor
	Fixed(Fixed const &copy);				// Copy constructor
	Fixed &operator=(Fixed const &copy);	// Copy assignment operator
	
	// Member functions
	int getRawBits() const;					// Returns the raw value
	void setRawBits(int const raw);			// Sets the raw value
	float toFloat(void) const;				// Converts to float
	int toInt(void) const;					// Converts to integer
	
	// Comparison operators
	bool operator>(const Fixed &other) const;		// Greater than
	bool operator<(const Fixed &other) const;		// Less than
	bool operator>=(const Fixed &other) const;		// Greater than or equal
	bool operator<=(const Fixed &other) const;		// Less than or equal
	bool operator==(const Fixed &other) const;		// Equal to
	bool operator!=(const Fixed &other) const;		// Not equal to
	
	// Arithmetic operators
	Fixed operator+(const Fixed &other) const;		// Addition
	Fixed operator-(const Fixed &other) const;		// Subtraction
	Fixed operator*(const Fixed &other) const;		// Multiplication
	Fixed operator/(const Fixed &other) const;		// Division
	
	// Increment/Decrement operators
	Fixed &operator++();						// Pre-increment
	Fixed operator++(int);						// Post-increment
	Fixed &operator--();						// Pre-decrement
	Fixed operator--(int);						// Post-decrement
	
	// Static member functions
	static Fixed &min(Fixed &a, Fixed &b);					// Min of two Fixed
	static const Fixed &min(const Fixed &a, const Fixed &b);	// Min of two const Fixed
	static Fixed &max(Fixed &a, Fixed &b);					// Max of two Fixed
	static const Fixed &max(const Fixed &a, const Fixed &b);	// Max of two const Fixed
};

// Insertion operator overload - allows output stream operations
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif