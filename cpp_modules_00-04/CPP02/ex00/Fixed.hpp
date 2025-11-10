#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

// Fixed-point number class (basic version)
// Represents numbers with a fixed number of fractional bits
class Fixed
{
private:
	int value;						// Raw integer value storing the fixed-point number
	static const int fractBits;		// Number of fractional bits (always 8)

public:
	// Orthodox Canonical Form
	Fixed();								// Default constructor
	~Fixed();								// Destructor
	Fixed(Fixed const &copy);				// Copy constructor
	Fixed &operator=(Fixed const &copy);	// Copy assignment operator
	
	// Member functions
	int getRawBits() const;					// Returns the raw value
	void setRawBits(int const raw);			// Sets the raw value
};

#endif