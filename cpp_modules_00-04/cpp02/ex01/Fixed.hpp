#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

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
};

// Insertion operator overload - allows output stream operations
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif