#include "Point.hpp"

// Default constructor - initializes x and y to 0
Point::Point(): x(0), y(0) {
}

// Constructor with float parameters - initializes x and y with given values
Point::Point(const float x, const float y): x(x), y(y) {
}

// Copy constructor - creates a new Point as a copy of another
Point::Point(Point const &copy): x(copy.x), y(copy.y) {
}

// Copy assignment operator - Note: since x and y are const, we can't actually reassign them
// This is a limitation of having const members, but we'll implement it for Orthodox Canonical Form
Point &Point::operator=(Point const &copy) {
	// Since x and y are const, we cannot reassign them
	// This assignment operator won't actually do anything meaningful
	(void)copy; // Suppress unused parameter warning
	return (*this);
}

// Destructor
Point::~Point() {
}

// Returns the x coordinate
Fixed Point::getX() const {
	return this->x;
}

// Returns the y coordinate
Fixed Point::getY() const {
	return this->y;
}