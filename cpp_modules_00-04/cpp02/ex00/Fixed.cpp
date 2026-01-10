#include "Fixed.hpp"

// Number of fractional bits used in fixed-point representation
const int Fixed::fractBits = 8;

// Default constructor - initializes value to 0
Fixed::Fixed(): value(0) {
	std::cout << "Default constructor called" << std::endl;
}

// Destructor
Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

// Copy constructor - creates a new object as a copy of another
Fixed::Fixed(Fixed const &copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

// Copy assignment operator - assigns the value of one object to another
Fixed &Fixed::operator=(Fixed const &copy) {
	std::cout << "Copy assignment operator called" << std::endl;
	this->value = copy.getRawBits();
	return (*this);
}

// Returns the raw integer value of the fixed-point number
int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called" << std::endl;
	return(this->value);
}

// Sets the raw integer value of the fixed-point number
void Fixed::setRawBits(int const raw) {
	this->value = raw;
}
