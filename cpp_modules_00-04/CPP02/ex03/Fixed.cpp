#include "Fixed.hpp"
#include <cmath>

// Number of fractional bits used in fixed-point representation
const int Fixed::fractBits = 8;

// Default constructor - initializes value to 0
Fixed::Fixed(): value(0) {
	std::cout << "Default constructor called" << std::endl;
}

// Integer constructor - converts int to fixed-point by shifting left
Fixed::Fixed(const int value): value(value << fractBits) {
	std::cout << "Int constructor called" << std::endl;
}

// Float constructor - converts float to fixed-point using roundf and scaling
Fixed::Fixed(const float value): value(roundf(value * (1 << fractBits))) {
	std::cout << "Float constructor called" << std::endl;
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
	return(this->value);
}

// Sets the raw integer value of the fixed-point number
void Fixed::setRawBits(int const raw) {
	this->value = raw;
}

// Converts fixed-point value to floating-point representation
float Fixed::toFloat(void) const {
	return static_cast<float>(this->value) / (1 << fractBits);
}

// Converts fixed-point value to integer representation
int Fixed::toInt(void) const {
	return this->value >> fractBits;
}

// Insertion operator overload - allows printing Fixed objects to output streams
std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
	out << fixed.toFloat();
	return out;
}

// Comparison operators
bool Fixed::operator>(const Fixed &other) const {
	return this->value > other.value;
}

bool Fixed::operator<(const Fixed &other) const {
	return this->value < other.value;
}

bool Fixed::operator>=(const Fixed &other) const {
	return this->value >= other.value;
}

bool Fixed::operator<=(const Fixed &other) const {
	return this->value <= other.value;
}

bool Fixed::operator==(const Fixed &other) const {
	return this->value == other.value;
}

bool Fixed::operator!=(const Fixed &other) const {
	return this->value != other.value;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &other) const {
	Fixed result;
	result.setRawBits(this->value + other.value);
	return result;
}

Fixed Fixed::operator-(const Fixed &other) const {
	Fixed result;
	result.setRawBits(this->value - other.value);
	return result;
}

Fixed Fixed::operator*(const Fixed &other) const {
	Fixed result;
	// Multiply and then divide by 2^fractBits to maintain fixed-point format
	result.setRawBits((this->value * other.value) >> fractBits);
	return result;
}

Fixed Fixed::operator/(const Fixed &other) const {
	Fixed result;
	// Multiply by 2^fractBits before division to maintain fixed-point format
	result.setRawBits((this->value << fractBits) / other.value);
	return result;
}

// Increment/Decrement operators
Fixed &Fixed::operator++() {
	// Pre-increment: increment by smallest representable epsilon (1)
	this->value++;
	return *this;
}

Fixed Fixed::operator++(int) {
	// Post-increment: return old value, then increment
	Fixed temp(*this);
	this->value++;
	return temp;
}

Fixed &Fixed::operator--() {
	// Pre-decrement: decrement by smallest representable epsilon (1)
	this->value--;
	return *this;
}

Fixed Fixed::operator--(int) {
	// Post-decrement: return old value, then decrement
	Fixed temp(*this);
	this->value--;
	return temp;
}

// Static member functions
Fixed &Fixed::min(Fixed &a, Fixed &b) {
	return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	return (a > b) ? a : b;
}
